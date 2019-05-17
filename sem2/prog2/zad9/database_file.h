// Jan Kucan 85917

#ifndef DATABASE_FILE
#define DATABASE_FILE

#define LINE_MAX_SIZE 512

// funkcie
Employee* loadEmployee(char* line); // vytvorit zamestnanca z textu
void saveEmployees(Employee **employees, int n, char* fileName); // ulozit zamestnancov
Employee** loadEmployees(int *n, char* fileName); // nacitat zamestnancov

#endif