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
    /**
     * @brief  Constructeur privé (singleton). Empêche l'instanciation externe
     *
     */
    Timer();

    /**
     * @brief Indique si le minuteur est en cours d'exécution (thread-safe)
     *
     */
    std::atomic<bool> running;

    /**
     * @brief Thread dédié à l’attente du délai
     *
     */
    std::thread worker;

    /**
     * @brief Heure de démarrage du minuteur
     *
     */
    std::chrono::steady_clock::time_point startTime;

    /**
     * @brief Délai total en millisecondes
     *
     */
    int delayMs;

    /**
     * @brief Mutex utilisé pour la synchronisation
     *
     */
    std::mutex mtx;

    /**
     * @brief Permet d’interrompre l’attente via stop()
     *
     */
    std::condition_variable cv;

public:
    /**
     * @brief Retourne l'instance unique de Timer (singleton)
     *
     * @return Timer&
     */
    static Timer &getInstance();

    /**
     * @brief Convertit un temps en secondes vers un format "M:SS" (ex: 65 => "1:05")
     *
     * @param toFormat Valeur à convertir
     * @return std::string
     */
    static std::string formatTime(int toFormat);

    /**
     * @brief Interdit l’affectation
     *
     */
    Timer(const Timer &) = delete;

    /**
     * @brief Interdit l’affectation
     *
     */
    Timer &operator=(const Timer &) = delete;

    /**
     * @brief Renvoie le temps écoulé depuis start() en ms
     *
     * @return int
     */
    int getElapsedTimeMs() const;

    /**
     * @brief Renvoie le temps restant jusqu’à l’expiration
     *
     * @return int
     */
    int getRemainingTimeMs() const;

    /**
     * @brief Retourne true si le minuteur est actif
     *
     * @return true
     * @return false
     */
    bool isRunning() const;

    /**
     * @brief Démarre le minuteur pour ms millisecondes et exécute le callback à la fin
     *
     * @param ms Valeur en milisec
     * @param callback callback de la fonction
     */
    void start(int ms, std::function<void()> callback);

    /**
     * @brief Arrête le minuteur prématurément et interrompt le thread
     *
     */
    void stop();

    /**
     * @brief  Destructeur : appelle stop() et nettoie les ressources
     *
     */
    ~Timer();
};

#endif
