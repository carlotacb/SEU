#include "mbed.h"

typedef struct {
  int value;
} message_t;

Mutex mutex;
const int queue_size = 10;
ConditionVariable cond(mutex);
MemoryPool<message_t, queue_size> mpool;
Queue<message_t, queue_size> queue;

Thread thread_producer_even;
Thread thread_producer_odd;
Thread thread_consumer_1;
Thread thread_consumer_2;

Serial pc(USBTX, USBRX, 115200);

int pointer = 0;
int countPar = 1;
int countImpar = 1;

void producer_even(){ 
    while (true) {
        mutex.lock(); 
        int par = countPar%2; 
        
        if(par==0){
            message_t *message = mpool.alloc();
            message->value = countPar;
            queue.put(message);
            printf("\nProducer even value %d \n", message->value);
            pointer++;
        }
        
        
        countPar++;
        
        while (pointer == queue_size){
            printf("\nThe queue is full, wait a consumer\n");
            cond.wait();
        }
            
        cond.notify_all();
        mutex.unlock(); 
    }
}

void producer_odd(){
    while (true) {
        mutex.lock(); 
        int impar = countImpar%2; 
        
        if(impar!=0){
            message_t *message = mpool.alloc();
            message->value = countImpar;
            queue.put(message);
            printf("\nProducer odd value %d \n", message->value);
            pointer++;
        }
        
        countImpar++;
        
        while (pointer == queue_size){
            printf("\nThe queue is full, wait a consumer\n");
            cond.wait();
        }
        
        cond.notify_all();
        mutex.unlock(); 
    }
}

void consumer_1(){
     while (true) {
        mutex.lock();
        
        while (pointer == 0){
            printf("\nThe queue is empty, wait for a producer.\n");
            cond.wait();
        }
            
        osEvent evt = queue.get();
        pointer--;
        
        if (evt.status == osEventMessage) {
            message_t *message = (message_t*)evt.value.p;
            printf("\nConsumer_1: Got value %.d .\n"   , message->value);
            mpool.free(message);
        }
        
        cond.notify_all();
        mutex.unlock();  
    }
}

void consumer_2(){
     while (true) {       
        mutex.lock();
        
        while (pointer == 0){
            printf("\nThe queue is empty, wait for a producer.\n");
            cond.wait();
        }
            
        osEvent evt = queue.get();
        pointer--;
        
        if (evt.status == osEventMessage) {
            message_t *message = (message_t*)evt.value.p;
            printf("\nConsumer_2: Got value %.d .\n"   , message->value);
            mpool.free(message);
        }
        
        cond.notify_all();
        mutex.unlock();
    }
}

int main () {
    thread_producer_even.start(&producer_even);
    thread_producer_odd.start(&producer_odd);
    thread_consumer_1.start(&consumer_1);
    thread_consumer_2.start(&consumer_2);
}
