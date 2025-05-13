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
#include "Display.hpp"

#include <iostream>
#include <string>
#include <cstdint>
#include <string>
#include <cstring>
#include <map>

#include "Timer.hpp"

// ================================================================================
// Macros
// ================================================================================

/**
 * A Case is made with 3 spaces for the board to be square.
 * The first space is where robot can be displayed
 * The last space is where the target can be displayed
 */
#define DISP_ROBOT_PLACE    0   // Robot place in a case
#define DISP_TARGET_PLACE   2   // Target place in a case
#define DISP_TARGET_OBJECTIF_X   16
#define DISP_TARGET_OBJECTIF_Y   16

#define CENTER_INDEX_START  15  // Start of center zone
#define CENTER_INDEX_END    17  // End of center zone

// Lines
#define LINE_HORIZ  "───"               // Vertical grid line x3 for case printing
#define LINE_HORIZ_WALL  "═══"          // Vertical wall line x3 for case printing
#define CROSSING_LINE_HORIZ_WALL  "═"   // Vertical wall line
#define LINE_VERTI  "│"                 // Horizontal grid line
#define LINE_VERTI_WALL  "║"            // Horizontal wall line
#define CROSSING_LINE_VERTI_WALL  "║"   // Horizontal wall line
#define SPACE       "   "               // Empty space for case

// Corners
#define CORNER_TOPLEFT  "┌"             // Top left corner grid
#define CORNER_TOPLEFT_WALL_FULL    "╔" // Top left corner wall
#define CORNER_TOPLEFT_WALL_BOT     "╓" // Top left corner bottom wall
#define CORNER_TOPLEFT_WALL_RIGHT   "╒" // Top left corner right wall

#define CORNER_TOPRIGHT "┐"             // Top right corner grid
#define CORNER_TOPRIGHT_WALL_FULL   "╗" // Top right corner wall
#define CORNER_TOPRIGHT_WALL_BOT    "╖" // Top right corner bottom wall
#define CORNER_TOPRIGHT_WALL_LEFT   "╕" // Top right corner left wall

#define CORNER_BOTLEFT  "└"             // Bottom left corner grid
#define CORNER_BOTLEFT_WALL_FULL    "╚" // Bottom left corner wall
#define CORNER_BOTLEFT_WALL_TOP     "╙" // Bottom left corner top wall
#define CORNER_BOTLEFT_WALL_RIGHT   "╘" // Bottom left corner right wall

#define CORNER_BOTRIGHT "┘"             // Bottom right corner grid
#define CORNER_BOTRIGHT_WALL_FULL   "╝" // Bottom right corner wall
#define CORNER_BOTRIGHT_WALL_TOP    "╜" // Bottom right corner top wall
#define CORNER_BOTRIGHT_WALL_LEFT   "╛" // Bottom right corner left wall

// Intersections
#define CROSSING_VERTI_TO_RIGHT "├"             // Vertical grid with extension to the right
#define CROSSING_VERTI_TO_RIGHT_WALL_FULL   "╠" // Vertical wall with extension to the right
#define CROSSING_VERTI_TO_RIGHT_WALL_RIGHT  "╞" // Vertical grid with wall extension to the right
#define CROSSING_VERTI_TO_RIGHT_WALL_VERTI  "╟" // Vertical wall with grid extension to the right

#define CROSSING_VERTI_TO_LEFT  "┤"             // Vertical grid with extension to the left
#define CROSSING_VERTI_TO_LEFT_WALL_FULL    "╣" // Vertical wall with extension to the left
#define CROSSING_VERTI_TO_LEFT_WALL_LEFT    "╡" // Vertical grid with wall extension to the left
#define CROSSING_VERTI_TO_LEFT_WALL_VERTI   "╢" // Vertical wall with grid extension to the left

#define CROSSING_HORIZ_TO_TOP   "┴"             // Horizontal grid with extension at the top
#define CROSSING_HORIZ_TO_TOP_WALL_FULL     "╩" // Horizontal wall with extension at the top
#define CROSSING_HORIZ_TO_TOP_WALL_TOP      "╨" // Horizontal grid with wall extension at the top
#define CROSSING_HORIZ_TO_TOP_WALL_HORIZ    "╧" // Horizontal wall with grid extension at the top

