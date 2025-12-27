#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
int main() {
    pid_t pid;
    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    }
    else if (pid == 0) {
        // getpid() = My ID, getppid() = Parent's ID
        printf("Child Process:  PID = %d (My Parent is %d)\n", getpid(), getppid());
        sleep(80); 
    }
    else {
        printf("Parent Process: PID = %d (I created Child %d)\n", getpid(), pid);
        // cat /proc/[proc id]/stat | awk '{print"User mode: ",$14,"\n Kernel mode: ",$15}'
        sleep(80);
    }
    return 0;
}