#include "mbed.h"
#include "rtos.h"

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);

Thread threadNormal;
Thread threadHigh;

Mutex mutex;
 
void led(DigitalOut led, uint32_t t) {
    mutex.lock();
    Thread::wait(t);
    led=!led;
    mutex.unlock();   
}
 
void led2_thread() {
    while (true) {
        led(led2,10000);
    }
}

void led3_thread() {  
    while (true) {
        led(led3,1000);
    }
}

int main() {
    
    threadHigh.set_priority(osPriorityHigh);
    threadHigh.start(led3_thread);
    threadNormal.start(led2_thread);
    
    osThreadSetPriority(osThreadGetId(), osPriorityLow);
    
    while (true) {
    led(led1,10);
    }   
}
