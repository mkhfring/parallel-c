#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void parallel_count_sort(int a[], int n) {
	int i, j, count;
	int* temp = malloc(n * sizeof(int));
    #pragma omp parallel for num_threads(8) private(j, count) shared(temp)
	for (i = 0; i < n; i++){
		//count all elements < a[i]
		count = 0;
		for (j = 0; j < n; j++)
			if(a[j]<a[i] ||(a[j]==a[i] && j<i))	
				count++;
		        //place a[i] at right order
		        temp[count] = a[i];
	}
	memcpy(a, temp, n * sizeof(int));
	free(temp);
}
int main(int argc, char const *argv[])
{
    int lower = 0, upper = 10, size=10; 
    int a[size];
    for(int i=0; i < size; i++){
        srand(omp_get_wtime());

        a[i] = (rand() % (upper - lower + 1)) + lower; // Generating a random number between 0 and 10000.
        printf("%d \n", a[i]);
        sleep(0.3);
    }

    double start = (double)omp_get_wtime();
    parallel_count_sort(a, size);
    double total = (double)(omp_get_wtime() - start) * 1000;
    printf("The total time to finish the task is: %.5f ms \n\n");
    for(int i=0; i < 4; i++){
        printf("%d ", a[i]);
    }
    return 0;
}

