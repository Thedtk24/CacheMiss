#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

void row_comp(int *mat, double *res, int size) {
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            res[i * size + j] = sin(mat[i * size + j]);
}

void column_comp(int *mat, double *res, int size) {
    for(int j = 0; j < size; j++)
        for(int i = 0; i < size; i++)
            res[i * size + j] = sin(mat[i * size + j]);
}

int main(int argc, char *argv[]) {
    if(argc < 3) {
        printf("Usage : %s <SIZE> <row|col>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int size = atoi(argv[1]);

    int    *mat = malloc(size * size * sizeof(int));
    double *res = malloc(size * size * sizeof(double));

    if(!mat || !res) {
        fprintf(stderr, "Allocation failed\n");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));
    for(int i = 0; i < size * size; i++)
        mat[i] = rand() % 10;

    struct timespec t0, t1;

    if(strcmp(argv[2], "row") == 0) {
        clock_gettime(CLOCK_MONOTONIC, &t0);
        row_comp(mat, res, size);
        clock_gettime(CLOCK_MONOTONIC, &t1);
    } else {
        clock_gettime(CLOCK_MONOTONIC, &t0);
        column_comp(mat, res, size);
        clock_gettime(CLOCK_MONOTONIC, &t1);
    }

    double elapsed = (t1.tv_sec - t0.tv_sec) * 1000.0
                   + (t1.tv_nsec - t0.tv_nsec) / 1e6;

    printf("%s %d: %.3f ms\n", argv[2], size, elapsed);

    free(mat);
    free(res);
    return 0;
}