#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
int main() {
    int pipe_tube[2];
    double a, b, c, b_squared, ac, term_from_child, disc;
    pid_t pid;
    if (pipe(pipe_tube) == -1) {
        perror("pipe creation failed");
        return 1;
    }
    printf("Enter a, b, c: ");
    scanf("%lf %lf %lf", &a, &b, &c);
    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        return 1;
    }
    else if (pid == 0) {
        close(pipe_tube[0]); 
        printf("\n[Child] Calculating 4ac...\n");
        ac = 4 * a * c;
        write(pipe_tube[1], &ac, sizeof(double));
        close(pipe_tube[1]);
        exit(0);
    }  
    else {
        close(pipe_tube[1]); 
        b_squared = b * b;
        read(pipe_tube[0], &term_from_child, sizeof(double));
        disc = b_squared - term_from_child;
        if (disc < 0) {
            printf("\n[Parent] Discriminant is negative (imaginary roots).\n");
        } else {
            printf("\n[Parent] Discriminant: %lf\n", sqrt(disc));
        }
         close(pipe_tube[0]);
    }
    return 0;
}