#define CROSSING_HORIZ_TO_BOT   "┬"             // Horizontal grid with extension at the bottom
#define CROSSING_HORIZ_TO_BOT_WALL_FULL     "╦" // Horizontal wall with extension at the bottom
#define CROSSING_HORIZ_TO_BOT_WALL_BOT      "╥" // Horizontal grid with wall extension at the bottom
#define CROSSING_HORIZ_TO_BOT_WALL_HORIZ    "╤" // Horizontal wall with grid extension at the bottom

#define CROSSING_CROSS          "┼"             // Crossing grid
#define CROSSING_CROSS_WALL_FULL            "╬" // Crossing wall
#define CROSSING_CROSS_WALL_VERTI           "╫" // Crossing with vertical wall
#define CROSSING_CROSS_WALL_HORIZ           "╪" // Crossing with horizontal wall

// Ansi Escapes Codes
// ESC Code Sequence 	Description
// ESC[38;5;{ID}m 	    Set foreground color.
// ESC[48;5;{ID}m 	    Set background color.

#define ANSI_CODE_ERASE "\33[0J"                        // ANSI ESCAPE CODE TO erase terminal
#define ANSI_CODE_CURSOR_RESET "\33[H"                  // ANSI ESCAPE CODE TO put cursor at x : 0, y : 0
#define ANSI_CODE_BACKGROUND_RESET "\033[39m\033[49m"   // ANSI ESCAPE CODE TO reset background color to default

#define ANSI_CODE_BACKGROUND_APP "\33[48;5;15m"         // ANSI ESCAPE CODE TO set the app background white
#define ANSI_CODE_BACKGROUND_CENTER "\33[48;5;0m"       // ANSI ESCAPE CODE TO set the app background black
#define ANSI_CODE_FOREGROUND_APP "\33[38;5;0m"          // ANSI ESCAPE CODE TO set the app foreground black
#define ANSI_CODE_FOREGROUND_CENTER "\33[38;5;15m"      // ANSI ESCAPE CODE TO set the app foreground white

#define ANSI_CODE_FOREGROUND_RED "\33[38;5;1m"
#define ANSI_CODE_FOREGROUND_BLUE "\33[38;5;4m"
#define ANSI_CODE_FOREGROUND_GREEN "\33[38;5;2m"
#define ANSI_CODE_FOREGROUND_YELLOW "\33[38;5;220m"

#define ANSI_CODE_LINE_COLOR "\33[38;5;253m"            // ANSI ESCAPE CODE TO set color for grid lines in grey
#define ANSI_CODE_WALL_COLOR "\33[38;5;0m"              // ANSI ESCAPE CODE TO set color for wall in black

#define ANSI_CODE_ERASE_LINE "\33[K"                    // ANSI ESCAPE CODE TO erase a line

#define ANSI_CODE_CURSOR_POS_SAVE   "\33[s"             // ANSI ESCAPE CODE TO save cursor position
#define ANSI_CODE_CURSOR_POS_LOAD   "\33[u"             // ANSI ESCAPE CODE TO load a saved cursor position

// ================================================================================
// Types
// ================================================================================

// ================================================================================
// Constantes
// ================================================================================
/**
 * @brief Map to get ANSI ESCAPE CODE to set colors
 * 
 */
std::map<Color, std::string> COLOR_MAP = {
    {Default,   std::string(ANSI_CODE_FOREGROUND_APP)},
    {Red,       std::string(ANSI_CODE_FOREGROUND_RED)},
    {Blue,      std::string(ANSI_CODE_FOREGROUND_BLUE)},
    {Green,     std::string(ANSI_CODE_FOREGROUND_GREEN)},
    {Yellow,    std::string(ANSI_CODE_FOREGROUND_YELLOW)},
    {Rainbow,   std::string(ANSI_CODE_FOREGROUND_APP)},
};

/**
 * @brief Map to get differents symbols for targets and robots
 * 
 */
std::map<Shape, std::string> SHAPE_MAP = {
    {Target1,    "♣"},
    {Target2,    "♥"},
    {Target3,    "♦"},
    {Target4,    "♠"},
    {TargetRainbow, "🌈"},
    {RobotSign,  "██"},
};

// ================================================================================
// Variables globale
// ================================================================================

// ================================================================================
// Fonction declaration
// ================================================================================

// ================================================================================
// Public Fonctions definitions
// ================================================================================

