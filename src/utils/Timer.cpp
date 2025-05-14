/**
 * @file Timer.cpp
 * @brief Singleton class to count time and indicate when timer as ended.
 * @version 0.1
 * @date 2025-05-14
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "Timer.hpp"
#include <sstream>
#include <iomanip>

/**
 * @brief  Constructeur privé (singleton). Empêche l'instanciation externe
 *
 */
Timer::Timer() : running(false), delayMs(0) {}

/**
 * @brief  Destructeur : appelle stop() et nettoie les ressources
 *
 */
Timer::~Timer()
{
    stop();
}

/**
 * @brief Retourne l'instance unique de Timer (singleton)
 *
 * @return Timer&
 */
Timer &Timer::getInstance()
{
    static Timer instance;
    return instance;
}

/**
 * @brief Démarre le minuteur pour ms millisecondes et exécute le callback à la fin
 *
 * @param ms Valeur en milisec
 * @param callback callback de la fonction
 */
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

/**
 * @brief Arrête le minuteur prématurément et interrompt le thread
 *
 */
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

/**
 * @brief Retourne true si le minuteur est actif
 *
 * @return true
 * @return false
 */
bool Timer::isRunning() const
{
    return this->running;
}

/**
 * @brief Renvoie le temps écoulé depuis start() en ms
 *
 * @return int
 */
int Timer::getElapsedTimeMs() const
{
    if (!this->running)
        return 0;
    auto now = std::chrono::steady_clock::now();
    return static_cast<int>(
        std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime).count());
}

/**
 * @brief Renvoie le temps restant jusqu’à l’expiration
 *
 * @return int
 */
int Timer::getRemainingTimeMs() const
{
    if (!this->running)
        return 0;
    int remaining = this->delayMs - getElapsedTimeMs();
    return remaining > 0 ? remaining : 0;
}

/**
 * @brief Convertit un temps en secondes vers un format "M:SS" (ex: 65 => "1:05")
 *
 * @param toFormat Valeur à convertir
 * @return std::string
 */
std::string Timer::formatTime(int toFormat)
{
    int minutes = toFormat / 60;
    int seconds = toFormat % 60;
    std::ostringstream oss;
    oss << minutes << ":" << std::setw(2) << std::setfill('0') << seconds;
    return oss.str();
}
