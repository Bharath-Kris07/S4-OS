#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
struct note{
    long type;
    char text[100];
};
int main(){
    struct note note;
    int queue_id;
    queue_id=msgget(IPC_PRIVATE,0666 | IPC_CREAT);
    if(queue_id==-1){
        perror("creating queue failed");
        return 1;
    }
    pid_t pid=fork();
    if(pid<0){
        perror("error forking");
        return 1;
    }else if(pid==0){
        msgrcv(queue_id,&note,sizeof(note.text),1,0);
        printf("\n[Child] I received: %s\n", note.text);
        int len=strlen(note.text);
        char temp;
        for(int i=0;i<len/2;i++){
            temp=note.text[i];
            note.text[i]=note.text[len-1-i];
            note.text[len-1-i]=temp;
        }
        printf("[Child] Reversed to %s\n",note.text);
        note.type=2;
        msgsnd(queue_id,&note,sizeof(note.text),0);
    }else{
        char string[100];
        printf("\n enter the string: ");
        scanf("%s", string);
        note.type=1;
        strcpy(note.text,string);
        msgsnd(queue_id,&note,sizeof(note.text),0);
        msgrcv(queue_id,&note,sizeof(note.text),2,0);
        printf("\n [Parent] received : %s\n",note.text);
        if(strcmp(note.text,string)==0)
            puts("it is palindrome");
        else
            puts("not palindrome");
        msgctl(queue_id,IPC_RMID,NULL);
    }
    return 0;
}