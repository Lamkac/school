// Jan Kucan 85917

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int getNumber(int c){

	if(c>=48 && c<=57)
		return c - 48;

	if(c>=45 && c<=70)
		return c -55;
		
	return -1;
}

int main(){
	char input[100];
	
	scanf("%s",input);
	
	int i = 1;
	int sum = 0;
	while(getNumber(input[i])>=0){
	
		int n = getNumber(input[i])<<4|getNumber(input[i+1]);
		sum += n;
		
		printf("%2X",n);
		
		i+=2;
	}
	
	printf("\n%X",0xFF-(sum%256)+1);
	
}