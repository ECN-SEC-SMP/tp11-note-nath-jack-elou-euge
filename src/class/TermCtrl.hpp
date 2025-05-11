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

// ================================================================================
// Macro
// ================================================================================

// ================================================================================
// Types
// ================================================================================

typedef void (*TermCtrlEvent_Callback)(std::string);

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
    void sendEvents(TermEvents key, TermCtrlEvent_Callback func, std::queue<std::string>* event);

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
    static TermCtrl* getInstance(void);

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
};

#endif  // _TERM_CTRL_HPP_
