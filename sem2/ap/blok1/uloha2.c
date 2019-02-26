// Jan Kucan 85917

#include<stdio.h>
#include<float.h>
#include<math.h>


void rim(int number,char a, char b, char c){

	if(number < 4){
		
		for(int i = 0; i < number; i++)
			printf("%c",a);
		
	}
	
	if(number == 4)
		printf("%c%c",a,b);
	if(number == 5)
		printf("%c",b);

	if(number > 5 && number < 9){
		printf("%c",b);
	
		for(int i = 0; i < number - 5; i++)
			printf("%c",a);
	
	}
	
	if(number == 9)
		printf("%c%c",a,c);
	
	
}

int main(){
	
	//for(int i=1;i<100;i++){
		
		int c;
		scanf("%d",&c);
		
		rim((c/10)%10,'X','L','C');
		rim(c%10,'I','V','X');
		printf("\n");
	//}
}