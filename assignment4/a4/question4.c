#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "my_rand.h"

int main(int argc, char **argv) {
	unsigned seed = omp_get_num_threads();
	unsigned randNumber = my_rand(&seed);
	printf("%d", randNumber);


	return 0;

}