/**
 * @brief Construct a new Display:: Display object
 * 
 * Set colors for terminal
 * 
 */
Display::Display(void) {
    std::cout << ANSI_CODE_BACKGROUND_APP;
    std::cout << ANSI_CODE_FOREGROUND_APP;
    std::cout << ANSI_CODE_CURSOR_RESET << ANSI_CODE_ERASE;
}

/**
 * @brief Destroy the Display:: Display object
 * 
 * Reset colors and clear terminal
 * 
 */
Display::~Display(void) {
    std::cout << ANSI_CODE_BACKGROUND_RESET;
    std::cout << ANSI_CODE_CURSOR_RESET << ANSI_CODE_ERASE;
}

/**
 * @brief Update Display's board
 * 
 * @param board 
 */
void Display::update(Case board[SIZE_BOARD][SIZE_BOARD]) {
    std::memcpy(this->board, board, sizeof(Case) * SIZE_BOARD * SIZE_BOARD);

    // Une case n'a un mur présent qu'à l'EST
    std::string to_put;
    
    // SIZE_BOARD + 1 because we want to print last line, /!\ Should not get value from array
    for (uint8_t i = 0; i < BOARD_DISP_SIZE; i++) {
        for (uint8_t j = 0; j < BOARD_DISP_SIZE; j++) {
            // Corners
            if (i == 0 && j == 0) {
                to_put = CORNER_TOPLEFT;
                // to_put = this->put_line(CORNER_TOPLEFT, x, y, DISP_CASE_NONE);
            }
            else if (i == 0 && j == (SIZE_BOARD * 2)) {
                to_put = CORNER_TOPRIGHT;
                // to_put = this->put_line(CORNER_TOPRIGHT, x, y, DISP_CASE_NONE);
            }
            else if (i == (SIZE_BOARD * 2) && j == 0) {
                to_put = CORNER_BOTLEFT;
                // to_put = this->put_line(CORNER_BOTLEFT, x, y, DISP_CASE_NONE);
            }
            else if (i == (SIZE_BOARD * 2) && j == (SIZE_BOARD * 2)) {
                to_put = CORNER_BOTRIGHT;
                // to_put = this->put_line(CORNER_BOTRIGHT, x, y, DISP_CASE_NONE);
            }
            
            // // Crossing
            else if (i == 0 && !(j % 2)) {
                // to_put = this->getWallStr(CROSSING_HORIZ_TO_BOT_WALL_HORIZ);
                to_put = this->getWallStr(CROSSING_LINE_HORIZ_WALL);
            }
            else if (i == (SIZE_BOARD * 2) && !(j % 2)) {
                // to_put = this->getWallStr(CROSSING_HORIZ_TO_TOP_WALL_HORIZ);
                to_put = this->getWallStr(CROSSING_LINE_HORIZ_WALL);
            }
            else if (!(i % 2) && j == 0) {
                // to_put = this->getWallStr(CROSSING_VERTI_TO_RIGHT_WALL_VERTI);
                to_put = this->getWallStr(CROSSING_LINE_VERTI_WALL);
            }
            else if (!(i % 2) && j == (SIZE_BOARD * 2)) {
                // to_put = this->getWallStr(CROSSING_VERTI_TO_LEFT_WALL_VERTI);
                to_put = this->getWallStr(CROSSING_LINE_VERTI_WALL);
            }
            else if (!(i % 2) && !(j % 2)) {
                to_put = CROSSING_CROSS;
                // to_put = this->put_line(CROSSING_CROSS, x, y, DISP_CASE_NONE);
            }
            
            // Lines
            else if (!(i % 2)) {
                to_put = LINE_HORIZ;
                // to_put = this->put_line(LINE_HORIZ, x, y, DISP_CASE_NONE);
            }
            else if (!(j % 2)) {
                to_put = LINE_VERTI;
                // to_put = this->put_line(LINE_VERTI, x, y, DISP_CASE_NONE);
            }
            else {
                to_put = SPACE;
                // to_put = this->put_line(SPACE, x, y, DISP_CASE_NONE);
            }
            
            // Add to board disp
            if (to_put != SPACE) {
                to_put.insert(0, ANSI_CODE_LINE_COLOR);
                to_put.append(ANSI_CODE_FOREGROUND_APP);
            }
            this->dispBoard[i][j] = to_put;
        }
    }

    this->put_walls();
    this->put_robots();
    this->put_targets();
    this->put_center();
}
void printcolors(void);
/**
 * @brief Print board
 * 
 */
