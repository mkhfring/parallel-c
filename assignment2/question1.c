#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int runNumber = 1;
void run();
void addVec(int* C, int* A, int* B, int size);
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
    int* C = malloc(vSize * sizeof(int));

    if(NULL!=A && NULL!=B && NULL!=C){
        addVec(C, A, B, vSize);
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
void addVec(int* C, int* A, int* B, int size){
    clock_t start, end;
    double total;
    start = clock();
    for(int i=0; i<size; i++){
        C[i] = A[i] + B[i];
    }
    end = clock();
    total = (double)(end - start) / CLOCKS_PER_SEC ;
    printf("Sample run %d: (successful)\n\t", runNumber);
    for(int i=0; i < 10; i++){
        printf("%d ", C[i]);
    }
    printf("\n\tExecution time: %.3f ms\n\n", total * 1000);
    runNumber++;


}
/*
Sample run 1: (successful)
        0 0 0 0 0 0 0 0 0 0 
        Execution time: 195.412 ms

Sample run 2: (unsuccessful memory allocation) 
        Not enough memory.
*/
