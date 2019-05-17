// Jan Kucan 85917

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "database.h"
#include "database_sort.h"
#include "database_file.h"

int parseCommand(char *command_list, Compare *compare, char* temp_output, char *error_output){
	
	// vynuluje compare strukturu
	char *temp;
	compare->amount = 0;
	compare->sort_key[0] = 0;
	compare->compare_key[0] = 0;
	compare->compare_value[0] = 0;
	compare->compare_type = 0;
	// najde prvy prikaz
	temp = strtok(command_list," ");
	// prehladava az na koniec
	while(temp!=NULL){
		// vypnutue programu
		if(!strcmp(temp,"exit")){
			return -1;
		// ukazanie zaznamov
		}else if(!strcmp(temp,"insert")){
			int start = 0;
			temp = strtok(NULL," ");
			while(temp != NULL){
				strcat(temp_output,temp);
				strcat(temp_output," ");
				temp = strtok(NULL," ");
			}
			
			return -2; // insert call
		}else if(!strcmp(temp,"delete")){
			
			temp = strtok(NULL," ");
			// ak sa nenasiel
			if(temp == NULL){
				strcpy(error_output,"Missing key string after command where");
				return 0;
			}
			// ulozi kluc do struktury
			strcpy(compare->compare_key, temp);
			// dalsi prikaz
			temp = strtok(NULL," ");
			// ak sa nenasiel
			if(temp == NULL){
				strcpy(error_output,"Missing comparing type >, < or = after command where");
				return 0;
			}
			// ulozi podla podmienky
			if(!strcmp(temp,"=")){
				compare->compare_type = 3;
			}else if (!strcmp(temp,"<")){
				compare->compare_type = 2;
			}else if (!strcmp(temp,">")){
				compare->compare_type = 1;
			}else{
				strcpy(error_output,"Invalid comparing type!");
				return 0;
			}
			// dalsi prikaz
			temp = strtok(NULL," ");
			// ak sa nenasiel
			if(temp == NULL){
				strcpy(error_output,"Missing comparing value");
				return 0;
			}
			// ulozu hodnotu do struktury
			strcpy(compare->compare_value, temp);
			
			return -3; // delete call
		}else if(!strcmp(temp,"show")){
			// dalsi prikaz
			temp = strtok(NULL," ");
			// ak sa nenasiel
			if(temp == NULL){
				strcpy(error_output,"Missing number or 'all' after command show");
				return 0;
			}
			// ak vsetko nastavi na 
			if(!strcmp(temp,"all")){
				compare->amount = 0;
			}else{
				// inak nacita pozadovanu hodnotu
				compare->amount = atoi(temp);
				// ak pozadovana nebolo cislo alebo 0
				if(compare->amount == 0){
					strcpy(error_output,"Invalid number after command show");
					return 0;
				}
			}
		// podmienky
		}else if(!strcmp(temp,"where")){
			// dalsi prikaz
			temp = strtok(NULL," ");
			// ak sa nenasiel
			if(temp == NULL){
				strcpy(error_output,"Missing key string after command where");
				return 0;
			}
			// ulozi kluc do struktury
			strcpy(compare->compare_key, temp);
			// dalsi prikaz
			temp = strtok(NULL," ");
			// ak sa nenasiel
			if(temp == NULL){
				strcpy(error_output,"Missing comparing type >, < or = after command where");
				return 0;
			}
			// ulozi podla podmienky
			if(!strcmp(temp,"=")){
				compare->compare_type = 0;
			}else if (!strcmp(temp,"<")){
				compare->compare_type = 1;
			}else if (!strcmp(temp,">")){
				compare->compare_type = 2;
			}else{
				strcpy(error_output,"Invalid comparing type!");
				return 0;
			}
			// dalsi prikaz
			temp = strtok(NULL," ");
			// ak sa nenasiel
			if(temp == NULL){
				strcpy(error_output,"Missing comparing value");
				return 0;
			}
			// ulozu hodnotu do struktury
			strcpy(compare->compare_value, temp);
		// sort
		}else if(!strcmp(temp,"sort")){	
			// dalsi prikaz
			temp = strtok(NULL," ");
			// ak sa nenasiel
			if(temp == NULL){
				strcpy(error_output,"Missing string after command sort");
				return 0;
			}
			// ulozu hodnotu do struktury
			strcpy(compare->sort_key, temp);
			// neznamy prikaz
		}else{
				strcpy(error_output,"Unknown command");
				return 0;
		}
		// dalsi prikaz
		temp = strtok(NULL," ");
	}
	// vsetko dobre
	return 1;
}

int main(int argc, char* argv[]) {
	srand(time(NULL)); // init random seed
	// init hodnoty
	int n = 10; // pocet zamestancov
	int newN = n;
	char command_list[128];
	char error[128]; // chybova hlaska
	char temp_output[128];
	int result = 0;
	Compare compare;
	// zamenstancy
	Employee **employees;
	Employee **employees_show;
	// vygenerovat zamestnancov
	//employees = generateEmployees(n);
	employees = loadEmployees(&n,"zoznam.txt");
	employees_show = malloc(n * sizeof(Employee*));
	
	// hlavny loop
	while(1){
		temp_output[0] = 0;
		error[0] = 0;
		// vynulovat a okopirovat original zamestancov do noveho pola
		newN = n;
		for(int i=0; i<n; i++)
			employees_show[i] = employees[i];
		// vypisat original
		CLEAR_SCREEN();
		printEmployees(employees,n);
		printf("\n\nPrikaz: ");
		// cakat na prikaz
		scanf("%[^\n]s",command_list);
		getchar();
		// vykonat prikaz
		result = parseCommand(command_list, &compare, temp_output, error);
		// ak je 0 vypisat chybu, ak mensie ako 0 ukoncit program inak pokracovat
		if (result == -1) {
			// ulozit zmeny
			saveEmployees(employees,n,"zoznam.txt");
			break;
		}else if (result == -2){
			
			Employee *e = loadEmployee(temp_output);
			employees = addEmployee(employees,&n,e);
			employees_show = realloc(employees_show,(n * sizeof(Employee*)));
			
			continue;
		}else if (result == -3){
			
			employees = prune(employees,&n,&compare,1);
			
			continue;
		}else if (result == 1){
			// vykonat prikaz
			printf("\n");
			
			employees_show = prune(employees_show,&newN,&compare,0);
			printEmployees(employees_show,newN);
			
			/*if(!prune(employees_show,&newN,&compare)){
				// ak sa zle vykonal
				result = 0;
				strcpy(error,"Invalid command");
			}else {
				// vypisat novy zoznam
				printEmployees(employees_show,newN);
			}*/
			
		}
		if (result == 0)
			printf("\n > %s\n Commands:\n  show [k|all] {where [plat|id|pozicia|meno|datum] [<|=|>] value} {sort [plat|id|pozicia|meno|datum] }\n  exit\n",error);
		// cakat na potvrdenie
		getchar();
		
	}
	
	return 0;
}