void Display::print(void) {
    std::cout << ANSI_CODE_CURSOR_RESET << ANSI_CODE_ERASE;
    // std::cout  << ANSI_CODE_ERASE;

    this->put_time();
    for (uint8_t i = 0; i < BOARD_DISP_SIZE; i++)
    {
        for (uint8_t j = 0; j < BOARD_DISP_SIZE; j++) 
        {

            std::cout << dispBoard[i][j];
            
        }   // Fin j
        std::cout << std::endl;
    }   // Fin i

    // Print perma lines
    for (uint8_t i = 0; i < PERMA_LINES_MAX_NB; i++)
    {
        if (this->permaLines[i].empty()) {
            continue;
        }

        std::cout << this->permaLines[i] << "\n";
    }
    
}

/**
 * @brief Print Time on the first line of terminal
 * 
 */
void Display::printTime(void) {
    // Save cursor pos
    std::cout << ANSI_CODE_CURSOR_POS_SAVE;
    // Goes to 0 0
    std::cout << ANSI_CODE_CURSOR_RESET;
    
    // Erase Line
    std::cout << ANSI_CODE_ERASE_LINE;

    this->put_time();
    
    // Return to cursor pos
    std::cout << ANSI_CODE_CURSOR_POS_LOAD;
}

/**
 * @brief Add line to print after the board
 * 
 * @param line Line to prin
 * @return int8_t Index of the line, needed to update or clear line, -1 if error
 */
int8_t Display::addLine(std::string line) {
    int8_t i = 0;

    while (!(this->permaLines[i].empty())) {
        i++;

        if (i >= PERMA_LINES_MAX_NB) {
            i = -1;
            return i;
        }
    }

    this->permaLines[i] = line;
    return i;
}

/**
 * @brief Update existing line bt it's index
 * 
 * @param lineIndex Index of the line to update
 * @param line New line
 */
void Display::updateLine(uint8_t lineIndex, std::string line) {
    if (lineIndex >= PERMA_LINES_MAX_NB) {
        return;
    }
    this->permaLines[lineIndex] = line;
}

/**
 * @brief Remove existing line by it's index
 * 
 * @param lineIndex 
 */
void Display::clearLine(uint8_t lineIndex) {
    if (lineIndex >= PERMA_LINES_MAX_NB) {
        return;
    }
    this->permaLines[lineIndex] = "";
}


// ================================================================================
// Private Fonctions definitions
// ================================================================================

/**
 * @brief Get Timer Singleton instance and print remaining time
 * 
 */
void Display::put_time(void) {
    Timer& time = Timer::getInstance();
    int t = time.getRemainingTimeMs();

    std::string timeStr = time.formatTime(t/1000);
    timeStr.insert(0, "Remaining Time : ");

    uint8_t strLength = timeStr.size();

    for (uint8_t i = 0; i < ((BOARD_DISP_SIZE / 2) - (strLength / 2)); i++)
    {
        std::cout << " ";
    }

    std::cout << timeStr << std::endl;
}

/**
 * @brief Put walls in dispBoard
 * 
 */
