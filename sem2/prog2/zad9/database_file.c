// Jan Kucan 85917

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "database.h"
#include "database_file.h"

// ulozit zamestnancov
void saveEmployees(Employee **employees, int n, char* fileName){
	
	FILE* file = fopen(fileName, "w");
	
	for(int i=0; i<n; i++){
		fprintf(file,"%d %.2f %s %s %d %d %d\n",
			employees[i]->ID,
			employees[i]->salary,
			employees[i]->position,
			employees[i]->info.name,
			employees[i]->info.birth.day,
			employees[i]->info.birth.month,
			employees[i]->info.birth.year);
	}
	
	// zavrie subor
    fclose (file);
	
}

// nacitat zamestnanca
Employee* loadEmployee(char* line){
	
	char *token;
	Employee *newEmpoyee = malloc(sizeof(Employee));
	Date newBirth = {};
	Information newInformation = {};
	
	// ID
	token = strtok(line, " ");
	newEmpoyee->ID = atoi(token);
	// plat
	token = strtok(NULL, " ");
	newEmpoyee->salary = atoi(token);
	// pozicia
	token = strtok(NULL, " ");
	strcpy(newEmpoyee->position,token);
	// meno
	token = strtok(NULL, " ");
	strcpy(newInformation.name,token);
	// den
	token = strtok(NULL, " ");
	newBirth.day = atoi(token);
	// mesiac
	token = strtok(NULL, " ");
	newBirth.month = atoi(token);
	// rok
	token = strtok(NULL, " ");
	newBirth.year = atoi(token);
	// priradit struktury
	newInformation.birth = newBirth;
	newEmpoyee->info = newInformation;
	
	return newEmpoyee;
}
// nacitat zamestnancov
Employee** loadEmployees(int *n, char* fileName){
	
	FILE* file = fopen(fileName, "r");
	
	int size = 0;
	int ch;
	// zisti velkost
	while((ch = fgetc(file)) != EOF)
		if (ch == '\n') size++;
	// nastavy zoznam
	*n = size; 
	Employee **employees = malloc(size * sizeof(Employee*));
	// vrati sa na zaciatok
	fseek(file, 0, SEEK_SET);
	
	//nacita kazdy riadok
	char line[LINE_MAX_SIZE];
	int i = 0;
	while (fgets(line, LINE_MAX_SIZE, file)) {
		 // odstrani novy riadok ak je na konci
		if(line[strlen(line)-1] == '\n')
			line[strlen(line)-1] = 0;
		
		employees[i] = loadEmployee(line);
		i++;
    }
	
	// zavrie subor
    fclose (file);
	// vrati zoznam
	return employees;
}

