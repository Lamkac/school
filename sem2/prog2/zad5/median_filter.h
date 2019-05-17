// Jan Kucan 85917

#ifndef MEDIAN_FILTER_H
#define MEDIAN_FILTER_H

#define _CRT_SECURE_NO_DEPRECATE
#define _USE_MATH_DEFINES

// konstanty
#define MAX_DATA_SIZE 40000 // max. dlzka vstupneho signalu
#define MAX_W 100 // max. hodnota parametra 'w' (pozri funkciu filterData)
#define PRECISION 6 // pocet desatinnych miest pouzity pri zapisovani vysledneho prefiltrovaneho signalu

// POVINNE funkcie
int loadData(double* input, int n); // funkcia na nacitanie prvkov pola 'input' (vstupny signal) zo standardneho vstupu
void filterData(double* input, double *output, int k, int w); // funkcia na prefiltrovanie pola 'input' (vstupny signal) medianovym filtrom s oknom o velkosti 2*'w'+1
double median(double* data, int n); // funkcia, ktora vrati median pola 'data', ktore ma 'n' prvkov
void printData(double* data, int n); // funkcia, ktora vypise 'n' prvkov pola 'data' na standardny vystup

#endif // MEDIAN_FILTER_H