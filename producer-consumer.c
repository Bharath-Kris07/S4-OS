#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#define BUFFER_SIZE 10
typedef struct {
    int id;
} item;
item buffer[BUFFER_SIZE];
volatile int in = 0;
volatile int out = 0; // volatile to prevent compiler optimizations that could cause issues in concurrent access and to always read the latest value from memory
void* producer(void* arg) {
    item next_produced;
    int item_counter = 1;
    while (item_counter <= 15) {
        next_produced.id = item_counter;
        usleep(100000); // 0.1 seconds to simulate production time
        while (((in + 1) % BUFFER_SIZE) == out);
        buffer[in] = next_produced;
        printf("Producer: Added Item %d at index %d\n", next_produced.id, in);
        in = (in + 1) % BUFFER_SIZE;
        item_counter++;
    }
    return NULL;
}
void* consumer(void* arg) {
    item next_consumed;
    int items_consumed = 0;
    while (items_consumed < 15) {
        while (in == out); 
        next_consumed = buffer[out];
        printf("Consumer: Removed Item %d from index %d\n", next_consumed.id, out);
        out = (out + 1) % BUFFER_SIZE;
        usleep(200000); // 0.2 seconds to simulate consumption time
        items_consumed++;
    }
    return NULL;
}
int main() {
    pthread_t prod_thread, cons_thread;
    printf("Starting Bounded Buffer (Size %d)\n", BUFFER_SIZE);
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);
    printf("\nFinished processing 15 items.\n");
    return 0;
}