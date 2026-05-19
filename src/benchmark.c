#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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
    if(argc < 2) {
        printf("Usage : %s <SIZE>\n", argv[0]);
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

    clock_gettime(CLOCK_MONOTONIC, &t0);
    row_comp(mat, res, size);
    clock_gettime(CLOCK_MONOTONIC, &t1);
    double row_time = (t1.tv_sec - t0.tv_sec) * 1000.0
                    + (t1.tv_nsec - t0.tv_nsec) / 1e6;

    clock_gettime(CLOCK_MONOTONIC, &t0);
    column_comp(mat, res, size);
    clock_gettime(CLOCK_MONOTONIC, &t1);
    double col_time = (t1.tv_sec - t0.tv_sec) * 1000.0
                    + (t1.tv_nsec - t0.tv_nsec) / 1e6;

    printf("%d,%.3f,%.3f\n", size, row_time, col_time);

    free(mat);
    free(res);
    return 0;
}