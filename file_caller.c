#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main() {
    char filename[100];
    printf("Enter filename to analyze: ");
    scanf("%s", filename);
    printf("\nParent: Creating child process...\n");
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } 
    else if (pid == 0) {
        printf("\nChild: Analyzing file %s...\n", filename);
        char *args[] = {"./fileinfo", filename, NULL};
        execvp("./fileinfo", args);
        perror("execvp failed");
        exit(1);
    } 
    else {
        wait(NULL);
        printf("\nParent: Analysis complete\n");
    }
    return 0;
}