#define _GNU_SOURCE // Required for syscall usage on Linux
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     
#include <sys/types.h>  
#include <sys/wait.h>  
#include <pthread.h>    
#include <sys/syscall.h> // For getting the actual kernel Thread ID (TID)
void *thread_task(void *arg) {
    int thread_num = *(int *)arg;
    pid_t tid = syscall(SYS_gettid);   
    printf("Thread %d of Child (TID: %d, PID: %d, PPID: %d)\n", 
           thread_num, tid, getpid(), getppid()); 
    pthread_exit(NULL);
} 
void child_logic(int child_num) {
    printf("Child %d (PID: %d) created\n", child_num, getpid());
    pthread_t t1, t2;
    int id1 = 1, id2 = 2;
    if (pthread_create(&t1, NULL, thread_task, &id1) != 0) {
        perror("Thread creation failed");
    }
    if (pthread_create(&t2, NULL, thread_task, &id2) != 0) {
        perror("Thread creation failed");
    }
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    exit(0); 
}
int main() {
    printf("Parent PID: %d\n\n", getpid());d
    pid_t pid1 = fork();
    if (pid1 == 0) {
        child_logic(1);
    } else if (pid1 > 0) {
        sleep(1); 
        pid_t pid2 = fork();
        if (pid2 == 0) {
            child_logic(2);
        } else if (pid2 > 0) {
            wait(NULL);
            wait(NULL); 
        } else {
            perror("Fork 2 failed");
        }
    } else {
        perror("Fork 1 failed");
    }
    return 0;
}