#include <stdio.h>
typedef struct process {
    int alloc[3], request[3], id, completed;
} process;
int main() {
    int m = 3; // cols of resources
    int n, avail[3], count = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    process p[n];
    for (int i = 0; i < n; i++) {
        p[i].id = i;
        p[i].completed = 0;
        printf("\nEnter the allocated resources for process %d: ", i);
        scanf("%d %d %d", &p[i].alloc[0], &p[i].alloc[1], &p[i].alloc[2]);
        printf("Enter the current REQUEST resources for process %d: ", i);
        scanf("%d %d %d", &p[i].request[0], &p[i].request[1], &p[i].request[2]);
        int has_alloc = 0;
        for(int j = 0; j < m; j++) {
            if(p[i].alloc[j] > 0) has_alloc = 1;
        }
        if(!has_alloc) {
            p[i].completed = 1; 
            count++; 
        }
    }
    printf("\nEnter the available resource matrix: ");
    scanf("%d %d %d", &avail[0], &avail[1], &avail[2]);
    int progress; 
    while (count < n) {
        progress = 0; 
        for (int i = 0; i < n; i++) {
            if (!p[i].completed) { 
                int can_execute = 1;
                for (int j = 0; j < m; j++) {
                    if (p[i].request[j] > avail[j]) {
                        can_execute = 0;
                        break;
                    }
                }
                if (can_execute) {
                    for (int j = 0; j < m; j++) avail[j] += p[i].alloc[j];
                    p[i].completed = 1;
                    count++;
                    progress = 1; 
                }
            }   
        }
        if (!progress) break; 
    }
    if (count == n) {
        printf("\nResult: System is NOT deadlocked.\n");
    } else {
        printf("\nResult: DEADLOCK DETECTED!\n");
        printf("The following processes are deadlocked: ");
        for (int i = 0; i < n; i++) {
            if (!p[i].completed) {
                printf("P%d ", p[i].id);
            }
        }
        printf("\n");
    }
    return 0;
}