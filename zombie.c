#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main() {
    pid_t pid = fork();
    if (pid < 0) exit(1);
    else if (pid == 0) {
        printf("Child (PID: %d) terminating...\n", getpid());
        exit(0);
    } else {
        printf("Parent: Sleeping for 25 seconds (child becomes zombie)\n");
        printf("Use 'ps aux | grep Z' in another terminal to see zombie\n");
        sleep(25);
        wait(NULL);
        printf("Parent: Now calling wait() to reap zombie\n");
        printf("Child reaped successfully\n");
    }
    return 0;
}