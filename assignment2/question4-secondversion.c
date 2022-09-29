#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>

int runNumber = 1;
int* vecCreate (int size);
int* vecCreateOpenMP(int size, int num_thread);
void run(int size);
int main(int argc, char const *argv[])
{
    printf("Sample run %d: (successful)\n", runNumber);
    run(50);
    runNumber++;
    printf("Sample run %d: (num_thread not divisible by size)\n\n", runNumber);
    run(50);
    runNumber++;
    printf("Sample run %d: (unsuccessful memory allocation) \n", runNumber);
    run(1000000);

    /* code */
    return 0;
}
void run(int size){
    clock_t start_1, end_1, start_2, end_2;
    double total1, total2;
    long long int vsize = 1000000 * size;
    start_1 = clock();
    int* A = vecCreate(vsize);
    end_1 = clock();
    total1 = (double)(end_1 - start_1) / (CLOCKS_PER_SEC/1000);
    if (NULL == A){
        printf("\tNot enough memory. \n");
    }else{
    printf("\tUsing serial code\n");
    printf("\tv[%d] = %d\n", (vsize-1), A[vsize-1]);
    printf("\tTime: %.3f ms\n", total1);
    free(A);
    }
    start_2 = clock();
    int thread_num = (runNumber==2)?3:4;
    if((vsize % thread_num)!= 0 ){
        printf("\tUsing OpenMP with %d threads: Error: number of threads must be divisible by vector size. \n\n", thread_num);
    }
    else{
    int* B = vecCreateOpenMP(vsize, thread_num);
    end_2 = clock();
    total2 = (double)(end_2 - start_2) / (CLOCKS_PER_SEC/1000);
    if (NULL == B){
        printf("\tNot enough memory. \n");
    }else{
    printf("\tUsing OpenMP with 4 threads:\n");
    printf("\tv[%d] = %d\n", (vsize-1), B[vsize-1]);
    printf("\tTime: %.3f ms\n\n", total2);
    free(B);}
    }


}
int* vecCreate (int size){
    long long int vsize = size;
    int* A = malloc(vsize * sizeof(int));
    if (NULL == A){
        return A;
    }
    for (int i=0; i < vsize; i++){
        A[i] = i;
    }
    return A;
}
int* vecCreateOpenMP(int size, int num_thread){
    long long int vsize = size;
    int* B = malloc(vsize * sizeof(int));
    if (NULL == B){
        return B;
    }
    #pragma omp parallel num_threads(num_thread)
    {

    #pragma omp for
    for (int i=0; i < vsize; i++){
        B[i] = i;
    }
    }
    
    return B;
    
}

/*
Sample run 1: (successful)
        Using serial code
        v[49999999] = 49999999
        Time: 89.354 ms
        Using OpenMP with 4 threads:
        v[49999999] = 0
        Time: 59.394 ms

Sample run 2: (num_thread not divisible by size)

        Using serial code
        v[49999999] = 49999999
        Time: 78.465 ms
        Using OpenMP with 3 threads: Error: number of threads must be divisible by vector size. 

Sample run 3: (unsuccessful memory allocation) 
        Not enough memory. 
        Not enough memory. 
*/