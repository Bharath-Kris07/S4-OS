#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main(){
    pid_t t;
    t=fork();
    if(t<0){
        fprintf(stderr,"fork failed");
        return 1;
    }
    else if(t==0){
        puts("inside child process");
        execlp("/bin/ls","ls",NULL);
    }
    else{
        puts("inside parent process");
        wait(NULL);
        puts("child complete");
        sleep(6000);
        return 0;
    }
}