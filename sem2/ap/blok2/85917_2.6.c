// Jan Kucan 85917

#include "stdafx.h"

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define WIDTH 120
#define HEIGHT 30

void clear() {
	system("cls");
}

int random_number(int a, int b) {
	return rand() % (b - a + 1) + a;
}

void show_help() {
	clear();
	printf("Navod na pouzitie:\n  F1 - Navod na pouzitie\n  F2 - Spustit odpocitavanie\n  F10 alebo ESC - ukoncenie programu\n");
}

void start() {

	char ch = 0;
	char random_char = random_number('a','z');
	float result;
	clock_t start, end;
	start = clock();

	clear();
	for (int i = 0; i < HEIGHT / 2; i++)
		printf("\n");

	printf("%*s%c\n",(WIDTH/2)," ",random_char);

	do {

		if (_kbhit())
			ch = _getch();

	} while (ch != random_char);

	end = clock();

	result = (float)(end - start) / CLOCKS_PER_SEC;

	clear();

	int sec = (int)result;
	int millis = (result - sec) * 1000;

	printf("\n  Trvalo to %i sekund a %i milisekund\n",sec,millis);
}

int main() {

	int special = 0;
	char ch = 0;

	srand(time(NULL));
	clear();

	do {

		if (!_kbhit())
			continue;

		ch = _getch();
		printf("%d", ch);
		if (ch == 0) {
			special = 1;
			ch = _getch();
		}
		else {
			special = 0;
		}

		switch (ch) {
			case 59:
				show_help();
				break;
			case 60:
				start();
				break;
		}

	} while (!(ch == 27 || (special && ch == 68)));

	return 0;
}