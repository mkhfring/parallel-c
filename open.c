#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void run_func(int, int);

int main()
{
    run_func(1,1);
    run_func(10,2);
    run_func(50,3);
    run_func(100,4);
    run_func(1000000,5);

    return 0;
}

void run_func(int vec_size, int count){
    clock_t start_t, end_t;
    double total_t;
    int i, sum=0;
    long long int size = vec_size * 1000000;

    start_t = clock();
    ///printf("Starting of the program: %ld\n", start_t);

    int* A = (int*) malloc(size * sizeof(int));
    int* B = (int*) malloc(size * sizeof(int));
    int* C = (int*) malloc(size * sizeof(int));

    if(A!=NULL && B!=NULL && C!= NULL){
        for(i=0; i<size; i++){
            A[i] = i*3;
            B[i] = -i*3;
            C[i] = A[i] + B[i];
            sum += C[i];
        }
        end_t = clock();
        ///printf("End of the program: %ld\n", end_t);

        total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        printf("Sample Run %d:\t(successful for vec_size: %d million)\n", count, vec_size);
        printf("\tSum:\t%d\n", sum);
        printf("\tExecution time:\t%lf sec\n\n", total_t);
    }else{
        end_t = clock();
        ///printf("End of the program: %ld\n", end_t);

        total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;

        printf("Sample Run %d:\t(unsuccessful memory allocation for vec_size: %d million)\n", count, vec_size);
        printf("\tNot Enough Memory.\n\n");
    }
}

/** Reporting correct results as a comment
    Sample Run 1:   (successful for vec_size: 1 million)
            Sum:    0
            Execution time: 0.004000 sec

    Sample Run 2:   (successful for vec_size: 10 million)
            Sum:    0
            Execution time: 0.057000 sec

    Sample Run 3:   (successful for vec_size: 50 million)
            Sum:    0
            Execution time: 0.272000 sec

    Sample Run 4:   (successful for vec_size: 100 million)
            Sum:    0
            Execution time: 0.548000 sec

    Sample Run 5:   (unsuccessful memory allocation for vec_size: 10000 million)
            Not Enough Memory.


    Process returned 0 (0x0)   execution time : 1.042 s
    Press any key to continue.
    **/