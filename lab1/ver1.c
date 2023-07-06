#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#define DEFAULT_NX 10
#define DEFAULT_NY 10
#define DEFAULT_NT 10
int Nx = DEFAULT_NX, Ny = DEFAULT_NY, Nt = DEFAULT_NT;
float Xb = 4.0, Xa = 0, Yb = 4.0, Ya = 0, hx = 4.0/(DEFAULT_NX - 1), hy = 4.0/(DEFAULT_NY - 1);

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define SQR(x) ((x)*(x))
#define ABS(x) ((x<0)?(-x) : (x))
#define SWAP(x, y, T) do { T SWAP = x; x = y; y = SWAP; } while (0)

void init_values(int argc, char** argv){
    if (argc == 2){
        int x = atoi(argv[1]);
        if (x){
            Nx = Ny = x;
        }
        return;
    }
    else if (argc == 3){
        int x = atoi(argv[1]);
        int y = atoi(argv[2]);
        if (x) Nx = x;
        if (y) Ny = y;
        return;
    }
    else if (argc == 4){
        int x = atoi(argv[1]);
        int y = atoi(argv[2]);
        int t = atoi(argv[3]);
        if (x) Nx = x;
        if (y) Ny = y;
        if (t) Nt = t;
        return;
    }
}

void fill_rho(float* rho){
    float Xs1 = Xa + (Xb - Xa) / 3;
    float Ys1 = Ya + (Yb - Ya) * 2 / 3;
    float Xs2 = Xa + (Xb - Xa) * 2 / 3;
    float Ys2 = Ya + (Yb - Ya) / 3;
    float R =  0.1 * MIN(Xb-Xa, Yb-Ya);
    
    for (int i = 0; i < Ny; ++i){
        float Yi = Ya + hy * i;
        for (int j = 0; j < Nx; ++j){
            float Xj = Xa + hx * j;
            if (SQR(Xj-Xs1) + SQR(Yi-Ys1) < SQR(R)) rho[i*Nx + j] = 0.1;
            else if (SQR(Xj-Xs2) + SQR(Yi-Ys2) < SQR(R)) rho[i*Nx + j] = -0.1;
            else rho[i*Nx + j] = 0.0;
        }
    }
}


int main(int argc, char** argv){

    init_values(argc, argv);

    printf("Nx = %d\tNy = %d\tNt = %d\n", Nx, Ny, Nt);

    hx = (Xb - Xa)/(Nx - 1);
    hy = (Yb - Ya)/(Ny - 1);
    
    float* rho = malloc(sizeof(float) * Nx * Ny);
    float* Phi = calloc(Nx * Ny, sizeof(float));
    float* Phi_next = calloc(Nx * Ny, sizeof(float));

    fill_rho(rho);

//ITERATIONS:

    float A = 1.0 / SQR(hx);
    float B = 1.0 / SQR(hy);
    float delta = 0;

    for (int k = 0; k < Nt; ++k){

        float olddelta = delta;
        delta = 0;

        for (int i = 1; i < Ny-1; ++i){
            for (int j = 1; j < Nx-1; ++j){

                Phi_next[i*Nx+j] = 1 / (5 * (A+B)) * ( 0.5*(5*A - B)*(Phi[i*Nx+j-1] + Phi[i*Nx+j+1]) + 0.5*(5*B - A)*(Phi[(i-1)*Nx+j] + Phi[(i+1)*Nx+j]) + \
                    0.25*(A+B)*(Phi[i*Nx+j-1] + Phi[i*Nx+j+1] + Phi[(i-1)*Nx+j] + Phi[(i+1)*Nx+j]) + 2*rho[i*Nx+j] + \
                    0.25*(rho[i*Nx+j-1] + rho[i*Nx+j+1] + rho[(i-1)*Nx+j] + rho[(i+1)*Nx+j]));
                
                if (ABS(Phi[i*Nx+j] - Phi_next[i*Nx+j]) > delta) delta = ABS(Phi[i*Nx+j] - Phi_next[i*Nx+j]);
            }
        }

        if (delta - olddelta > 0.000001  && k != 0){
            printf("Delta raised on %d iteration: %f -> %f\n", k+1, olddelta, delta);
        }

        SWAP(Phi, Phi_next, float*);
    }

    FILE* f = fopen("binary", "wb");
    for (int i = 0; i < Ny; ++i){
        fwrite(Phi + (i*Nx), sizeof(float), Nx, f);
    }

    fclose(f);
    free(rho);
    free(Phi);

    return 0;
}
