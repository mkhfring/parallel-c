#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>


int f(int a){
    return sin(a);
}
void Trap(double a, double b, int n, double* global_result_p);
int main() {
int x = 10, y = 5;
# pragma omp parallel num_threads(2)
{
int id = omp_get_thread_num();
# pragma omp critical
{
if(id==0) x *= 2;
if(id==1) x += y;
}
}
}