void Display::put_walls(void) {
    Case curCase;
    uint8_t x, y;

    // ===== Put Sides Walls
    for (uint8_t i = 0; i < SIZE_BOARD; i++)
    {
        for (uint8_t j = 0; j < SIZE_BOARD; j++) 
        {
            // Get current case
            curCase = this->board[i][j];

            // Get dispBoard Coord
            y = i*2 + 1;
            x = j*2 + 1;

            // If no wall next
            if (!curCase.isWall()) {
                continue;
            }

            if (curCase.getNorth()) {
                this->dispBoard[x - 1][y] = LINE_HORIZ_WALL;
            }

            if (curCase.getSouth()) {
                this->dispBoard[x + 1][y] = LINE_HORIZ_WALL;
            }
            
            if (curCase.getEast()) {
                this->dispBoard[x][y + 1] = LINE_VERTI_WALL;
            }
            
            if (curCase.getWest()) {
                this->dispBoard[x][y - 1] = LINE_VERTI_WALL;
            }

        }   // Fin j
    }   // Fin i

    // ===== Puts intersections
    // Bot, Top, Right, Left has a wall
    bool wbot, wtop, wrgt, wlft;
    std::string to_put;
    for (uint8_t i = 0; i < BOARD_DISP_SIZE; i += 2)
    {
        for (uint8_t j = 0; j < BOARD_DISP_SIZE; j += 2)
        {
            to_put = "";
            // ===== Check Corners
            // Top Left
            if (i == 0 && j == 0) {
                // Righ
                wrgt = (this->dispBoard[i][j + 1].find(LINE_HORIZ_WALL) != std::string::npos) ? true : false;
                
                // Bot
                wbot = (this->dispBoard[i + 1][j].find(LINE_VERTI_WALL) != std::string::npos) ? true : false;

                if (wrgt && wbot) {
                    to_put = CORNER_TOPLEFT_WALL_FULL;
                }
                else if (wbot) {
                    to_put = CORNER_TOPLEFT_WALL_BOT;
                }
                else if (wrgt) {
                    to_put = CORNER_TOPLEFT_WALL_RIGHT;
                }
            }
            // Top Right
            else if (i == 0 && j == (BOARD_DISP_SIZE - 1)) {
                // Left
                wlft = (this->dispBoard[i][j - 1].find(LINE_HORIZ_WALL) != std::string::npos) ? true : false;
                
                // Bot
                wbot = (this->dispBoard[i + 1][j].find(LINE_VERTI_WALL) != std::string::npos) ? true : false;
    
                if (wlft && wbot) {
                    to_put = CORNER_TOPRIGHT_WALL_FULL;
                }
                else if (wbot) {
                    to_put = CORNER_TOPRIGHT_WALL_BOT;
                }
                else if (wlft) {
                    to_put = CORNER_TOPRIGHT_WALL_LEFT;
                }
            }
            // Bottom Left
            else if (i == (BOARD_DISP_SIZE - 1) && j == 0) {
                // Left
                wrgt = (this->dispBoard[i][j + 1].find(LINE_HORIZ_WALL) != std::string::npos) ? true : false;
                
                // Bot
                wtop = (this->dispBoard[i - 1][j].find(LINE_VERTI_WALL) != std::string::npos) ? true : false;
    
                if (wrgt && wtop) {
                    to_put = CORNER_BOTLEFT_WALL_FULL;
                }
                else if (wtop) {
                    to_put = CORNER_BOTLEFT_WALL_TOP;
                }
                else if (wrgt) {
                    to_put = CORNER_BOTLEFT_WALL_RIGHT;
                }
            }
            // Bottom Right
            else if (i == (BOARD_DISP_SIZE - 1) && j == (BOARD_DISP_SIZE - 1)) {
                // Left
                wlft = (this->dispBoard[i][j - 1].find(LINE_HORIZ_WALL) != std::string::npos) ? true : false;
                
                // Bot
                wtop = (this->dispBoard[i - 1][j].find(LINE_VERTI_WALL) != std::string::npos) ? true : false;
    
                if (wlft && wtop) {
                    to_put = CORNER_BOTRIGHT_WALL_FULL;
                }
                else if (wtop) {
                    to_put = CORNER_BOTRIGHT_WALL_TOP;
                }
                else if (wlft) {
                    to_put = CORNER_BOTRIGHT_WALL_LEFT;
                }
            }

            // ===== Check Sides intersections
            // Top Side
            else if (i == 0) {
                wbot = (this->dispBoard[i + 1][j].find(LINE_VERTI_WALL) != std::string::npos) ? true : false;
                if (wbot) {
                    to_put = CROSSING_HORIZ_TO_BOT_WALL_FULL;
                }
            }
            // Bot Side
            else if (i == (BOARD_DISP_SIZE - 1)) {
                wtop = (this->dispBoard[i - 1][j].find(LINE_VERTI_WALL) != std::string::npos) ? true : false;
                if (wtop) {
                    to_put = CROSSING_HORIZ_TO_TOP_WALL_FULL;
                }
            }
            // Left Side
            else if (j == 0) {
                wrgt = (this->dispBoard[i][j + 1].find(LINE_HORIZ_WALL) != std::string::npos) ? true : false;
                if (wrgt) {
                    to_put = CROSSING_VERTI_TO_RIGHT_WALL_FULL;
                }
            }
            // Right Side
            else if (j == (BOARD_DISP_SIZE - 1)) {
                wlft = (this->dispBoard[i][j - 1].find(LINE_HORIZ_WALL) != std::string::npos) ? true : false;
                if (wlft) {
                    to_put = CROSSING_VERTI_TO_LEFT_WALL_FULL;
                }
            }
            
            // ===== Check Cross intersections
            else {
                wtop = (this->dispBoard[i - 1][j].find(LINE_VERTI_WALL) != std::string::npos) ? true : false;
                wbot = (this->dispBoard[i + 1][j].find(LINE_VERTI_WALL) != std::string::npos) ? true : false;
                wrgt = (this->dispBoard[i][j + 1].find(LINE_HORIZ_WALL) != std::string::npos) ? true : false;
                wlft = (this->dispBoard[i][j - 1].find(LINE_HORIZ_WALL) != std::string::npos) ? true : false;

                // Count true booleans
                uint8_t nb_true = (uint8_t)wtop + (uint8_t)wbot + (uint8_t)wlft + (uint8_t)wrgt;

                if (nb_true == 4) {
                    to_put = this->getWallStr(CROSSING_CROSS_WALL_FULL);
                }
                else if (nb_true == 3)
                {
                    if (wtop && wbot) {
                        // Crossing Vertical
                        to_put = wrgt ? CROSSING_VERTI_TO_RIGHT_WALL_FULL : CROSSING_VERTI_TO_LEFT_WALL_FULL;
                    }
                    else if (wrgt && wlft) {
                        // Crossing Horizontal
                        to_put = wtop ? CROSSING_HORIZ_TO_TOP_WALL_FULL : CROSSING_HORIZ_TO_BOT_WALL_FULL;
                    }
                }
                else if (nb_true == 2)
                {
                    // Corner and lines
                    if (wtop && wbot) {
                        // Line Vertial
                        to_put = this->getWallStr(CROSSING_LINE_VERTI_WALL);
                    }
                    else if (wlft && wrgt) {
                        // Line Horizontal
                        to_put = this->getWallStr(CROSSING_LINE_HORIZ_WALL);
                    }
                    else if (wtop && wlft) {
                        // Corner Bottom Right
                        to_put = this->getWallStr(CORNER_BOTRIGHT_WALL_FULL);
                    }
                    else if (wtop && wrgt) {
                        // Corner Bottom Left
                        to_put = this->getWallStr(CORNER_BOTLEFT_WALL_FULL);
                    }
                    else if (wbot && wlft) {
                        // Corner Top Right
                        to_put = this->getWallStr(CORNER_TOPRIGHT_WALL_FULL);
                    }
                    else if (wbot && wrgt) {
                        // Corner Top Left
                        to_put = this->getWallStr(CORNER_TOPLEFT_WALL_FULL);
                    }
                }
            }
            
            // ===== Put string
            if (to_put != "") {
                this->dispBoard[i][j] = this->getWallStr(to_put);
            }
        }   // End for j
    }   // End for i
}

