// Jan Kucan 85917

#ifndef DATABASE
#define DATABASE

// MAKRA na vymazanie obsahu konzoly a uspanie programu
#ifdef _WIN32
#include <windows.h>
#define CLEAR_SCREEN() system("cls")
#define SLEEP(sleepMs) Sleep(sleepMs)
#else
#include <unistd.h>
#define CLEAR_SCREEN() system("clear")
#define SLEEP(sleepMs) usleep(sleepMs * 1000)
#endif

// KONSTANTY
#define NAME_MAX_LEN 15
#define POSITION_MAX_LEN 15

static char NAME_CHARSET[] = "abcdefghijklmnopqrstuvwxyz";
static char* POSITIONS[] = {"developer","tester","analytik","web dizajner","db architekt"};
// datum
typedef struct {
	int day;
	int month;
	int year;
} Date;
// informacie
typedef struct {
	char name[NAME_MAX_LEN];
	Date birth;
} Information;
// zamenstanec
typedef struct  {
	int ID;
	double salary;
	char position[POSITION_MAX_LEN];
	Information info;
} Employee;

// funkcie
Employee* generateEmployee(); // vygenerovat zamestnanca
Employee** generateEmployees(int n); // vygenerovat n zamestnancov
void printEmployee(Employee *employees); // vypisat zamestnanca
void printEmployees(Employee **employees, int n); // vypisat zamestnancov
Employee** addEmployee(Employee **employees, int *n, Employee *employee); // pridat zamestnanca

#endif