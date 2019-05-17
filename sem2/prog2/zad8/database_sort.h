// Jan Kucan 85917

#ifndef DATABASE_SORT
#define DATABASE_SORT
	
// podmienky na skratenie
typedef struct {
	int amount;
	char sort_key[100];
	char compare_key[100];
	char compare_value[100];
	int compare_type;
} Compare;

int compareEmployee(Employee *employee, Compare *compare); // skusit porovnat podla podmienky
int sort(Employee list[], int n, char* sort_key); // roztriedit pole
int prune(Employee list[], int *n, Compare *compare); // skratit pole podla podmienky

#endif