/**
 * @brief Put Robots in Display Board
 * 
 */
void Display::put_robots(void) {
    uint8_t x, y;
    Case curCase;
    Robot* curRobot;
    std::string strTarget = "";

    for (uint8_t i = 0; i < SIZE_BOARD; i++)
    {
        for (uint8_t j = 0; j < SIZE_BOARD; j++) 
        {
            // Get current case
            curCase = this->board[i][j];

            // Get dispBoard Coord
            y = i*2 + 1;
            x = j*2 + 1;

            curRobot = curCase.getRobot();

            if (curRobot == nullptr)
            {
                continue;
            }
            
            Color clr = curRobot->getColor();
            Shape shp = curRobot->getShape();

            strTarget = "";
            strTarget.append(COLOR_MAP[clr]);
            strTarget.append(SHAPE_MAP[shp]);
            strTarget.append(COLOR_MAP[Default]);

            // From SHAPE_MAP we can see that a robot take 2 space
            this->dispBoard[x][y].erase(DISP_ROBOT_PLACE, 2); // Remove Space, robot take 2 spaces
            this->dispBoard[x][y].insert(DISP_ROBOT_PLACE, strTarget);

        }
    }
}

/**
 * @brief Put Targets in Display Board
 * 
 */
void Display::put_targets(void) {
    uint8_t x, y;
    Case curCase;
    Target* curTarget;
    std::string strTarget = "";

    for (uint8_t i = 0; i < SIZE_BOARD; i++)
    {
        for (uint8_t j = 0; j < SIZE_BOARD; j++) 
        {
            // Get current case
            curCase = this->board[i][j];

            // Get dispBoard Coord
            y = i*2 + 1;
            x = j*2 + 1;

            curTarget = curCase.getTarget();

            if (curTarget == nullptr)
            {
                continue;
            }
            
            strTarget = this->getTargetStr(curTarget);

            if ((curTarget->getShape() == TargetRainbow)) {
                if ((curCase.getRobot() != nullptr))
                {
                    continue;
                }
                
                this->dispBoard[x][y].pop_back();
            }

            this->dispBoard[x][y].pop_back();
            this->dispBoard[x][y].append(strTarget);
        }
    }
}

