#ifndef _TIMER_HPP_
#define _TIMER_HPP_

#include <iostream>
#include <chrono>
#include <thread>
#include <functional>
#include <atomic>
#include <string>
#include <condition_variable>
#include <mutex>

class Timer
{
private:
    Timer();

    std::atomic<bool> running;
    std::thread worker;

    std::chrono::steady_clock::time_point startTime;
    int delayMs;

    std::mutex mtx;
    std::condition_variable cv;

public:
    static Timer &getInstance();
    static std::string formatTime(int toFormat);

    Timer(const Timer &) = delete;
    Timer &operator=(const Timer &) = delete;

    int getElapsedTimeMs() const;
    int getRemainingTimeMs() const;

    bool isRunning() const;

    void start(int ms, std::function<void()> callback);
    void stop();

    ~Timer();
};

#endif
