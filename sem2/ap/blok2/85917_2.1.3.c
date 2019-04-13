
#include <stdio.h>

int asm_a, asm_result;
	
int prevod(int a){
	asm_a = a;

	asm(".intel_syntax noprefix \n" // Prepneme z AT&T syntaxe na na Intel

		 "mov eax,_asm_a \n" // a do eax
		 "cmp eax, 10  \n" // skok do "pismeno" ak je rovne alebo vecsie ako 10
		 "jge pismeno \n"
		 "add eax, 48\n" // prida 48
		 "jmp end\n"
		 "pismeno:\n"
		 "add eax, 55\n" // prida 55
		 "end:\n"
		 "mov _asm_result,eax \n" // ulozi eax do result
		 
	".att_syntax \n"); // Dame vsetko do povodneho stavu
	
	return asm_result;
}
	
int main(){

	int c = 0;
	scanf("%d",&c);
	
	printf("%c",prevod(c));

	return 0;
}