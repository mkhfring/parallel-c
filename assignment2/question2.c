#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int runNumber = 1;
void run();
int* addVec(int* A, int* B, int size);
int main(int argc, char const *argv[])
{
    run(50);
    run(1000000);
    /* code */
    return 0;
}
void run(int size){
    
    long long int vSize = 1000000 * size;
    int* A =  calloc(vSize, sizeof(int));
    int* B = calloc(vSize, sizeof(int));
    if(NULL!=A && NULL!=B){
        clock_t start, end;
        double total;
        start = clock();
        int* C = addVec(A, B, vSize);
        end = clock();
        if (NULL != C){
            printf("Sample run %d: (successful)\n\t", runNumber);
            for(int i=0; i < 10; i++){
                printf("%d ", C[i]);
            }
            total = (double)(end-start) / CLOCKS_PER_SEC;
            printf("\n\tExecution time: %.3f ms\n\n", total * 1000);
            runNumber++;
            free(A);
            free(B);
            free(C);
       }
       else{

          printf("Sample run %d: (unsuccessful memory allocation) \n", runNumber);
          printf("\tNot enough memory.\n");
          runNumber++;
       }
    }
    else{
        printf("Sample run %d: (unsuccessful memory allocation) \n", runNumber);
        printf("\tNot enough memory.\n");
        runNumber++;
    }


}
int* addVec(int* A, int* B, int size){
    clock_t start, end;
    int* C = calloc(size, sizeof(int));
    if (NULL != C){
        for (int i=0; i < size; i++){
            C[i] = *A + *B;
            A++;
            B++;
        }
        return C;

    }
    else{
        return C;
    }

}
/*
Sample run 1: (successful)
        0 0 0 0 0 0 0 0 0 0 
        Execution time: 225.402 ms

Sample run 2: (unsuccessful memory allocation) 
        Not enough memory.
*/