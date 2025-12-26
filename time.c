#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
int main(){
    volatile long i;
    int j;
    time_t t;
    pid_t pid=getpid();
    time(&t);
    printf("The current system time is %s\n",ctime(&t));
    printf("The process id is %d\n",pid);
    puts("Doing some work(User mode)");
    for(i=0;i<1000000000;i++);
    puts("Doing some work(Kernel mode)");
    for(j=0;j<5000000;j++) getpid();
    puts("Sleeping for 6000 seconds");
    printf("Run this command now:  cat /proc/%d/stat\n",pid);
    sleep(6000);
    return 0;
}