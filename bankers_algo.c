#include <stdio.h>
typedef struct process{
    int need[3],max[3],alloc[3],id,completed;
}process;
int main(){
    int m=3; // cols of resources
    int n,avail[3],count=0;
    printf("Enter the number of processes: ");
    scanf("%d",&n);
    int safe_seq[n];
    process p[n];
    for(int i=0;i<n;i++){
        p[i].id=i;
        p[i].completed=0;
        printf("Enter the allocated resources for process : %d",i);
        scanf("%d %d %d", &p[i].alloc[0], &p[i].alloc[1], &p[i].alloc[2]);
        printf("Enter the max resources for process : %d",i);
        scanf("%d %d %d", &p[i].max[0], &p[i].max[1], &p[i].max[2]);   
    }
    printf("Enter the available resource matrix : ");
    scanf("%d %d %d",&avail[0],&avail[1],&avail[2]);
    for(int i=0;i<n;i++)
        for(int j=0;j<3;j++) p[i].need[j]=p[i].max[j]-p[i].alloc[j];
    while(count<n){
        int progress=0;
        for(int i=0;i<n;i++){
            if(!p[i].completed){ // not completed
                int can_execute=1;
                for(int j=0;j<m;j++){ // for each resource column
                    if(p[i].need[j] > avail[j]){
                        can_execute=0;
                        break;
                    }
                }
                if(can_execute){
                    for(int j=0;j<m;j++) avail[j]+=p[i].alloc[j];
                    safe_seq[count++]=i;
                    p[i].completed=1;
                    progress=1;
                }
            }   
        }
        if(!progress) break;
    }
    if (count == n) {
        printf("\nSystem is in a SAFE state.\nSafe Sequence: ");
        for (int i = 0; i < n; i++) {
            printf("P%d ", safe_seq[i]);
            if (i != n - 1) printf("-> ");
        }
        printf("\n");
    } else 
        printf("\nDEADLOCK DETECTED! The system is NOT in a safe state.\n");
    return 0;
}