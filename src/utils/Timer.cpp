#include "Timer.hpp"
#include <sstream>
#include <iomanip>

Timer::Timer() : running(false), delayMs(0) {}

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

    this->delayMs = delay_ms;
    this->startTime = std::chrono::steady_clock::now();
    this->running = true;

    this->worker = std::thread([this, callback]()
                         {
        // Verrouille l'accès aux ressources partagées
        std::unique_lock<std::mutex> lock(this->mtx);

        // Attend soit que la durée s'écoule, soit qu'on appelle stop()
        // La condition est "running == false", le wait se termine si on arrête le timer
        if (cv.wait_for(lock, std::chrono::milliseconds(this->delayMs), [this] { return !this->running.load(); })) {
            return; // Si stop est appellé avant la fin du timer
        }

        if (this->running.load()) {
            callback();
        } });
}

void Timer::stop()
{
    {
        std::lock_guard<std::mutex> lock(mtx);
        this->running = false;
    }
    this->cv.notify_one(); // Interrompt le wait
    if (this->worker.joinable())
    {
        this->worker.join();
    }
}

bool Timer::isRunning() const
{
    return this->running;
}

int Timer::getElapsedTimeMs() const
{
    if (!this->running)
        return 0;
    auto now = std::chrono::steady_clock::now();
    return static_cast<int>(
        std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime).count());
}

int Timer::getRemainingTimeMs() const
{
    if (!this->running)
        return 0;
    int remaining = this->delayMs - getElapsedTimeMs();
    return remaining > 0 ? remaining : 0;
}

std::string Timer::formatTime(int toFormat)
{
    int minutes = toFormat / 60;
    int seconds = toFormat % 60;
    std::ostringstream oss;
    oss << minutes << ":" << std::setw(2) << std::setfill('0') << seconds;
    return oss.str();
}
