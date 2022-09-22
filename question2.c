#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int runNumber = 1;
void computeTheSum();
int main(int argc, char const *argv[])
{

    computeTheSum(1);
    computeTheSum(10);
    computeTheSum(50);
    computeTheSum(100);
    computeTheSum(1000000);


    /* code */
    return 0;
}
void computeTheSum(int size){
    clock_t start, end;
    double total;
    long long int vSize = 1000000 * size;
    int n;
    int sum = 0;
    int* A = (int*) malloc(vSize * sizeof(int));
    int* B = (int*) malloc(vSize * sizeof(int));
    int* C = (int*) malloc(vSize * sizeof(int));
    start = clock();
    if(NULL!=A && NULL!=B && NULL!=C){
        for(int i=0; i<vSize; i++){
            A[i] = i * 3;
            B[i] = -i * 3;
            C[i] = A[i] + B[i];
            sum += C[i];
        }
        end = clock();
        total = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Sample run %d: (successful) \n\tSum: %d \n",runNumber, sum);
        printf("\tThe execution time: %.2f sec\n", total);
        runNumber++;

    }
    else{
        printf("Sample run %d: (unsuccessful memory allocation) \n", runNumber);
        printf("\tNot enough memory.\n");
        runNumber++;
    }

}
/**
 Sample run 1: (successful) 
        Sum: 0 
        The execution time: 0.00 sec
Sample run 2: (successful) 
        Sum: 0 
        The execution time: 0.04 sec
Sample run 3: (successful) 
        Sum: 0 
        The execution time: 0.18 sec
Sample run 4: (successful) 
        Sum: 0 
        The execution time: 0.35 sec
Sample run 5: (unsuccessful memory allocation) 
        Not enough memory.
**/