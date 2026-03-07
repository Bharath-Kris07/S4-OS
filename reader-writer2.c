#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
sem_t mutex,wrt;
int data=0,readcount=0;
void *writer(void *arg){
    sem_wait(&wrt);
    data++;
    printf("Writing Data: %d\n",data);
    sleep(1);
    sem_post(&wrt);
    return NULL;
}
void *reader(void *arg){
    sem_wait(&mutex);
    readcount++;
    if(readcount==1) sem_wait(&wrt);
    sem_post(&mutex);
    printf("Reading Data: %d (Active Readers: %d)\n", data, readcount);
    sleep(1);
    sem_wait(&mutex);
    readcount--;
    if(readcount==0) sem_post(&wrt);
    sem_post(&mutex);
    return NULL;
}
int main(){
    pthread_t r[5],w[5];
    sem_init(&mutex,0,1);
    sem_init(&wrt,0,1);
    for(int i=0;i<5;i++){
        pthread_create(&w[i],NULL,writer,NULL);
        pthread_create(&r[i],NULL,reader,NULL);
    }
    for(int i=0;i<5;i++){
        pthread_join(w[i],NULL);
        pthread_join(r[i],NULL);
    }
    sem_destroy(&mutex);
    sem_destroy(&wrt);
    return 0;
}