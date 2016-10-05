#include<math.h>
#include<stdio.h>


int main(int argc, char* argv[]){
    int i,j;
    int n_loop;

    if(argc<2){
        printf("usage : ./sqrt n_loop\n");
    }

    n_loop = atoi(argv[1]);

    for(i=0;i<n_loop;i++){
        sqrt(i*i+0.1*i);
    }

    return 0;
}
