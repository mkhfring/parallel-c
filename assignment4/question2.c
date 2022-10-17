#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define NRA 20  /* number of rows in A */
#define NCA 30  /* number of columns in A = number of rows in B */
#define NCB 10  /* number of columns in matrix B */

void matrix_init(int m, int n, int arr[m][n], int (*f)(int, int));
int addElements(int a, int b);
int multiplyElementsPlusOne(int a, int b);
int fillWithZeros();
int main(int argc, char const *argv[])
{
 	int i, j, k, thread_count = NRA;
	int A[NRA][NCA], B[NCA][NCB], C[NRA][NCB];
    double start = omp_get_wtime();
    #pragma omp parallel num_threads(2)
    {
    matrix_init(NRA, NCA, A, addElements);
    matrix_init(NCA, NCB, B, multiplyElementsPlusOne);
    matrix_init(NRA, NCB, C, fillWithZeros);
    
    #pragma omp parallel for num_threads(2) private(j, k)
	for (i = 0; i < NRA; i++)
	    for (j = 0; j < NCB; j++) {
	        for (k = 0; k < NCA; k++) {
	        	C[i][j] = C[i][j] + A[i][k]*B[k][j];
	        }
	      }
    }
	for(i=0; i<NRA; i++){
		for(j=0; j<NCB; j++)
			printf("%d\t", C[i][j]);
		printf("\n");
	}
    double end = omp_get_wtime();
    double t = end - start;
    printf("The total time is %f", t * 1000);
	return 0;
}

int addElements(int a, int b){
    return a + b;
}
int multiplyElementsPlusOne(int a, int b){
    return a * b + 1;
}
int fillWithZeros(){
    return 0;
}
void matrix_init(int m, int n, int arr[m][n], int (*f)(int, int)){
    int i, j;
    #pragma omp parallel for num_threads(2) private(j)
    for (i=0; i<m; i++){
        for (j=0; j< n; j++){
            arr[i][j] = f(i, j);
        }
    }
}
/*
435     8990    17545   26100   34655   43210   51765   60320   68875   77430
465     9455    18445   27435   36425   45415   54405   63395   72385   81375
495     9920    19345   28770   38195   47620   57045   66470   75895   85320
525     10385   20245   30105   39965   49825   59685   69545   79405   89265
555     10850   21145   31440   41735   52030   62325   72620   82915   93210
585     11315   22045   32775   43505   54235   64965   75695   86425   97155
615     11780   22945   34110   45275   56440   67605   78770   89935   101100
645     12245   23845   35445   47045   58645   70245   81845   93445   105045
675     12710   24745   36780   48815   60850   72885   84920   96955   108990
705     13175   25645   38115   50585   63055   75525   87995   100465  112935
735     13640   26545   39450   52355   65260   78165   91070   103975  116880
765     14105   27445   40785   54125   67465   80805   94145   107485  120825
795     14570   28345   42120   55895   69670   83445   97220   110995  124770
825     15035   29245   43455   57665   71875   86085   100295  114505  128715
855     15500   30145   44790   59435   74080   88725   103370  118015  132660
885     15965   31045   46125   61205   76285   91365   106445  121525  136605
915     16430   31945   47460   62975   78490   94005   109520  125035  140550
945     16895   32845   48795   64745   80695   96645   112595  128545  144495
975     17360   33745   50130   66515   82900   99285   115670  132055  148440
1005    17825   34645   51465   68285   85105   101925  118745  135565  152385
*/
