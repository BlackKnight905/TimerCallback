#include "timerCallback.h"
/**  
 * Constructor for TimerCallback class.
 * 
 * @param values none
 * @return none
 */
TimerCallback::TimerCallback() : _pCallback(nullptr),
                                 _timerPeriodMs(0UL),
                                 _runCallbackThread(false),
                                 _callbackThreadFinished(true),
                                 _callbackRegistered(false),
                                 _timerMode(TimerMode::kOneShot),
                                 _pCallbackData(nullptr) {
}
/**
 * This method implements callback thread loop.
 *
 * @param values none
 * @return none
 */
void TimerCallback::timerThread() {
    Timer timer;
    timer.start();
    _callbackThreadFinished = false;
    while (_runCallbackThread) {
        if (timer.elapsedTimeMs() >= _timerPeriodMs) {
            if (_pCallback && _runCallbackThread) _pCallback(_pCallbackData);
            if (_timerMode == TimerMode::kOneShot) {
                _runCallbackThread = false;
                break;
            }
            else timer.restart();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    _callbackThreadFinished = true;
}
/**
 * This method allows user to register callback and it's exectution parameters. 
 * It must be called before runCallbackThread(). 
 * If callback thread is currently running for this TimerCallback instance nothing is going to happen.  
 * If callback thread is already registered there will be no effect of calling this function.
 *
 * @param values timerMode - one shot or periodic callback execution modes are avaliable
 *               timerPeriodMs - time period given in miliseconds, that callback is going to be executed, 
 *               pCallbackFunction - adress of callback function
 *               pCallbackData - data that will be passed to callback function
 * @return none
 */
void TimerCallback::registerCallback(TimerMode timerMode, unsigned long timerPeriodMs,
                                          std::function<void(void *data)> pCallbackFunction,
                                          void *pCallbackData) {
    if (_callbackThreadFinished && !_callbackRegistered) {
        _pCallback = pCallbackFunction;
        _timerPeriodMs = timerPeriodMs;
        _callbackRegistered = true;
        _timerMode = timerMode;
        _pCallbackData = pCallbackData;
    }
}
/**
 * This method allows user to unregister callback and it's exectution parameters.
 * If callback thread is currently running, it will be stoped.
 * Before next time registerCallback() must be called to setup new callback and execution parameters. 
 * 
 * @param values none
 * @return none
 */
void TimerCallback::unregisterCallback() {
    if(!_callbackRegistered) return;
    _runCallbackThread = false;
    while (!_callbackThreadFinished);
    _pCallback = nullptr;
    _pCallbackData = nullptr;
    _callbackRegistered = false;
    _timerPeriodMs = 0UL;
}
/**
 * This method allows user to stop execution of registered callback thread. 
 * All execution parameters and callback function adress won't be cleared.
 * To start again a callback thread use method runCallbackThread().
 * 
 * @param values none
 * @return none
 */
void TimerCallback::stopCallbackThread() {
    if(!_callbackRegistered) return;
    _runCallbackThread = false;
    while (!_callbackThreadFinished);
}
/**
 * This method allows user to start execution of registered callback thread. 
 * Only one callback thread is possible to be exectuted in moment for one TimerCallback instance.
 * If callback thread is currently running there will be no efects of calling this method. 
 * 
 * @param values none
 * @return none
 */
void TimerCallback::runCallbackThread() {
    if (_callbackThreadFinished && _callbackRegistered) {
        _runCallbackThread = true;
        std::thread thread(&TimerCallback::timerThread, this);
        thread.detach();
    }
}
/**
 * This method returns information if callback thread is currently running.
 * 
 * @param values none
 * @return true - callback thread is currently running, 
 *         false - callback thread isn't currently running 
 */
bool TimerCallback::isCallbackThreadRunning () {
    return !(_callbackThreadFinished);
}
/**
 * This method returns information if callback and exexution parameters are currently registered.
 * 
 * @param values none
 * @return true - callback is registered,
 *         false - callback isn't registered
 */
bool TimerCallback::isCallbackRegistered() {
    return (_callbackRegistered);
}