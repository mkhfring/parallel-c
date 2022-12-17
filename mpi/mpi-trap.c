#include <stdio.h>
#include <math.h>
#include <mpi.h>


double f(double a){
    return sin(a);
}
double Trap(double my_a, double my_b, int my_n, double h) {

    double my_result = (f(my_a) + f(my_b)) / 2.0;
    for (int i = 1; i <= my_n - 1; i++) {
        double x = my_a + i * h;
        my_result += f(x);
    }
    my_result = my_result * h;
    return my_result;
}
int main() {
double a = 0.0, b = 3.0, n = 1024;
int my_rank, comm_sz, my_n, source;
double h, my_a, my_b, my_sum, total_sum;
//initialize, get rank and comm_sz
MPI_Init(NULL, NULL);
MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
//break down the problem to subproblems
h = (b-a) / n; // the same for all processes
my_n = n / comm_sz;
my_a = a + my_rank * my_n * h;
my_b = my_a + my_n * h;
my_sum = Trap(my_a, my_b, my_n, h);
if(my_rank!=0){
    MPI_Send(&my_sum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
}else{
    total_sum = my_sum;
    for(int i=1; i<comm_sz; i++){
        MPI_Recv(&my_sum, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        total_sum += my_sum;
    }
}

if (my_rank == 0) {
    printf("%.3f\n", total_sum);
}
MPI_Finalize();
return 0;   
}