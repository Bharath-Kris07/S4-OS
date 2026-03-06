#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <ctype.h>
struct shared_data{
    int status;
    char str1[100];
    char str2[200];
    char str3[100];
    char res[300];
};
int main(){
    pid_t t;
    int shm_id;
    struct shared_data *shm_pointer;
    shm_id=shmget(IPC_PRIVATE,sizeof(struct shared_data),0666 | IPC_CREAT);
    if (shm_id < 0) {
        perror("shmget failed");
        return 1;
    }
    shm_pointer=(struct shared_data*)(shmat(shm_id,NULL,0));
    if(shm_pointer==(void*)-1){
        perror("shm failed");
        return 1;
    }
    shm_pointer->status=0;
    t=fork();
    if(t<0){
        perror("fork failed");
        return 1;
    }
    else if(t==0){
        while(shm_pointer->status==0) sleep(1);
        printf("[CHILD] received 3 strings..concatenating now..\n");
        sprintf(shm_pointer->res,"%s %s %s",shm_pointer->str1,shm_pointer->str2,shm_pointer->str3);
        shm_pointer->status=2;
        shmdt(shm_pointer);
        exit(0);
    }
    else{
        printf("Enter string 1: ");
        scanf("%s", shm_pointer->str1);
        printf("Enter string 2: ");
        scanf("%s", shm_pointer->str2);
        printf("Enter string 3: ");
        scanf("%s", shm_pointer->str3);
        shm_pointer->status = 1;
        while (shm_pointer->status != 2) sleep(1);
        printf("\n[PARENT] Received concatenated string: %s\n", shm_pointer->res);
        for (int i = 0; shm_pointer->res[i] != '\0'; i++) {
            if (islower(shm_pointer->res[i])) {
                shm_pointer->res[i] = toupper(shm_pointer->res[i]);
            } else if (isupper(shm_pointer->res[i])) {
                shm_pointer->res[i] = tolower(shm_pointer->res[i]);
            }
        }
        printf("[PARENT] Flipped Case Output: %s\n", shm_pointer->res);
        wait(NULL);
        shmdt(shm_pointer);
        shmctl(shm_id, IPC_RMID, NULL);
    }
    return 0;
}