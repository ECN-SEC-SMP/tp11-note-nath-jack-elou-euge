/**
 * @file TermCtrl.cpp
 * @author Nathan ANDRE 
 * @brief 
 * @version 0.1
 * @date 2025-05-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */
/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-04-28
 * 
 * @copyright Copyright (c) 2025
 * 
 */

// ================================================================================
// Include
// ================================================================================
#include "TermCtrl.hpp"

#include <iostream>
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include <vector>
#include <map>
#include <thread>

// ================================================================================
// Macros
// ================================================================================

#define KEY_ENTER       '\n'
#define KEY_SPACE       ' '
#define KEY_BACKSPACE   std::string("\x7f")

#define KEY_START_ARROW "\33["
#define KEY_UP      std::string("\33[A")
#define KEY_DOWN    std::string("\33[B")
#define KEY_RIGHT   std::string("\33[C")
#define KEY_LEFT    std::string("\33[D")

// ================================================================================
// Types
// ================================================================================

// ================================================================================
// Constantes
// ================================================================================

// ================================================================================
// Variables globale
// ================================================================================

std::thread TermWorker;

termios oldTerminal;

bool _TermCtrlStarted = false;
TermCtrl* _TermInstance = nullptr;

/**
 * @brief Map of callback for each enum in TermEvents
 * 
 */
std::map<TermEvents, TermCtrlEvent_Callback> EventCallbackTable = {
    {TermEvents::DIRECTIONAL_ARROW, nullptr},
    {TermEvents::DIGIT_INPUT, nullptr},
    {TermEvents::SPACE_INPUT, nullptr}
};

/**
 * @brief List of events stored as string
 * 
 */
std::map<TermEvents, std::queue<std::string>> EventPendingTable = {
    {TermEvents::DIRECTIONAL_ARROW, {}},
    {TermEvents::DIGIT_INPUT, {}},
    {TermEvents::SPACE_INPUT, {}}
};

// ================================================================================
// Fonction declaration
// ================================================================================

char getcharAlt(void);
void TermThreadRunner(void);

// ================================================================================
// Thread Fonctions definitions
// ================================================================================
void TermThreadRunner(void) {
    int raw;
    char c;
    std::string word = "";

    fflush(stdin);
    while (_TermCtrlStarted)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // To prevent looping to fast
        c = getcharAlt();
        if (c == EOF) {
            continue;
        }
        std::cout << (uint16_t)c << std::endl;
        word.push_back(c);

        /**
         * Word detection for simple characters is made by looking if word variable
         * contain only wanted char and has a size of 2 : char + empty char (string).
         * 
         * If word variable exceed the size of 2, it should be cleared, enless it
         * start by character for arrows.
         */

        // Look for digits
        if ((word[0] >= '0' && word[0] <= '9') && word.size() == 1) {
            
            EventPendingTable[TermEvents::DIGIT_INPUT].push(word);

            word = "";
            continue;
        }

        // Look for Enter key
        else if ((word[0] == KEY_SPACE) && word.size() == 1) {

            EventPendingTable[TermEvents::SPACE_INPUT].push(word);

            word = "";
            continue;
        }

        // Look for arrow keys
        else if (word == KEY_UP) {
            EventPendingTable[TermEvents::DIRECTIONAL_ARROW].push(KEY_UP);
            word = "";
        }
        
        else if (word == KEY_DOWN) {
            EventPendingTable[TermEvents::DIRECTIONAL_ARROW].push(KEY_DOWN);
            word = "";
        }
        
        else if (word == KEY_RIGHT) {
            EventPendingTable[TermEvents::DIRECTIONAL_ARROW].push(KEY_RIGHT);
            word = "";
        }
        
        else if (word == KEY_LEFT) {
            EventPendingTable[TermEvents::DIRECTIONAL_ARROW].push(KEY_LEFT);
            word = "";
        }

        // Reset 
        else if (word.size() == 1) {
            if (word != "\33") {
                word = "";
            }
        }
        else if (word.size() >= 2) {
            if (word.size() == 2 && word != KEY_START_ARROW) {

                word = "";
            }

            if (word.size() >= 4) {
                word = "";
            }
        }
    }
}

// ================================================================================
// Private Fonctions definitions
// ================================================================================

void TermCtrl::sendEvents(TermEvents key, TermCtrlEvent_Callback func, std::queue<std::string>* event) {
    std::string token;
    
    while (event->size())
    {
        token = event->front();  // Get first arrow
        event->pop(); // Remove first arrow

        func(token);
    }
}

char getcharAlt(void) {
    char buff[2];
    int l = read(STDIN_FILENO,buff,1);
    if (l>0) return buff[0];
    return ( EOF);
}

