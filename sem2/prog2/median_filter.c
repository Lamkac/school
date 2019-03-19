// Jan Kucan 85917

#include "median_filter.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

// nacitanie dat zo vstupu
int loadData(double* input, int n){
	int i=0;
	double val;
	while(scanf("%lf",&val)>0)
	{
		input[i] = val;
		i++;
		
		if(i>=n)
			break;
		
	}
	
    return i;
}

// filtrovanie dat
void filterData(double *input, double* output, int k, int w){
	
	int w_len = w*2+1;
	double win[w_len];
	
	for(int i = 0; i < k; i++){
		// iba prekopiruje okraj
		if( i < w || i > k-w-1){
			output[i] = input[i];
		}else{
			
			for(int j = 0; j < w_len; j++){
				win[j] = input[i - w + j];
			}
			
			output[i] = median(win, w_len);
		}
		
	}
	
}

// sort filter
int cmpfunc (const void * a, const void * b) {
   double result = ( *(double*)a - *(double*)b );
   // osetrenie cisel pre mensie ako 1
   if (result > 0)
	   return 1;
   if (result < 0)
	   return -1;
   return 0;
   
}

// vypocitat median
double median(double *data, int n){
	
	qsort(data,n,sizeof(double),cmpfunc);
		
    return data[n/2];
	
}

// vypisat data
void printData(double *data, int n)
{
	
	for(int i = 0; i < n; i++){
		printf("%.*f\n", PRECISION, data[i]);
	}
	
}