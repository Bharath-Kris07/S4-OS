#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main() {
    printf("Process A (PID: %d): Starting chain\n", getpid());
    pid_t pid_b = fork();
    if (pid_b < 0) {
        perror("Fork B failed");
        exit(1);
    } 
    else if (pid_b == 0) {
        pid_t pid_c = fork();
        if (pid_c < 0) {
            perror("Fork C failed");
            exit(1);
        }
        else if (pid_c == 0) {
            printf("Process C (PID: %d): Executing ls -l\n\n", getpid());
            execlp("ls", "ls", "-l", NULL);
            perror("execlp ls failed");
            exit(1);
        }
        else {
            wait(NULL); 
            printf("\nProcess B (PID: %d): Executing pwd\n\n", getpid());
            execlp("pwd", "pwd", NULL);
            perror("execlp pwd failed");
            exit(1);
        }
    } 
    else {
        wait(NULL);
        printf("\nProcess A: All processes completed\n");
    }
    return 0;
}