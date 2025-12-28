#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> 
int main() {
    pid_t pid;
    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }
    else if (pid == 0) {
        sleep(1); 
        printf("Operating Systems Lab\n");
    }
    else {
        printf("PCCSL407 ");
        fflush(stdout);
        wait(NULL);
    }
    return 0;
}