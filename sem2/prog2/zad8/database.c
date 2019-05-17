// Jan Kucan 85917

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "database.h"

// nahodne cislo od a do b
int random_number(int a, int b) {
	return rand() % (b - a + 1) + a;
}
// nahodne slovo
void randomStringFromCharset(char* random, int minSize, int maxSize){
	
	int randomLen = random_number(minSize,maxSize);
	int i;
	
	for(i=0; i<randomLen; i++){
		
        int key = rand() % strlen(NAME_CHARSET);
		random[i] = NAME_CHARSET[key];
		
	}
	
	random[i] = 0;
	
}
// nahodny retazec s pola
void randomStringFromArray(char* output, char** input, int len){
	
    int key = rand() % len;
	strcpy(output,input[key]);
	
}
// vygenerovat zamestnanca
Employee generateEmployee(){
	// nahodny datum narodenia
	Date newBirth = {random_number(1,27),random_number(1,12),random_number(1980,2010)};
	// nahodne informacie
	Information newInformation = {};
	randomStringFromCharset(newInformation.name,5,10);
	newInformation.birth = newBirth;
	// nahodne data
	Employee newEmpoyee = {random_number(1000,9999),random_number(2000,5000),"",newInformation};
	randomStringFromArray(newEmpoyee.position,POSITIONS,5);
	
	return newEmpoyee;
	
}
// vygenerovat n zamestnancov
void generateEmployees(Employee employees[], int n){
	
	for(int i = 0; i < n; i++){
		
		employees[i] = generateEmployee();
		
	}

}
// vypisat zamestnanca
void printEmployee(Employee *employees){
	// formatovany print v jednom riadku
	printf("\n%s%*c %4d | %s%*c %4.2f | %d/%d/%d",
		employees->info.name,NAME_MAX_LEN+2-strlen(employees->info.name),'|',
		employees->ID,
		employees->position,POSITION_MAX_LEN+2-strlen(employees->position),'|',
		employees->salary,
		employees->info.birth.day,employees->info.birth.month,employees->info.birth.year);
	
}
// vypisat zamestnancov
void printEmployees(Employee employees[], int n){
	// hlavicka
	printf("Meno%*c| ID   | Pozicia%*c| Plat    | Datum narodenia\n",NAME_MAX_LEN-3,' ',POSITION_MAX_LEN-6,' ');
	for(int i=0; i<38+NAME_MAX_LEN+POSITION_MAX_LEN; i++)
		printf(".");
	// vypisat zamestnancov
	for(int i = 0; i < n; i++){
		printEmployee(&employees[i]);
	}
	
}