// ================================================================================
// Protected Fonctions definitions
// ================================================================================

TermCtrl::TermCtrl(void) {

}

// ================================================================================
// Public Fonctions definitions
// ================================================================================

TermCtrl::~TermCtrl() {
    // Restore Terminal if it hasn't been made
    if (_TermCtrlStarted) {
        this->end();
    }
}

TermCtrl* TermCtrl::getInstance(void) {
    if (_TermInstance == nullptr) {
        _TermInstance = new TermCtrl();
    }
    return _TermInstance;
}

void TermCtrl::begin(void) {
    termios newt;

    // Clear all pending events
    this->eventClearAll();

    tcgetattr(STDIN_FILENO, &oldTerminal); // Sauvegarde de l'ancien mode
    newt = oldTerminal;
    newt.c_lflag &= ~(ICANON | ECHO);        // Mode sans buffer ni echo
    newt.c_cc[VMIN] = 0;
    newt.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Activation du mode
    _TermCtrlStarted = true;

    TermWorker = std::thread(TermThreadRunner);

}

void TermCtrl::end(void) {
    _TermCtrlStarted = false;

    if (TermWorker.joinable())
    {
        TermWorker.join();
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldTerminal); // Restauration

}

bool TermCtrl::isStarted(void) {
    return _TermCtrlStarted;
}

void TermCtrl::attach(TermEvents evt_type, TermCtrlEvent_Callback func) {
    // Add callback to the Event to Callback table
    EventCallbackTable[evt_type] = func;
}



void TermCtrl::runEvents(void) {
    std::map<TermEvents, TermCtrlEvent_Callback>::iterator it;
    TermEvents key;
    TermCtrlEvent_Callback callback;
    uint8_t nb_callbacks;

    for (it = EventCallbackTable.begin(); it != EventCallbackTable.end(); it++)
    {
        key = it->first;
        callback = it->second;

        // Check if event is pending
        if (!EventPendingTable[key].size()) {
            continue;
        }

        // Check if there is an attached callback
        if (EventCallbackTable[key] == nullptr) {
            continue;
        }
        
        // Send event
        this->sendEvents(key, callback, &EventPendingTable[key]);
    }
    
}

uint8_t TermCtrl::eventPending(TermEvents evt) {
    return EventPendingTable[evt].size();
}

void TermCtrl::eventClear(TermEvents evt) {
    while (EventPendingTable[evt].size())
    {
        EventPendingTable[evt].pop();
    }
}

void TermCtrl::eventClearAll(void) {
    this->eventClear(TermEvents::DIRECTIONAL_ARROW);
    this->eventClear(TermEvents::DIGIT_INPUT);
    this->eventClear(TermEvents::SPACE_INPUT);
}

// ================================================================================
// Test Fonctions definitions
// ================================================================================

void TermCtrl_Test_ArrowCallback(std::string evt) {

    std::cout << "[ARROW KEY] ";

    if (evt == KEY_DOWN) {
        std::cout << "KEY_DOWN" << std::endl;
    }
    if (evt == KEY_UP) {
        std::cout << "KEY_UP" << std::endl;
    }
    if (evt == KEY_LEFT) {
        std::cout << "KEY_LEFT" << std::endl;
    }
    if (evt == KEY_RIGHT) {
        std::cout << "KEY_RIGHT" << std::endl;
    }
}

void TermCtrl_Test_DigitCallback(std::string evt) {
    std::cout << "[DIGIT KEY] " << evt << std::endl;
}
void TermCtrl_Test_SpaceCallback(std::string evt) {
    if (evt == std::string(" ")) {
        std::cout << "[SPACE KEY] SPACE" << std::endl;
    }
}

void TermCtrl_Test(void) {
    TermCtrl* term = TermCtrl::getInstance();

    std::cout << "Begin TermCtrl Test" << std::endl;
    std::cout << "Push keys en check if it's printed in cli :" << std::endl;
    std::cout << "\t- Arrows : LEFT, RIGHT, UP, DOWN" << std::endl;
    std::cout << "\t- SPACE" << std::endl;
    std::cout << "\t- Digits from 0 to 9" << std::endl;

    term->attach(TermEvents::DIRECTIONAL_ARROW, TermCtrl_Test_ArrowCallback);
    term->attach(TermEvents::DIGIT_INPUT, TermCtrl_Test_DigitCallback);
    term->attach(TermEvents::SPACE_INPUT, TermCtrl_Test_SpaceCallback);

    term->begin();

    while (_TermCtrlStarted)
    {
        sleep(1);
        term->runEvents();
    }
    
    

    term->end();
    return;
}

