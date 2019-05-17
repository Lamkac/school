// Jan Kucan 85917

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "database.h"
#include "database_sort.h"

#define MAX_ZAM 100

int parseCommand(char *command_list, Compare *compare, char *error_output){
	
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
	int result = 0;
	Compare compare;
	// zamenstancy
	Employee employees[MAX_ZAM];
	Employee employees_show[MAX_ZAM];
	// vygenerovat zamestnancov
	generateEmployees(employees,n);
	// hlavny loop
	while(1){
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
		result = parseCommand(command_list, &compare, error);
		// ak je 0 vypisat chybu, ak mensie ako 0 ukoncit program inak pokracovat
		if (result < 0) {
			break;
		}else if (result == 1){
			// vykonat prikaz
			printf("\n");
			if(!prune(employees_show,&newN,&compare)){
				// ak sa zle vykonal
				result = 0;
				strcpy(error,"Invalid command");
			}else {
				// vypisat novy zoznam
				printEmployees(employees_show,newN);
			}
			
		}
		if (result == 0)
			printf("\n > %s\n Commands:\n  show [k|all] {where [plat|id|pozicia|meno|datum] [<|=|>] value} {sort [plat|id|pozicia|meno|datum] }\n  exit\n",error);
		// cakat na potvrdenie
		getchar();
		
	}
	
	return 0;
}
