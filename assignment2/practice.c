#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

///Sequential Code
int* vecCreate(int);
///Parallelized Code
int* vecCreateOpenMP(int, int);

int main (int argc, char *argv[]){
    int count = 1;
    int num_thread = 4;
    int size = 700000000; ///1000000000

    clock_t start_t, end_t; ///start and end time
    double total_t;

    printf("Sample Run %d: ", count++);

    start_t = clock();
    int* v = vecCreate(size);

    end_t = clock();
    total_t = (double)(end_t - start_t) / (CLOCKS_PER_SEC/1000);

    if(v!=NULL){
        if(size%num_thread != 0)
            printf("(num_thread not divisible by size)\n\tUsing Serial Code\n\t");
        else
            printf("(Successfull)\n\tUsing Serial Code\n\t");
        printf("v[%d] = %d\n", size-1, v[size-1]);
        printf("\tExecution Time: %lf ms\n\n", total_t);
    }
    else{
        printf("(UnSuccessfull Memory Allocation)\n\tUsing Serial Code\n\t", count++);
        printf("Not Enough Memory\n");
    }

    free(v);

    if(size%num_thread != 0){
        printf("\tUsing OpenMP with %d threads:\n\t", num_thread);
        printf("Error: number of threads must be divisible by vector size.");
        exit(0);
    }
    else{
        start_t = clock();
        int* v = vecCreateOpenMP(size, num_thread);
        end_t = clock();
        total_t = (double)(end_t - start_t) / (CLOCKS_PER_SEC/1000);

        if(v!=NULL){
            printf("\tUsing OpenMP with %d threads:\n\t", num_thread);
            printf("v[%d] = %d\n", size-1, v[size-1]);
            printf("\tExecution Time: %lf ms\n", total_t);
        }
        else{
            printf("\tUsing OpenMP Code\n\t");
            printf("Not Enough Memory");
        }
    }
    free(v);

}

///Sequential Code
int* vecCreate(int size){
    int* A = (int*) malloc(size * sizeof(int));
    int i;
    if(A!=NULL)
        for(i=0;i<size;i++)
            A[i] = i;
    return A;
}

///Parallelized Code
int* vecCreateOpenMP(int size, int num_thread){
    int* A = (int*) malloc(size * sizeof(int));
    if(A!=NULL){
        # pragma omp parallel num_threads(num_thread)
        {
            int my_rank = omp_get_thread_num();

            int my_size = size / num_thread; /// # of contiguous trapezoids per thread
            int i;
            for(i=(my_size*my_rank); i<(my_size*my_rank)+my_size; i++){
                A[i] = i;
            }
        }
    }
    return A;
}


/** OUTPUT:
Sample Run 1: (Successfull)
        Using Serial Code
        v[49999999] = 49999999
        Execution Time: 92.000000 ms

        Using OpenMP with 4 threads:
        v[49999999] = 49999999
        Execution Time: 36.000000 ms

Sample Run 2: (num_thread not divisible by size)
        Using Serial Code
        v[49999999] = 49999999
        Execution Time: 93.000000 ms

        Using OpenMP with 3 threads:
        Error: number of threads must be divisible by vector size.

Sample Run 3: (UnSuccessfull Memory Allocation)
        Using Serial Code
        Not Enough Memory
        Using OpenMP Code
        Not Enough Memory


**/
