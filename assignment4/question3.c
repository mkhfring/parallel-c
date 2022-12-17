#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void printTheResult(int arr[], int size);
void serialImplementation(int size);
void paralizedImplementation(int size);
int main(int argc, char const *argv[])
{   

    serialImplementation(10);
    paralizedImplementation(10);
    //printing the result
    return 0;
}
void serialImplementation(int size){
    int a[size];
    a[0] = 0;
    for(int i=1; i < size; i++){
        a[i] = a[i-1] + i;
    }
    printf("The result for serialized version is: \n");
    printTheResult(a, size);
}
void paralizedImplementation(int size){
    int a[size];
    a[0] = 0;
    int i;
    #pragma omp parallel for num_threads(4)
    for(i=1; i < size; i++){
        a[i] = 
    }
    printf("\n\nThe result for parallel version is: \n");
    printTheResult(a, size);

}
void printTheResult(int arr[], int size){
    for(int i=0; i < size; i++){
        printf("%d ", arr[i]);
    }
}

/*
The value of each element from element 1 onward is calculated based on the result, which is calculated for previous element. So, there 
is a loop carried dependency. Since the value of each element cannot be calculated before the previous element is computed,current 
version of the algorithm should be updated. As a result, since each element is the sum of 0 + ...,+ i-1 + i, we can use (i * (i+1))
equation to compute each element without considering the previous calculated element in the array. Accordingly, we can remove the
loop carried dependency. Now that we have changed the algorithm, we can use parallel loop to compute all the elements of the array
*/