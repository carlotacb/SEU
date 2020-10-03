#include "mbed.h"

DigitalIn enable(p17);
DigitalOut myled(LED1);

int main() {

    while(1) {
         if(enable) {
             myled = !myled;
             }

            wait(0.25);
    }
}