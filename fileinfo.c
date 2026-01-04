#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // For isspace()
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./fileinfo <filename>\n");
        return 1;
    }
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }
    long size = 0;
    int lines = 0;
    int words = 0;
    int in_word = 0; // Boolean flag to track word boundaries
    char c;
    while ((c = fgetc(fp)) != EOF) {
        size++; // increase file size (bytes) for each character read
        if (c == '\n') {
            lines++;
        }
        if (isspace(c)) {
            in_word = 0;
        } 
        else if (in_word == 0) {
            in_word = 1;
            words++;
        }
    }
    fclose(fp);
    printf("\nFile Size: %ld bytes\n", size);
    printf("\nLines: %d\n", lines);
    printf("\nWords: %d\n", words);
    return 0;
}