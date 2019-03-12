// school.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#pragma warning(disable:4996)

int main()
{
	char* text = "architektura_pocitacov_je_super_predmet_milujem_ho";
	void *pointer = text;

	printf("%s\n", text);
	printf("%p\n", pointer);
	*text++;
	printf("%s\n", text);

	return 0;
}

