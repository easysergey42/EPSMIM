#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
// #define N 10
int N = 10;
int main(int argc, char** argv){

    if (argc > 1){
        int x = atoi(argv[1]);
        if (x) N = x;
    }

    FILE* f = fopen("binary", "wb");
    double* A = malloc(sizeof(double) * N*N);
    double x = 0.5;
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            // A[i*N + j] = (double) j / N;
            int r = i*i+j*j;
            A[i*N + j] = (i+j)%2;
        }
    }

    for (int i = 0; i < N; ++i){
        fwrite(A + (i*N), sizeof(double), N, f);
    }

    fclose(f);
    return 0;
}
