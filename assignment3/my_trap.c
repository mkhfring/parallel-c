#include <stdio.h>
#include <stdlib.h>
#include <omp.h> 
#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void count_sort(int a[], int n) {

	int i, j, count;
	int* temp = malloc(n * sizeof(int));

	double start_time = omp_get_wtime();
	#pragma omp parallel num_threads(8) shared(temp, n)
	{
		#pragma omp for private(j, count)
		for (i = 0; i < n; i++){
			//count all elements < a[i]
			count = 0;
			for (j = 0; j < n; j++)
				if(a[j]<a[i] ||(a[j]==a[i] && j<i))
					count++;
			//place a[i] at right order
			temp[count] = a[i];
		}
	}
	memcpy(a, temp, n * sizeof(int));
	free(temp);
	double time = (omp_get_wtime() - start_time)*1000;
	printf("%.5f ms", time);
}


int main (int argc, char *argv[]) {

    int a[] = {5,2,1,4};
    int n = 4;

    count_sort(a, n);
    for(int i=0; i<n; i++){
        printf("%d \n", a[i]);
    }

    return 0;
}