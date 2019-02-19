#include<stdio.h>
#include<float.h>
#include<math.h>

void printToBinary(int n, int len){

	for(int i = len - 1; i >= 0; i--){
	
		printf("%d", (n >> i) & 1);
	
	}

}

void uloha11(){

	int a = 33777;
	char b = 'X';
	
	/*printToBinary(1,4);
	printf("\n");
	printToBinary(2,4);
	printf("\n");
	printToBinary(4,4);
	printf("\n");
	printToBinary(8,4);
	printf("\n");*/
	
	printToBinary(a,16);
	printf(" %d %X\n",a,a);
	printToBinary(b,16);
	printf(" %d %X\n",b,b);

}

void uloha13(){

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

int power(int a, int b){

	for(int i = 1; i < b; i++){
		a *= a;
	}
	return a;
	
}

float factorial(int a){
	int vys = 1.0;
	for(int i = 1; i < a; i++){
		vys += i + 1.0;
	}
	return vys;
	
}

float sinus(float radians, float epsilon){
	
	if(radians > (M_PI/2))
		return sinus(radians - M_PI,epsilon);
	
	
	float x = radians;
	float last = radians;
	int i = 1;
	
	while( fabs(last - x) < epsilon){
	
		last = x;
		
		int j = 1;
		if(i%2)
			j = -1;
			
		x += (j * powf(x,2*i+1)) / factorial(2*i+1);
		
		i++;
		
		if (i>1000){
			printf("Test");
			break;
		}
		
	}
	
	return x;

}

int main(){

	uloha11();
	printf("\n\n");
	uloha13();
	printf("\n\n");
	printf("%f",sinus(3,0.0001));
	
}