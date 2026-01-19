#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#define MAX 100
typedef struct process {
    int pid, bt, at, prio, rt, ct, wt, tat;
} Process;
float avg_wt_fcfs, avg_wt_srtf, avg_wt_pri, avg_wt_rr;
void reset_processes(Process p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].rt = p[i].bt;
        p[i].ct = 0;
        p[i].wt = 0;
        p[i].tat = 0;
    }
}
void fcfs(Process p[], int n) {
    Process temp[MAX];
    for (int i = 0; i < n; i++) temp[i] = p[i];
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (temp[j].at > temp[j + 1].at) {
                Process t = temp[j]; temp[j] = temp[j + 1]; temp[j + 1] = t;
            }
        }
    }
    int current_time = 0;
    float total_wt = 0;
    printf("\n--- FCFS ---\n");
    for (int i = 0; i < n; i++) {
        if (current_time < temp[i].at) current_time = temp[i].at;
        temp[i].ct = current_time + temp[i].bt;
        temp[i].tat = temp[i].ct - temp[i].at;
        temp[i].wt = temp[i].tat - temp[i].bt;
        total_wt += temp[i].wt;
        current_time = temp[i].ct;
        printf("P%d: WT=%d\n", temp[i].pid, temp[i].wt);
    }
    avg_wt_fcfs = total_wt / n;
    printf("Avg WT: %.2f\n", avg_wt_fcfs);
}
int ShortestBT(Process p[], int n, int current_time) {
    int min_rt = INT_MAX;
    int shortest_index = -1;
    for (int i = 0; i < n; i++) {
        if (p[i].at <= current_time && p[i].rt > 0) {
            if (p[i].rt < min_rt) {
                min_rt = p[i].rt;
                shortest_index = i;
            }
        }
    }
    return shortest_index;
}
void srtf(Process p[], int n) {
    reset_processes(p, n);
    int current_time = 0;
    int completed = 0;
    float total_wt = 0;
    printf("\n--- SRTF ---\n");
    while (completed < n) {
        int s_index = ShortestBT(p, n, current_time);
        if (s_index == -1) {
            current_time++;
            continue;
        }
        p[s_index].rt--;
        current_time++;
        if (p[s_index].rt == 0) {
            completed++;
            int tat = current_time - p[s_index].at;
            p[s_index].wt = tat - p[s_index].bt;
            total_wt += p[s_index].wt;
            printf("P%d: WT=%d\n", p[s_index].pid, p[s_index].wt);
        }
    }
    avg_wt_srtf = total_wt / n;
    printf("Avg WT: %.2f\n", avg_wt_srtf);
}
int HighestPrio(Process p[],int n,int current_time,bool visited[]){
    int max_prio=-1,index=-1;
    for(int i=0;i<n;i++){
    if(p[i].at<=current_time && !visited[i]){
        if(p[i].prio>max_prio){
            index=i;
            max_prio=p[i].prio;
        }
        else if(max_prio==p[i].prio){
            if(index==-1|| p[i].at<p[index].at) index=i;
        }
    }
}
return index;
}
void priority_non_preemptive(Process p[], int n) {
    reset_processes(p, n);
    int current_time = 0;
    int completed = 0;
    float total_wt = 0;
    bool visited[MAX] = { false };
    printf("\n--- Priority ---\n");
    while (completed < n) {
        int idx = HighestPriority(p, n, current_time, visited);
        if (idx == -1) {
            current_time++;
            continue;
        }
        current_time += p[idx].bt;
        int tat = current_time - p[idx].at;
        p[idx].wt = tat - p[idx].bt;
        total_wt += p[idx].wt;
        visited[idx] = true;
        completed++;
        printf("P%d: WT=%d\n", p[idx].pid, p[idx].wt);
    }
    avg_wt_pri = total_wt / n;
    printf("Avg WT: %.2f\n", avg_wt_pri);
}
int main() {
    int n;
    Process p[MAX];
    printf("Enter number of processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("P%d (BT AT Pri): ", i + 1);
        scanf("%d %d %d", &p[i].bt, &p[i].at, &p[i].prio);
    }
    fcfs(p, n);
    srtf(p, n);
    priority_non_preemptive(p, n);
    //round_robin(p, n);
    printf("\n--- Result ---\n");
    float min_avg = avg_wt_fcfs;
    if (avg_wt_srtf < min_avg) min_avg = avg_wt_srtf;
    if (avg_wt_pri < min_avg) min_avg = avg_wt_pri;
    //if (avg_wt_rr < min_avg) min_avg = avg_wt_rr;
    printf("Minimum Average Waiting Time: %.2f\n", min_avg);
    return 0;
}