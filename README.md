# TimerCallback
## Descritpion 
TimerCallback class provides functionality of calling custom function in desired period of time for C++. It supports one-shot and periodic calls.
## Demo 
This listing shows sample usage of TimerCallback class.
```
#include <iostream>
#include <vector>
#include <mutex>
#include "timerCallback.h"

std::mutex mutex;
void textCallback(void *p);

int main() {
    /* timer callback class instances */
    TimerCallback tc1,tc2;
    /* register tc1 timer callback that will be called periodicly in period of 500ms */
    tc1.registerCallback(TimerMode::kPeriodic, 500UL, textCallback,
		         static_cast<void *>(new std::string("Periodic: passed string")));
    /* register tc2 timer callback that will be called onece after 2000ms */                                                            
    tc2.registerCallback(TimerMode::kOneShot, 2000UL, textCallback,
                         static_cast<void *>(new std::string("One shot: passed string")));
    /* run both callback threads */
    tc1.runCallbackThread();
    tc2.runCallbackThread();
    /* give callbacks some time to executed */
    std::this_thread::sleep_for(std::chrono::milliseconds(2100));
    /* stop tc1 callback thread */
    tc1.stopCallbackThread();
    /* unregister tc1 */
    tc1.unregisterCallback();
    /* register tc1 timer callback that will be called periodicly in period of 5000ms */
    tc1.registerCallback(TimerMode::kPeriodic,5000UL, textCallback,
                         static_cast<void *>(new std::string("Periodic: second passed string")));
    /* run both callback threads */
    tc1.runCallbackThread();
    tc2.runCallbackThread();
    /* give callbacks some time to executed */
    std::this_thread::sleep_for(std::chrono::milliseconds(21000));
    return 0;
}

void textCallback(void *p) {
    auto str = static_cast<std::string *>(p);
    mutex.lock();
    std::cout<<*str<<std::endl;
    mutex.unlock();
}
```
Sample code is provided in  ```demo.cpp ``` file.             
Detailed method descriptions are avaliable in ```src/timerCallback.cpp``` file.  
To run ```demo.cpp``` type:  
```
git clone https://github.com/BlackKnight905/TimerCallback
cd TimerCallback/
make
./demo
```


