#include "mbed.h"
#include "mbed_events.h"
 
Timer timer;
Timer t1;
Timer t2;
Timer t3;

EventQueue queue;
Serial pc(USBTX, USBRX, 115200);
 
void task1(int c, int d){
    t1.reset();
    t1.start();
    printf("task1: DeadLine %d s\r\n", d);
    wait_ms(c);
    float tex = t1.read_ms()/1000;
    
    if(tex > d){
        printf("task1: No se cumple el DeadLine %f s\r\n", tex);
    } else {
        printf("task1: Se cumple el DeadLine - Coste: %f s\r\n", tex);
    }
    
    t1.reset();
}

 
void task2(int c, int d){
    t2.reset();
    t2.start();
    printf("task2: DeadLine %d s\r\n", d);
    wait_ms(c);
    float tex = t2.read_ms()/1000;
    
    if(tex > d){
        printf("task2: No se cumple el DeadLine %f s\r\n", tex);
    } else {
        printf("task2: Se cumple el DeadLine - Coste: %f s\r\n", tex);
    }
    
    t2.reset();
}

void task3(int c, int d){
    t3.reset();
    t3.start();
    printf("task3: DeadLine %d s\r\n", d);
    wait_ms(c);
    float tex = t3.read_ms()/1000;
    
    if(tex > d){
    	printf("task3: No se cumple el DeadLine %f s\r\n", tex);
    } else {
    	printf("task3: Se cumple el DeadLine - Coste: %f s\r\n", tex);
    }
    
    t3.reset();
}
 
int main() {
    queue.call(task1, 100, 10);
    queue.call(task2, 300, 3);
    queue.call(task3, 400, 5);
    
    queue.call(task1, 200, 10);
    queue.call(task2, 400, 3);
    queue.call(task3, 300, 5);
    
    queue.call(task1, 300, 10);
    queue.call(task2, 200, 11);
    queue.call_in(1000, task3, 400, 8);
    
    queue.dispatch();
}