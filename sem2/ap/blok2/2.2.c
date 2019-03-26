#include <stdio.h>

int main()
{
	char text[] = "architektura_pocitacov_je_super_predmet_milujem_ho";
	char *pointer = text;
	
	printf("%s\n", text);
	
	printf("%p\n", pointer);
	pointer++;
	*pointer = 150;
	
	printf("%s\n", text);
	
	pointer = (char*) 12345;
	*pointer = 150;

	return 0;
}

