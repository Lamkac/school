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
Employee* generateEmployee(){
	// nahodny datum narodenia
	Date newBirth = {random_number(1,27),random_number(1,12),random_number(1980,2010)};
	// nahodne informacie
	Information newInformation = {};
	randomStringFromCharset(newInformation.name,5,10);
	newInformation.birth = newBirth;
	// nahodne data
	Employee *newEmpoyee = malloc(sizeof(Employee));
	newEmpoyee->ID = random_number(1000,9999);
	newEmpoyee->salary = random_number(2000,5000);
	newEmpoyee->info = newInformation;
	//{random_number(1000,9999),random_number(2000,5000),"",newInformation};
	randomStringFromArray(newEmpoyee->position,POSITIONS,5);
		
	return newEmpoyee;
	
}
// vygenerovat n zamestnancov
Employee** generateEmployees( int n){
	
	Employee **employees = malloc(n * sizeof(Employee*));
	
	for(int i = 0; i < n; i++){
		
		employees[i] = generateEmployee();
		
	}
	printf("TEST %d\n",employees[0]->ID);

	return employees;
}
// vypisat zamestnanca
void printEmployee(Employee *employee){
	// formatovany print v jednom riadku
	printf("\n%s%*c %5d | %s%*c %7.2f | %d/%d/%d",
		employee->info.name,NAME_MAX_LEN+2-strlen(employee->info.name),'|',
		employee->ID,
		employee->position,POSITION_MAX_LEN+2-strlen(employee->position),'|',
		employee->salary,
		employee->info.birth.day,employee->info.birth.month,employee->info.birth.year);
	
}
// vypisat zamestnancov
void printEmployees(Employee **employees, int n){
	// hlavicka
	printf("Meno%*c| ID    | Pozicia%*c| Plat    | Datum narodenia\n",NAME_MAX_LEN-3,' ',POSITION_MAX_LEN-6,' ');
	for(int i=0; i<38+NAME_MAX_LEN+POSITION_MAX_LEN; i++)
		printf(".");
	// vypisat zamestnancov
	for(int i = 0; i < n; i++){
		printEmployee(employees[i]);
	}
	
}
// prida zamestnanca
Employee** addEmployee(Employee **employees, int *n, Employee *employee){
	
	(*n)++;
	employees = (Employee**) realloc(employees,((*n) * sizeof(Employee*)));
	employees[(*n)-1] = employee;
	
	return employees;
}

