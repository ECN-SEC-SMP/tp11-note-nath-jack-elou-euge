#include "Timer.hpp"

Timer::Timer()
{
    this->running = false;
    this->delayMs = 0;
}

Timer::~Timer()
{
    stop();
}

Timer &Timer::getInstance()
{
    static Timer instance;
    return instance;
}

void Timer::start(int delay_ms, std::function<void()> callback)
{
    stop();
    running = true;
    delayMs = delay_ms;
    startTime = std::chrono::steady_clock::now();

    worker = std::thread([=]()
                         {
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
        if (running) {
            callback();
        } });
}

void Timer::stop()
{
    running = false;
    if (worker.joinable())
    {
        worker.join();
    }
}

int Timer::getElapsedTimeMs() const
{
    if (!running)
        return 0;
    auto now = std::chrono::steady_clock::now();
    return static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime).count());
}

int Timer::getRemainingTimeMs() const
{
    if (!running)
        return 0;
    int elapsed = getElapsedTimeMs();
    int remaining = delayMs - elapsed;
    return remaining > 0 ? remaining : 0;
}

std::string Timer::formatTime(int toFormat)
{
    int seconde = toFormat % 60;
    std::string minute = std::to_string(toFormat / 60);
    std::string sec = (seconde  < 10 ? "0" : "") + std::to_string(seconde);
    return minute + ":" + sec;
}