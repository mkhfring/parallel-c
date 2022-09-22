#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int main(){
    int input [4];
    int *p;
    p = input;
    float sum = 0;

    printf("Please insert 4 integers: \n");
    for (int i=0; i<4; i++){
        scanf("%d", p);
        sum += *p++;
    }
    int length = sizeof(input) / sizeof(input[0]);

    float average = sum/length;
    int moreThanAvergage = 0;
    for (int i =0; i<4; i++){
        if(input[i] > average){
            moreThanAvergage ++;
        }
    }
    char *entry;
    entry = (moreThanAvergage > 1) ? "There are %d entries more than average (%.1f) \n" : "There is %d entry more than average (%.1f) \n";
    printf(entry, moreThanAvergage, average);

}
