/*
 * CSV Grade Book
 *
 * Reads grades.csv, one student per line in the format
 * name,score1,score2,score3, and prints each student's average.
 */

#include <stdio.h>
#include <string.h>

int main(void) {
    FILE *fp = fopen("grades.csv", "r");
    char line[256];
    char name[100];
    int score1, score2, score3;

    if (fp == NULL) {
        printf("Error: grades.csv not found\n");
        return 1;
    }

    while (fgets(line, sizeof(line), fp) != NULL) {
        if (sscanf(line, " %99[^,],%d,%d,%d", name, &score1, &score2, &score3) == 4) {
            printf("%s average: %.1f\n", name, (score1 + score2 + score3) / 3.0);
        } else {
            printf("Invalid line\n");
        }
    }

    fclose(fp);
    return 0;
}
