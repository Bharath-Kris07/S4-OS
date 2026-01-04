#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
int nums[20];
int partial_sums[4];
void *sum_part(void *arg) {
    int thread_id = *(int *)arg;
    int start = thread_id * 5;
    int end = start + 5;
    int sum = 0;
    int i;
    for (i = start; i < end; i++) {
        sum += nums[i];
    }
    partial_sums[thread_id] = sum;
    printf("Thread %d (elements %d-%d): Sum = %d\n", thread_id + 1, start + 1, end, sum);
    pthread_exit(NULL);
}
int main(int argc, char *argv[]) {
    if (argc != 21) {
        printf("Usage: ./array_sum <20 integers>\n");
        return 1;
    }
    int i;
    for (i = 0; i < 20; i++) {
        nums[i] = atoi(argv[i + 1]);
    }
    printf("Array: ");
    for (i = 0; i < 20; i++) printf("%d ", nums[i]);
    printf("\n\n");
    pthread_t threads[4];
    int thread_ids[4];
    for (i = 0; i < 4; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, sum_part, &thread_ids[i]);
    }
    int total_sum = 0;
    for (i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
        total_sum += partial_sums[i];
    }
    printf("\nTotal Sum: %d\n", total_sum);
    return 0;
}