#include "mbed.h"

PwmOut CH1(p21);
PwmOut CH2(p22);
AnalogIn input1(p15);
AnalogIn input2(p16);
Serial pc(USBTX, USBRX, 115200); 

int main() {
    
    CH1.period(1.0);
    CH2.period(1.0);     
 
    while(1) { 
        CH1.write(input1.read()); 
        CH2.write(input2.read());
        wait_ms(1.0); 
    }
}