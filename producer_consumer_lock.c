#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#define buffer_size 10
typedef struct process {
    int id;
} item;
item buffer[buffer_size];
int out = 0, in = 0;
sem_t empty, full, mutex;
void* producer(void *param) {
    item next_produced;
    int item_counter = 1;
    while(item_counter <= 15) {
        next_produced.id = item_counter; 
        usleep(100000);
        sem_wait(&empty);
        sem_wait(&mutex);
        buffer[in] = next_produced;
        printf("Producer: Added Item %d at index %d\n", next_produced.id, in);
        in = (in + 1) % buffer_size;
        sem_post(&mutex);
        sem_post(&full);
        item_counter++; 
    }
    return NULL;
}
void* consumer(void* param) {
    item next_consumed;
    int item_consumed = 0; 
    while(item_consumed < 15) {
        sem_wait(&full);
        sem_wait(&mutex);
        next_consumed = buffer[out];
        printf("Consumer : Consumed Item %d at index %d\n", next_consumed.id, out);
        out = (out + 1) % buffer_size;
        sem_post(&mutex);
        sem_post(&empty);
        item_consumed++; 
    }
    return NULL;
}
int main() {
    pthread_t con, pro;
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, buffer_size); 
    sem_init(&full, 0, 0);
    printf("Starting Bounded buffer...\n");
    pthread_create(&pro, NULL, producer, NULL);
    pthread_create(&con, NULL, consumer, NULL);
    pthread_join(pro, NULL);
    pthread_join(con, NULL);  
    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    return 0;
}