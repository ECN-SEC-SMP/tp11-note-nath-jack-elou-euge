/**
 * @file TermCtrl.hpp
 * @author Nathan ANDRE
 * @brief
 * @version 0.1
 * @date 2025-05-06
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef _TERM_CTRL_HPP_
#define _TERM_CTRL_HPP_
// ================================================================================
// Include
// ================================================================================
#include <cstdint>
#include <string>
#include <queue>
#include <functional>
// ================================================================================
// Macro
// ================================================================================

#define KEY_ENTER '\n'
#define KEY_SPACE std::string(" ")
#define KEY_BACKSPACE std::string("\x7f")

#define KEY_START_ARROW "\33["
#define KEY_UP std::string("\33[A")
#define KEY_DOWN std::string("\33[B")
#define KEY_RIGHT std::string("\33[C")
#define KEY_LEFT std::string("\33[D")

// ================================================================================
// Types
// ================================================================================

typedef std::function<void(std::string)> TermCtrlEvent_Callback;
// ================================================================================
// Tests declaration
// ================================================================================

void TermCtrl_Test(void);

// ================================================================================
// Class declaration
// ================================================================================

enum class TermEvents
{
    DIRECTIONAL_ARROW,
    DIGIT_INPUT,
    ENTER_INPUT
};

/**
 * @brief Singleton to get Terminal inputs
 *
 */
class TermCtrl
{
private:
    bool initialized;

    /**
     * @brief Will call sending event method corresponding with key
     *
     * @param func
     * @param event
     */
    void sendEvents(TermEvents key, TermCtrlEvent_Callback func, std::queue<std::string> *event);

protected:
    TermCtrl(void);

public:
    /**
     * Singletons should not be cloneable.
     */
    TermCtrl(TermCtrl &other) = delete;
    ~TermCtrl();

    /**
     * Singletons should not be assignable.
     */
    void operator=(const TermCtrl &) = delete;

    /**
     * @brief Get the Instance object
     *
     * @return TermCtrl*
     */
    static TermCtrl *getInstance(void);

    /**
     * @brief Start Terminal Control Mode
     *
     */
    void begin(void);

    /**
     * @brief End Terminal Control Mode
     *
     */
    void end(void);

    /**
     * @brief Return if the TermCtrl Singleton is started
     *
     * @return true TermCtrl is started,
     * @return false TermCtrl is stopped
     */
    bool isStarted(void);

    /**
     * @brief Attach a callback to an event.
     *
     * The callback is called with the string corresponding to the occured event.
     * Those callback are called by the runEvents methods.
     *
     * @param evt_type Type of the event
     * @param callback Callback Function, take in parameter a string
     */
    void attach(TermEvents evt_type, TermCtrlEvent_Callback func);

    /**
     * @brief Run pending events. Call this function to avoid calling callbacks in TermCtrl thread context
     *
     */
    void runEvents(void);

    /**
     * @brief Return the number of pending event
     *
     * @param evt The type of event to check
     * @return uint8_t Number of events pendings
     */
    uint8_t eventPending(TermEvents evt);

    /**
     * @brief Clear pending events
     *
     * @param evt The event type to clear
     */
    void eventClear(TermEvents evt);

    /**
     * @brief Clear all pending events
     *
     */
    void eventClearAll(void);
};

#endif // _TERM_CTRL_HPP_
