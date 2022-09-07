#include <stdio.h>
double getAverage(int a[], int size);
int main(){
	int a[3] = {1, 2, 3};
	double avg;
	avg = getAverage(a, 2);
	printf("The result is %f \n", avg);
}
double getAverage(int a[], int size){
	double sum=0;
	double avg;
	for(int i=0; i<size; ++i){
		sum += a[i];
	}
	return sum / size;

}

