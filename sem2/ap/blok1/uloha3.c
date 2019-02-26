// Jan Kucan 85917

#include<stdio.h>
#include<float.h>
#include<math.h>

int main(){
	float sumFloat = 2;
	float lastFloat = 2;
	double sumDouble = 2;
	double lastDouble = 2;
	double div = 2; 
	
	while(sumFloat > 1.0){
		lastFloat = (1/div);
		div *= 2;
		sumFloat = 1 + (1/div);
	}
	div = 2;
	while(sumDouble > 1.0){
		lastDouble = (1/div);
		div *= 2;
		sumDouble = 1 + (1/div);
	}
	
	printf("Float moje:\n");
	printf("%.20f %e\n",lastFloat,lastFloat);
	
	printf("Float FLT_EPSILON:\n");
	printf("%.20f %e\n\n",FLT_EPSILON,FLT_EPSILON);
	
	printf("Double moje:\n");
	printf("%.20f %e\n",lastDouble,lastDouble);
	
	printf("Double DBL_EPSILON:\n");
	printf("%.20f %e\n",DBL_EPSILON,DBL_EPSILON);
	
}