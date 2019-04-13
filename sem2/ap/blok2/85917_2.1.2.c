
#include <stdio.h>

int asm_a, asm_result;
	
int nasobenie2(int a){
	asm_a = a;

	asm(".intel_syntax noprefix \n" // Prepneme z AT&T syntaxe na na Intel

		 "mov eax,_asm_a \n"
		 "shl eax\n"
		 "mov _asm_result,eax \n"

	".att_syntax \n"); // Dame vsetko do povodneho stavu
	
	return asm_result;
}
	
int main(){

	int c = 0;
	scanf("%d",&c);
	
	printf("%d",nasobenie2(c));

	return 0;
}