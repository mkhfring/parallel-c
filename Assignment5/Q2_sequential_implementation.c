%%cu

// CPU Implementation goes here!
#include <stdio.h>
#include <time.h>

void vector_init(double *arr, int size);
int main(){
    clock_t start, end;
    const int n = 10000000;
    double *a = (double*) malloc(n * sizeof(double));
    if (NULL == a){
        printf("enable to allocate memory");
        exit(0);
    }
    start = clock();
    vector_init(a, n);
    end = clock();
    double total_time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("The total time to execute the serial code is %.3f \n", total_time);
    for (int i=0; i<5; i++){
        printf("a[%d]: %.7f \n", i, a[i]);
    }
    printf("....\n");
    for (int i=n-5; i<n; i++){
        printf("a[%d]: %.7f \n", i, a[i]);
    }

}
void vector_init(double *arr, int size){
    for(int i=0; i<size; i++){
        arr[i] = (double) i/size;
    }
}
/*
The total time to execute the serial code is 0.095 
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