/**
 * @brief Put center in Display Board
 * 
 */
void Display::put_center(void) {

    // Draw center
    for (uint8_t i = CENTER_INDEX_START; i <= CENTER_INDEX_END; i++)
    {
        for (uint8_t j = CENTER_INDEX_START; j <= CENTER_INDEX_END; j++)
        {
            // Wall
            if (!(j%2)) {
                this->dispBoard[i][j] = std::string(ANSI_CODE_BACKGROUND_APP) + " " + std::string(ANSI_CODE_BACKGROUND_APP);
            } 
            // Case
            else {
                this->dispBoard[i][j] = std::string(ANSI_CODE_BACKGROUND_APP) + std::string(SPACE) + std::string(ANSI_CODE_BACKGROUND_APP);
            }
        }   // Fin j
    }   // Fin i

    // Put target in middle
    Target* targ = this->board[TARGET_OBJECTIF_X][TARGET_OBJECTIF_Y].getTarget();
    this->dispBoard[DISP_TARGET_OBJECTIF_X][DISP_TARGET_OBJECTIF_Y] = getTargetStr(targ);

    if (targ->getShape() == TargetRainbow) {
        this->dispBoard[DISP_TARGET_OBJECTIF_X][DISP_TARGET_OBJECTIF_Y + 1] = "  ";
    }

}

/**
 * @brief Get the wall with ANSI ESCAPE CODE for colors
 * 
 * @param wall_chr Wall character to put
 * @return std::string 
 */
std::string Display::getWallStr(std::string wall_chr) {
    return std::string(ANSI_CODE_WALL_COLOR) + wall_chr + std::string(ANSI_CODE_BACKGROUND_APP);
}

std::string Display::getTargetStr(Target* targ) {
    std::string retStr = "";
    Color clr = targ->getColor();
    Shape shp = targ->getShape();

    retStr.append(COLOR_MAP[clr]);
    retStr.append(SHAPE_MAP[shp]);
    retStr.append(COLOR_MAP[Default]);

    return retStr;
}

// ================================================================================
// Test Fonctions definitions
// ================================================================================


bool running = true;
void stop(void) {
    running = false;
}

void Display_Test(void) {

    Board board = Board();
    Display disp = Display();
    Case plateau[16][16];

    Timer& time = Timer::getInstance();
    time.start(100000, stop);

    Target* listTarg[] = {
        new Target(Blue, Target1),
        new Target(Red, Target2),
        new Target(Green, Target3),
        new Target(Yellow, Target4),
        new Target(Rainbow, TargetRainbow)
    };
    
    board.getBoard(plateau);

    plateau[0][0].setTarget(listTarg[0]);
    plateau[15][0].setTarget(listTarg[1]);
    plateau[4][6].setTarget(listTarg[2]);
    plateau[13][10].setTarget(listTarg[3]);
    plateau[7][3].setTarget(listTarg[4]);
    // plateau[TARGET_OBJECTIF_X][TARGET_OBJECTIF_Y].setTarget(listTarg[4]);
    plateau[TARGET_OBJECTIF_X][TARGET_OBJECTIF_Y].setTarget(listTarg[3]);

    disp.update(plateau);

    // while (running)
    // {
        // if (!time.isRunning()) {
        //     break;
        // }
        disp.print();


        // if ((time.getElapsedTimeMs() % 1000) == 0) {
        //     disp.print();
        // }
    // }

    std::string tp;
    std::cin >> tp;
    std::cout << "EXIT MAIN" << std::endl;

    time.stop();

}