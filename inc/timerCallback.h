#include <thread>
#include <functional>
#include <atomic>
#include "timer.h"

#ifndef TIMERCALLBACK_H_
#define TIMERCALLBACK_H_
/* Timer operating modes */
enum class TimerMode {
    kOneShot,
    kPeriodic
};
/* TimerCallback class */
class TimerCallback {
public:
    /* Public methods */
    TimerCallback();
    void registerCallback(TimerMode timerMode, unsigned long timerPeriodMs,
                          std::function<void(void *data)> callbackFunction, void *callbackData);
    void unregisterCallback();
    void runCallbackThread();
    void stopCallbackThread();
    bool isCallbackThreadRunning();
    bool isCallbackRegistered();
private:
    /* Private Vars */
    std::function<void(void *)> _pCallback;
    unsigned long _timerPeriodMs;
    std::atomic<bool> _runCallbackThread;
    std::atomic<bool> _callbackThreadFinished;
    std::atomic<bool> _callbackRegistered;
    TimerMode _timerMode;
    void *_pCallbackData;
    /* Private methods */
    void timerThread();
};
#endif
