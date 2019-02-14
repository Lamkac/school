#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>

int main() {

	int a, b;

	scanf("%i", &a);
	scanf("%i", &b);

	genManyNumbers(a,b);

	//printf("Output: %d\n", vys);


	return 0;

}

int doSomething(int p) {

	if (p > 0)
		return p * 2;
	
	return p;
}

int genOneNumber(int a, int b) {

	srand(time(NULL));
	return rand() % (b - a + 1) + a;

}

void genManyNumbers(int k, int m) {

	int lastNumber = genOneNumber(k, m);
	int count = 0;

	printf("%d\n", lastNumber);

	while (count < 5) {

		int newNumber = genOneNumber(k, m);

		printf("%d\n", newNumber);

		if (newNumber >= lastNumber) {
			count++;
		}else {
			count = 0;
		}

		lastNumber = newNumber;
	}


}