#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}
void sstf(int *req, int n, int start) {
    int total = 0, current = start, count = 0;
    int visited[10] = {0};
    while (count < n) {
        int min = 5001, index = -1;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && abs(req[i] - current) < min) {
                min = abs(req[i] - current);
                index = i;
            }
        }
        visited[index] = 1;
        total += min;
        current = req[index];
        count++;
    }
    printf("SSTF Total Movement: %d\n", total);
}
void look(int *req, int n, int start) {
    int sorted[n], total = 0, current = start, split = -1;
    for (int i = 0; i < n; i++) sorted[i] = req[i];
    qsort(sorted, n, sizeof(int), compare);
    for (int i = 0; i < n; i++) if (sorted[i] >= start) { split = i; break; }
    if (split != -1) {
        for (int i = split; i < n; i++) { total += abs(sorted[i] - current); current = sorted[i]; }
        for (int i = split - 1; i >= 0; i--) { total += abs(sorted[i] - current); current = sorted[i]; }
    } else {
        for (int i = n - 1; i >= 0; i--) { total += abs(sorted[i] - current); current = sorted[i]; }
    }
    printf("LOOK Total Movement: %d\n", total);
}
void cscan(int *req, int n, int start) {
    int sorted [n], total = 0, current = start, split = -1;
    for (int i = 0; i < n; i++) sorted[i] = req[i];
    qsort(sorted, n, sizeof(int), compare);
    for (int i = 0; i < n; i++) if (sorted[i] >= start) { split = i; break; }
    if (split != -1) {
        total += abs(4999 - current); 
        total += 4999; // Jump to 0
        current = 0;
        for (int i = 0; i < split; i++) { total += abs(sorted[i] - current); current = sorted[i]; }
    } else {
        total += abs(4999 - current) + 4999 + sorted[n-1];
    }
    printf("C-SCAN Total Movement: %d\n", total);
}
int main(int argc, char *argv[]) {
    if (argc != 2) return 1;
    int start = atoi(argv[1]);
    int req[10];
    srand(time(NULL));
    printf("Requests: ");
    for (int i = 0; i < 10; i++) {
        req[i] = rand() % 5000;
        printf("%d ", req[i]);
    }
    printf("\n---\n");
    sstf(req, 10, start);
    look(req, 10, start);
    cscan(req, 10, start);
    return 0;
}