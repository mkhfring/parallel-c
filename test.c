#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char const *argv[])
{
	 int x = 5;
	 #pragma omp parallel num_threads(4) private(x)
	 {
	 x = 10;
	 printf("%d \n", x);

     }
	 printf("%d", x);

    return 0;
}
