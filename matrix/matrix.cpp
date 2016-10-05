#include<cmath>
#include<cstdlib>
#include<stdio.h>
#include<stdint.h>
int main(int argc, char* argv[]){

    if(argc < 2){
        printf("Usage : ./matrix width_of_square_matrix\n");
    }
    uint32_t width = atoi(argv[1]);

    double *A = (double*) malloc(width*width*sizeof(double));
    double *B = (double*) malloc(width*width*sizeof(double));
    double *C = (double*) malloc(width*width*sizeof(double));


    for(int i=0; i<width*width; i++){
        A[i] = 3.14159*(rand()%100);
        B[i] = 0.14159*(rand()%100);
        C[i] = 0;
    }

    for(int i=0; i<width; i++){
        for(int j=0; j<width; j++){
            for(int k=0; k<width; k++){
                C[ i*width + j ] += A[ i*width + k ] * B[ k*width + j ] ;
            }
        }
    }

    FILE *f_log = fopen("matrix.log","w");
    for(int i=0; i<width*width; i++){
        fprintf(f_log,"A[%d] %lf\n",i,A[i]);
        fprintf(f_log,"B[%d] %lf\n",i,B[i]);
        fprintf(f_log,"C[%d] %lf\n",i,C[i]);
    }
    fclose(f_log);
    if(A){ free(A); };
    if(B){ free(B); };
    if(C){ free(C); };

    return 0;
}
