#include "mbed.h"
#include "rtos.h"
 
DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
Thread thread;
 
void led2_thread() {
    
    led2 = !led2;
    while (true) {
        led2=!led2;
        led3=!led3;
        Thread::wait(1000);
    }
}
 
int main() {
    thread.start(led2_thread);
    while (true) {
        led1 = !led1;
        Thread::wait(300);
    }
}