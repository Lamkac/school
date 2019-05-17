// Jan Kucan 85917

#include <stdio.h>

int a, b, result;
	
int main(){
	
	scanf("%d",&a);
	scanf("%d",&b);
	result = 0;

	asm(".intel_syntax noprefix \n" // Prepneme z AT&T syntaxe na na Intel

		 "mov eax, _a \n"
		 "add eax, _b\n"
		 "mov _result,eax \n"

	".att_syntax \n"); // Dame vsetko do povodneho stavu
	
	/*__asm {
		MOV EAX, a
		ADD EAX, b
		MOVE result, EAX
	}*/

	printf("%d\n",result);

	return 0;
}