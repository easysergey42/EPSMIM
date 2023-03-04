#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
// #define N 10
typedef float mtype;
int N = 10;

int main(int argc, char** argv){

    if (argc > 1){
        int x = atoi(argv[1]);
        if (x) N = x;
    }
    
    FILE* f = fopen("binary", "rb");
    mtype* A = malloc(sizeof(mtype) * N*N);

    for (int i = 0; i < N; ++i){
        fread(A+i*N, sizeof(mtype), N, f);
    }

    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
           printf("%lf ",A[i*N + j]);
        }
        printf("\n");
    }

    fclose(f);
    return 0;
}