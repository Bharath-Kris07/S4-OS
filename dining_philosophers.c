#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define N 5 
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define LEFT (ph_num + 4) % N 
#define RIGHT (ph_num + 1) % N 
int state[N];        
sem_t mutex;         
sem_t S[N];          // One semaphore per philosopher (to block them if forks are busy)
void test(int ph_num) {
    if (state[ph_num] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
        state[ph_num] = EATING;
        sleep(2);
        printf("Philosopher %d takes fork %d and %d\n", ph_num + 1, LEFT + 1, ph_num + 1);
        printf("Philosopher %d is EATING\n", ph_num + 1);
        sem_post(&S[ph_num]); // to wake up the philosopher if they were waiting in take_fork()
    }
}
void take_fork(int ph_num) {
    sem_wait(&mutex);       
    state[ph_num] = HUNGRY;
    printf("Philosopher %d is Hungry\n", ph_num + 1);
    test(ph_num);           // Try to acquire two forks
    sem_post(&mutex);       
    sem_wait(&S[ph_num]);   // Block here if the philosopher couldn't get forks in test()
}
void put_fork(int ph_num) {
    sem_wait(&mutex);       
    state[ph_num] = THINKING;
    printf("Philosopher %d putting fork %d and %d down\n", ph_num + 1, LEFT + 1, ph_num + 1);
    printf("Philosopher %d is THINKING\n", ph_num + 1);
    test(LEFT);             // Check if Left neighbor was waiting 
    test(RIGHT);            // Check if Right neighbor was waiting 
    sem_post(&mutex);       
}
void* philosopher(void* num) {
    while (1) {
        int *i = num;
        sleep(1);           // thinking phase
        take_fork(*i);    
        sleep(1);           // eating phase
        put_fork(*i);     
    }
}
int main() {
    int i;
    pthread_t thread_id[N];
    int phil[N] = {0, 1, 2, 3, 4}; 
    sem_init(&mutex, 0, 1);
    for (i = 0; i < N; i++)
        sem_init(&S[i], 0, 0);
    for (i = 0; i < N; i++) {
        pthread_create(&thread_id[i], NULL, philosopher, &phil[i]);
        printf("Philosopher %d is THINKING\n", i + 1);
    }
    for (i = 0; i < N; i++) pthread_join(thread_id[i], NULL);
    sem_destroy(&mutex);
    for (i = 0; i < N; i++) sem_destroy(&S[i]);
    return 0;
}