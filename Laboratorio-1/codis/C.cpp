#include "mbed.h"

DigitalIn enable(p17);
DigitalOut led(LED1);
Timer t;
Timer t2;
Timer t3;
bool flag = false;

int main() {
	while(1) { 
		t.reset();     
		t.start();
		t2.reset();           
		
		while(enable){  
            while(t.read_ms() >= 500){        
                t2.start();                 		 
                while(t2.read_ms() < 10000){                   
					led = 1;
                    wait(0.1);
                    led = 0;
                    wait(0.1);
                    if(!enable) {
                        flag=true;
                    }
                    while(flag && enable){                        
                        t3.start();                        
                        while(t3.read_ms() >= 500){  
                            led = 0;                      
                        }
                    }    
                } 
                led = 0;
            }
            wait(0.25);
		}  
    }
}