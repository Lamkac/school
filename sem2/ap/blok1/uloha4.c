// Jan Kucan 85917

#include<stdio.h>
#include<float.h>
#include<math.h>

float factorial(int a){
	int vys = 1.0;
	for(int i = 1; i < a; i++){
		vys += i + 1.0;
	}
	return vys;
	
}

float sinus(float radians, float epsilon){
	
	double pi = M_PI;
	
	if(radians > ((3*pi)/2))
		return sinus(radians - (2*pi),epsilon);
	if(radians < -(pi/2))
		return sinus(radians + (2*pi),epsilon);
	
	int invert = 1;
	if(radians > pi/2){
		invert = -1;
		radians -= pi;
	}else if(radians < -(pi/2)){
		invert = -1;
		radians += pi;
	}
	
	float x = radians;
	float last = 0;
	int i = 1;
	
	while(fabs(last - x) > epsilon){
		
		last = x;
		
		int j = 1;
		if(i%2)
			j = -1;
			
		x += (j * pow(radians,2*i+1)) / factorial(2*i+1);
		
		i++;
	}
	
	return x*invert;

}

int main(){
	
	float c;
	while(1){
		scanf("%f", &c);
		if(c > 1000000)
			break;
	
		printf("%.5f\n",sinus(c,0.00001));
		printf("%.5f\n",sin(c));
	}
	
	
}