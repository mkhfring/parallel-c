#include <stdio.h>
#include <stdlib.h>

int f(){
    return 1;
}
int g(int x){
    return x;
}
int main(int argc, char const *argv[])
{
    int x;
    /* code */
#pragma omp parallel num_threads(2)

{ double tmp, B;
B = f();
tmp = g(B);
#pragma omp atomic
x += tmp;


}
printf("%d", x);
}

