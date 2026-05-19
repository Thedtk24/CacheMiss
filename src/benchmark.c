#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define SIZE 4096

void row_comp(int mat[SIZE][SIZE], double res[SIZE][SIZE]){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            res[i][j] = sin(mat[i][j]);
        }
    }
}

void column_comp(int mat[SIZE][SIZE], double res[SIZE][SIZE]){
    for(int j = 0; j < SIZE; j++){
        for(int i = 0; i < SIZE; i++){
            res[i][j] = sin(mat[i][j]);
        }
    }
}

int mat[SIZE][SIZE];
double res[SIZE][SIZE];

int main(void){
    srand(time(NULL));
    struct timespec t0, t1;

    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            mat[i][j] = rand() % 10;
        }
    }


    // Time profiling for row computation

    clock_gettime(CLOCK_MONOTONIC, &t0);
    row_comp(mat, res);
    clock_gettime(CLOCK_MONOTONIC, &t1);

    double row_time = (t1.tv_sec - t0.tv_sec) * 1000.0 
                + (t1.tv_nsec - t0.tv_nsec) / 1e6;

    printf("row_comp:    %.3f ms\n", row_time);


    //Time profiling for column computation

    clock_gettime(CLOCK_MONOTONIC, &t0);
    column_comp(mat, res);
    clock_gettime(CLOCK_MONOTONIC, &t1);

    double col_time = (t1.tv_sec - t0.tv_sec) * 1000.0 
                + (t1.tv_nsec - t0.tv_nsec) / 1e6;

    printf("column_comp:    %.3f ms\n", col_time);

    return 0;
}