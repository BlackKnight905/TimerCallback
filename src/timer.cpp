#include "timer.h"
/**
 * Timer class constructor.
 *
 * @param values none 
 * @return none
 */
Timer::Timer() {
    _running = false;
    _startTime = std::chrono::high_resolution_clock::now();
    _stopTime = std::chrono::high_resolution_clock::now();
}
/**
 * Time mesurement begins from this moment untill stop() method is called.
 *
 * @param values none 
 * @return none
 */
void Timer::start() {
    _startTime = std::chrono::high_resolution_clock::now();
    _running = true;
}
/**
 * Time mesurement ceases in this moment. 
 * Use start() method to begin a new mesurement.
 *
 * @param values none 
 * @return none
 */
void Timer::stop() {
    _stopTime = std::chrono::high_resolution_clock::now();
    _running = false;
}
/**
 * This method clears current time mesurement and starts a new one.
 *
 * @param values none 
 * @return none
 */
void Timer::restart() {
    stop();
    start();
}
/**
 * This method returns information if timer is currently running 
 *
 * @param values none 
 * @return true - timer is running, 
 *         false - false isn't running 
 */
bool Timer::isRunning() const {
    return _running;
}
/**
 * This method returns time in miliseconds between calling start() and stop().
 * If stop() was not yet called, returned time is mesured from calling start() to actual moment 
 *
 * @param values none 
 * @return time in miliseconds 
 */
unsigned long Timer::elapsedTimeMs() const {
    std::chrono::high_resolution_clock::time_point endTime;
    if (_running) endTime = std::chrono::high_resolution_clock::now();
    else  endTime = _stopTime;
    return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - _startTime).count();
}
/**
 * This method returns time in seconds between calling start() and stop().
 * If stop() was not yet called, returned time is mesured from calling start() to actual moment 
 *
 * @param values none 
 * @return time in seconds 
 */
unsigned long Timer::elapsedTimeS() const {
    std::chrono::high_resolution_clock::time_point endTime;
    if (_running) endTime = std::chrono::high_resolution_clock::now();
    else endTime = _stopTime;
    return std::chrono::duration_cast<std::chrono::seconds>(endTime - _startTime).count();
}
