// Jan Kucan 85917

#include <stdio.h>
#include "median_filter.h"

int main()
{
    int k; // pocet nacitanych prvkov vstupneho signalu (vrati funkcia 'loadData')
    double input[MAX_DATA_SIZE]; // vstupny signal
    double output[MAX_DATA_SIZE]; // vystupny prefiltrovany signal

	int count = loadData(input,MAX_DATA_SIZE);
	filterData(input,output,count,1);
	printData(output,count);

    return 0;
}