#ifndef _TIMER_HPP_
#define _TIMER_HPP_
#include <iostream>
#include <chrono>
#include <thread>
#include <functional>
#include <atomic>
#include <string>

class Timer
{
private:
    Timer();

    std::atomic<bool> running;
    std::thread worker;

    std::chrono::steady_clock::time_point startTime;
    int delayMs;

public:
    static Timer &getInstance();
    static std::string formatTime(int toFormat);

    // Delete copy operator
    Timer(const Timer &) = delete;
    Timer &operator=(const Timer &) = delete;

    // Timing info
    int getElapsedTimeMs() const;
    int getRemainingTimeMs() const;

    bool isRunning(void);

    void start(int ms, std::function<void()> callback);
    void stop();


    ~Timer();
};

#endif