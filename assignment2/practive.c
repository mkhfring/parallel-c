#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>


int f(int a){
    return sin(a);
}
void Trap(double a, double b, int n, double* global_result_p);
int main() {
double global_result = 0.0; // result stored in global_result
double a = 1, b = 2; // endpoints
int thread_count = 4; // should be = number of cores
int n = 8; // Total number of trapezoids = multiple of thread_count
# pragma omp parallel num_threads(thread_count)
Trap(a, b, n, &global_result);
printf("Approximate area: %f\n", global_result); return 0;
}


void Trap(double a, double b, int n, double* global_result_p) {
double h, x, my_result, my_a, my_b; int i, my_n;
int my_id = omp_get_thread_num();
int thread_count = omp_get_num_threads();
// h = (b - a) / n;
my_n = n / thread_count; // # of contiguous trapezoids per thread
my_a = a + (my_id * my_n);
my_b = my_a + my_n ;
printf("thread: %d, [%d: %d] \n", my_id, my_a, my_b);
// my_result = (f(my_a) + f(my_b)) / 2.0;
// for (i = 1; i <= my_n - 1; i++) {
// x = my_a + i * h;
// my_result += f(x);
// }
// my_result = my_result * h;
// *global_result_p += my_result;
}