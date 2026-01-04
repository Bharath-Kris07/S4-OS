#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
    pid_t pid = fork();
    if (pid < 0) exit(1);
    else if (pid > 0) {
        printf("Parent (PID: %d) terminating immediately...\n", getpid());
        exit(0);
    } else {
        printf("Child (PID: %d) running...\n", getpid());
        sleep(2);
        printf("Child (PID: %d) adopted by Init/Systemd (New PPID: %d)\n", getpid(), getppid());
    }
    return 0;
}