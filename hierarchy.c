#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main() {
    pid_t child1 = fork();
    if (child1 < 0) {
        exit(1);
    }
    if (child1 == 0) {
        printf("First Child Process\n");
        pid_t grandchild = fork();
        if (grandchild < 0) {
            exit(1);
        }
        if (grandchild == 0) {
            printf("Grandchild Process\n");
            exit(0);
        } else {
            wait(NULL);
            exit(0);
        }
    } else {
        wait(NULL);
        pid_t child2 = fork();
        if (child2 < 0) {
            exit(1);
        }
        if (child2 == 0) {
            printf("Second Child Process\n");
            exit(0);
        } else {
            wait(NULL);
            printf("Parent Process: All children completed\n");
        }
    }
    return 0;
}