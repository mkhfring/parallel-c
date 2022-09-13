#include <stdio.h>
int main(){

    int arr[5] = {1,23,17,4,-5};
    int* p = arr; // or int* p = &arr[0]
    for (int i = 0; i < 5; i++) {
    printf("arr[%d] = %d ", i, arr[i]);
    printf("\tp + %d = %d\n", i, *p++);
}
    
}