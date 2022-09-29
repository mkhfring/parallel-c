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
    printf("Sample run %d: (num_thread not divisible by size)\n", runNumber);
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
    if (NULL == B){
        printf("\tNot enough memory. \n");
    }else{
    
    
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
    int my_n, my_a, my_b;
    int* B = malloc(vsize * sizeof(int));
    if (NULL == B){
        return B;
    }
    double total = omp_get_wtime();
    #pragma omp parallel num_threads(num_thread)
    {
    
    int my_id = omp_get_thread_num();
    my_n = size / num_thread;
    my_a = my_id * my_n;
    my_b = my_a + my_n;
    for (int i=my_a; i < my_b; i++){
        B[i] = i;
    }
    
    }
    printf("\tUsing OpenMP with 4 threads:\n");
    total = omp_get_wtime() - total;
    printf("\tv[%d] = %d\n", (vsize-1), B[vsize-1]);
    printf("\tTime: %.3f ms\n\n", total*1000);
    return B;
    
}

/*
Sample run 1: (successful)
        Using serial code
        v[49999999] = 49999999
        Time: 80.478 ms
        Using OpenMP with 4 threads:
        v[49999999] = 49999999
        Time: 66.454 ms

Sample run 2: (num_thread not divisible by size)
        Using serial code
        v[49999999] = 49999999
        Time: 74.180 ms
        Using OpenMP with 3 threads: Error: number of threads must be divisible by vector size. 

Sample run 3: (unsuccessful memory allocation) 
        Not enough memory. 
        Not enough memory. 

*/