#include <chrono>
#include <ctime>
#include <cmath>

#ifndef TIMER_H_
#define TIMER_H_
class Timer {
    private:
        std::chrono::high_resolution_clock::time_point _startTime;
        std::chrono::high_resolution_clock::time_point _stopTime;
        bool _running;

    public:
        Timer();
        void start();
        void stop();
        void restart();
        bool isRunning() const;
        unsigned long elapsedTimeMs() const;
        unsigned long elapsedTimeS() const;
};
#endif
