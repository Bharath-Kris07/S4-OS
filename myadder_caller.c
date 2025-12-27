#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(){
    pid_t pid=fork();
    if(pid<0){
        perror("fork failed");
        return 1;
    }
    else if(pid==0){
        puts("Child process(executing myadder now)");
        char* args[]={"./myadder","60","40",NULL};
        execvp("./myadder",args);
        perror("execution failed");
    }
    else{
        puts("Parent process : waiting for child to finish");
        wait(NULL);
        puts("child execution completed");
    }
    return 0;
}