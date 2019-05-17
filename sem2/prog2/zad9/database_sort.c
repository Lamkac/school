// Jan Kucan 85917

#include <string.h>

#include "database.h"
#include "database_sort.h"

// prekonvertuje datum do cisla na porovnavanie
int dateToNumber(Date date){
	return (date.year*10000) + (date.month*100) + date.day;
}
// roztriedit podla mena
int databaseSortByName(const void *v1, const void *v2){
	
	const Employee *p1 = *(Employee **)v1;
    const Employee *p2 = *(Employee **)v2;
	
	return strcmp(p1->info.name,p2->info.name);
	
}
// roztriedit podla id
int databaseSortById(const void *v1, const void *v2){
	
	const Employee *p1 = *(Employee **)v1;
    const Employee *p2 = *(Employee **)v2;
	
	return p1->ID - p2->ID;
	
}
// roztriedit podla platu
int databaseSortBySalary(const void *v1, const void *v2){
	
	const Employee *p1 = *(Employee **)v1;
    const Employee *p2 = *(Employee **)v2;
	
	return p1->salary - p2->salary;
	
}
// roztriedit podla pozicie
int databaseSortByPosition(const void *v1, const void *v2){
	
	const Employee *p1 = *(Employee **)v1;
    const Employee *p2 = *(Employee **)v2;
	
	return strcmp(p1->position,p2->position);
	
}
// roztriedit podla datumu narodenia
int databaseSortByBirth(const void *v1, const void *v2){
	
	const Employee *p1 = *(Employee **)v1;
    const Employee *p2 = *(Employee **)v2;
	
	return dateToNumber(p1->info.birth) - dateToNumber(p2->info.birth);
	
}
// roztriedit pole
int sort(Employee **list, int n, char* sort_key){
	
	int (*sortFunction)(const void*,const void*);
	// najst spravnu funkciu podla klucu
	if(!strcmp(sort_key,"meno")){
		sortFunction = &databaseSortByName;
	}else if(!strcmp(sort_key,"id")){
		sortFunction = &databaseSortById;
	}else if(!strcmp(sort_key,"plat")){
		sortFunction = &databaseSortBySalary;
	}else if(!strcmp(sort_key,"pozicia")){
		sortFunction = &databaseSortByPosition;
	}else if(!strcmp(sort_key,"datum")){
		sortFunction = &databaseSortByBirth;
	}else{
		return 0;
	}
	// vytriedit pole
	qsort(list,n,sizeof(Employee*),sortFunction);
	return 1;
}
// porovnat retazec
int compareByString(char *str1, char *str2, Compare *compare){
	
	if(compare->compare_type == 0)
		return (strstr(str1,str2) != NULL);
	else if(compare->compare_type == 3)
		return (strstr(str1,str2) == NULL);
	else if(compare->compare_type == 1)
		return strcmp(str2,str1)>0;
	else
		return strcmp(str2,str1)<0;
		
}
// porovnat integer
int compareByInt(int num1, int num2, Compare *compare){
	
	if(compare->compare_type == 0)
		return num1 == num2;
	else if(compare->compare_type == 3)
		return num1 != num2;
	else if(compare->compare_type == 1)
		return num1 < num2;
	else
		return num1 > num2;
}
// porovnat double
int compareByDouble(double num1, double num2, Compare *compare){
	
	if(compare->compare_type == 0)
		return num1 == num2;
	else if(compare->compare_type == 3)
		return num1 != num2;
	else if(compare->compare_type == 1)
		return num1 < num2;
	else
		return num1 > num2;
}
// skusit porovnat podla podmienky
int compareEmployee(Employee *employee, Compare *compare){
	
	if(!strcmp(compare->compare_key,"meno")){
		return compareByString(employee->info.name,compare->compare_value,compare);
			
	}else if(!strcmp(compare->compare_key,"id")){
		return compareByInt(employee->ID,atoi(compare->compare_value),compare);
		
	}else if(!strcmp(compare->compare_key,"plat")){
		return compareByDouble(employee->salary,atoi(compare->compare_value),compare);
		
	}else if(!strcmp(compare->compare_key,"pozicia")){
		return compareByString(employee->position,compare->compare_value,compare);
			
	}else if(!strcmp(compare->compare_key,"datum")){
		return compareByInt(dateToNumber(employee->info.birth),atoi(compare->compare_value),compare);
		
	}
	
	return -1;
	
}
// skratit pole podla podmienky
Employee** prune(Employee **list, int *n, Compare *compare, int freeMemory){
	// roztriedi pole ak je pozadovane
	if(compare->sort_key[0] != 0)
		if(!sort(list,*n,compare->sort_key))
			return 0;
	// pripravy novy list
	Employee **newList = malloc(*n * sizeof(Employee*));
	int newSize = 0;
	// prejde cele pole
	int result = 0;
	for(int i=0; i<*n; i++){
		// maximalna pozadovana dlzka pola
		if(compare->amount!=0 && newSize >= compare->amount)
			break;
		// porovna podmienku ak je
		if(compare->compare_key[0] != 0)
			result = (compareEmployee(list[i],compare));
		else
			result = 1;
		if(result < 0) {
			// chyba
			return 0;
		}else if(result){
			// prida do noveho
			newList[newSize] = list[i];
			newSize++;
		}else if(freeMemory){
			free(list[i]);
		}
	}
	// skopiruje pole
	*n = newSize;
	free(list);
	
	return newList;
}

