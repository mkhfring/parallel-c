%%cu

// CUDA Implementation goes here!
#include <stdio.h>
#include <stdio.h>
#include <time.h>
#include "cuda_runtime.h"
#define MaxThreads 1024
#define CHK(call) {cudaError_t err = call; if (err != cudaSuccess) { printf("Error%d: %s:%d\n",err,__FILE__,__LINE__); printf(cudaGetErrorString(err)); cudaDeviceReset(); exit(1);}}


__global__ void vector_init(double *arr, int size);
int main(){
    clock_t start, end;
    double *a, *d_a;
    const int n = 10000000;
    int block_number = (int) (n-1)/ MaxThreads + 1;
    a = (double*) malloc(n * sizeof(double));
    if (NULL == a){
        printf("enable to allocate memory");
        exit(0);
    }
    CHK(cudaMalloc(&d_a, n *sizeof(double));)
    start = clock();
    vector_init<<<block_number, MaxThreads>>>(d_a, n);
    cudaMemcpy(a, d_a, n * sizeof(double), cudaMemcpyDeviceToHost);
    end = clock();
    double total_time = ((double) (end - start)) / CLOCKS_PER_SEC; 
    printf("The total time to execute the serial code is %.3f \n", total_time );
    for (int i=0; i<5; i++){
        printf("a[%d]: %.7f \n", i, a[i]);
    }
    printf("....\n");
    for (int i=n-5; i<n; i++){
        printf("a[%d]: %.7f \n", i, a[i]);
    }


}
__global__ void vector_init(double *arr, int size){
    int i = blockDim.x * blockIdx.x + threadIdx.x;
    if(i < size){
        double val = (double) i / size;
        arr[i] = val;
    }
}

/*
The total time to execute the serial code is 0.053 
a[0]: 0.0000000 
a[1]: 0.0000001 
a[2]: 0.0000002 
a[3]: 0.0000003 
a[4]: 0.0000004 
....
a[9999995]: 0.9999995 
a[9999996]: 0.9999996 
a[9999997]: 0.9999997 
a[9999998]: 0.9999998 
a[9999999]: 0.9999999 
*/