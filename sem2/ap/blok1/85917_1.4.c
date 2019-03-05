// Jan Kucan 85917

#include<stdio.h>
#include<float.h>
#include<math.h>

float factorial(int a){
	int vys = 1.0;
	for(int i = 1; i < a; i++){
		vys *= i + 1.0;
	}
	return vys;
	
}

float sinus(float degre, float epsilon){
	
	while(degre > 270)
		degre -= 360;
		
	while(degre <= -90)
		degre += 360;
	
	int invert = 1;
	if(degre > 90){
		invert = -1;
		degre -= 180;
	}
	
	float radians = degre*M_PI/180;
	
	float x = radians;
	float last = 0;
	int i = 1;
	
	while(fabs(last - x) > epsilon){
		
		last = x;
		
		int j = 1;
		if(i%2)
			j = -1;
			
		x += j * (pow(radians,2*i+1)) / factorial(2*i+1);
		
		i++;
	}
	
	return x*invert;

}

int main(){
	
	float c;
	while(1){
		scanf("%f", &c);
		if(c > 10000000)
			break;
		
		printf("%.5f\n",sinus(c,0.00001));
	}
	
	
}