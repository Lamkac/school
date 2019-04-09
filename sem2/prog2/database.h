// Jan Kucan 85917

#ifndef DATABASE
#define DATABASE

typedef struct {
	int day;
	int month;
	int year;
} Birth;

typedef struct {
	char* meno;
	Birth birth;
} Udaje;

typedef struct  {
	int ID;
	int plat;
	int pozicia;
	Udaje udaje;
} Unit;

// funckie
Unit* generateUnits();
void printUnits(Unit* units);

#endif