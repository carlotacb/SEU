#include "mbed.h"

DigitalIn enable(p17);
DigitalOut led(LED1);
Timer t;

int main() {
            
        while(1) { 
             
        t.start();           
        while(enable){  
                    
             if(t.read_ms() >= 500){
                 led = !led;
                 t.stop();
                 t.reset();              
             }
             
             wait(0.25);
       }  
    }
}