#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
int matrix[3][3];
int total_sum = 0;
struct {
    int value;
    int row;
    int col;
} max_element;
int trace_sum = 0;
void *calculate_sum(void *arg) {
    int sum = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            sum += matrix[i][j];
        }
    }
    total_sum = sum;
    pthread_exit(NULL);
}
void *find_max(void *arg) {
    int current_max = matrix[0][0];
    int r = 0, c = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (matrix[i][j] > current_max) {
                current_max = matrix[i][j];
                r = i;
                c = j;
            }
        }
    }
    max_element.value = current_max;
    max_element.row = r;
    max_element.col = c;
    pthread_exit(NULL);
}
void *calculate_trace(void *arg) {
    int sum = 0;
    for (int i = 0; i < 3; i++) 
        sum += matrix[i][i]; 
    trace_sum = sum;
    pthread_exit(NULL);
}
int main(int argc, char *argv[]) {
    if (argc != 10) {
        printf("Usage: ./program <9 integers>\n");
        return 1;
    }
    int k = 1; 
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrix[i][j] = atoi(argv[k]);
            k++;
        }
    }
    printf("\nInput Matrix:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    pthread_t threads[3];
    if (pthread_create(&threads[0], NULL, calculate_sum, NULL) != 0) {
        perror("Failed to create thread 1");
        return 1;
    }
    if (pthread_create(&threads[1], NULL, find_max, NULL) != 0) {
        perror("Failed to create thread 2");
        return 1;
    }
    if (pthread_create(&threads[2], NULL, calculate_trace, NULL) != 0) {
        perror("Failed to create thread 3");
        return 1;
    }
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("Thread 1: Sum of all elements = %d\n", total_sum);
    printf("Thread 2: Maximum element = %d at position (%d, %d)\n", max_element.value, max_element.row, max_element.col);
    printf("Thread 3: Trace (diagonal sum) = %d\n", trace_sum);
    printf("\nMain Thread: All calculations completed\n");
    return 0;
}