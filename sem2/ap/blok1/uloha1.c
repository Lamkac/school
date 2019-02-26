// Jan Kucan 85917

#include<stdio.h>
#include<float.h>
#include<math.h>

void printToBinary(int n, int len){

	for(int i = len - 1; i >= 0; i--){
	
		printf("%d", (n >> i) & 1);
	
	}

}

int main(){

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