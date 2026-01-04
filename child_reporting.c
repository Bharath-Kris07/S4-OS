#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main() {
    int i;
    for (i = 1; i <= 5; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            printf("Child %d (PID: %d) reporting\n", i, getpid());
            exit(0);
        } else if (pid < 0) {
            perror("Fork failed");
            exit(1);
        }
    }
    for (i = 0; i < 5; i++) {
        wait(NULL);
    }
    printf("Parent: All 5 children completed successfully\n");
    return 0;
}