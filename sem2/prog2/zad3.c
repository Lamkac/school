// Jan Kucan 85917

// menu size
#define MENU_WIDTH 60
#define OFFSET 30

// headers
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// link headers
//#include "cp_data1.h"
#include "cp_data2.h"
//#include "cp_data3.h"
//#include "cp_data4.h"

// print x time in row one char
void printRepeat(char c, int count){
	
	for(int i=0;i < count; i++)
		printf("%c",c);
	
}

// print x time in row ine char with border
void printRepeatWithBorder(char c, int count, char leftBorder, char rightBorder){
	
	printRepeat(' ',OFFSET);
	printf("%c",leftBorder);
	printRepeat(c,count-2);
	printf("%c\n",rightBorder);
	
}

// print simple text in borders
void printWithBorder(char border, int textOffset, char *text){
	
	printRepeat(' ',OFFSET);
	printf("%c",border);
	printRepeat(' ',textOffset);
	printf("%s",text);
	printRepeat(' ',MENU_WIDTH-2-textOffset-strlen(text));
	printf("%c\n",border);
	
}

// print numbered text in border
void printNumberedWithBorder(char border, int textOffset, int number, char *text){
	
	printRepeat(' ',OFFSET);
	printf("%c",border);
	printRepeat(' ',textOffset);
	printf("%d %s",number,text);
	printRepeat(' ',MENU_WIDTH-4-textOffset-strlen(text));
	printf("%c\n",border);
	
}

// print custom menu
void drawMenu(char *title, char **args, int count, int busStop){
	
	// title size
	int a = strlen(title);
	
	CLEAR_SCREEN();
	printf("\n");
	printRepeatWithBorder(205,MENU_WIDTH,201,187);
	printRepeatWithBorder(' ',MENU_WIDTH,186,186);
	printWithBorder(186,(MENU_WIDTH/2)-(strlen(title)/2),title); // title
	printRepeatWithBorder(' ',MENU_WIDTH,186,186);
	printRepeatWithBorder(205,MENU_WIDTH,204,185);
	printRepeatWithBorder(' ',MENU_WIDTH,186,186);
	
	// menu items
	for(int i=0;i<count;i++)
		printNumberedWithBorder(186,4,i+1,args[i]);
	
	printRepeatWithBorder(' ',MENU_WIDTH,186,186);
	printRepeatWithBorder(205,MENU_WIDTH,200,188);
	
	// last info and input
	printf("\n");
	printRepeat(' ',OFFSET+4);
	printf("Cislo zastavky: %d (+%d min.)\n",busStop,(busStop-1)*DELTA);
	printf("\n");
	printRepeat(' ',OFFSET+4);
	printf("Volba: ");
	
}

// draw CP or find closest time if time is no 0
void drawCP(int stopNumber, int c_hour, int c_minute){
	
	// calculate time with offset
	int time = PRVY_SPOJ_M + (stopNumber * DELTA);
	// time in first bus stop
	int realTime = PRVY_SPOJ_M;
	// first hour
	int hour = PRVY_SPOJ_H;
	
	// if draw CP
	if(!c_hour){
		CLEAR_SCREEN();
		printf("\n   Hodina %c Minuta\n ",179);
		printRepeat(205,40);
		printf("\n");
	}
	
	// loop every one hour
	for(int i=PRVY_SPOJ_H;i<=POSLED_SPOJ_H;i++){
		
		// draw hour
		if(!c_hour)
			printf("       %02d %c",i,179);
		
		// draw time with offset
		while(time < 60){
			
			// calculate no moved time and add offset
			if(realTime >= 60){
				realTime -= 60;
				time = realTime + (stopNumber * DELTA);
				hour++;
			}
			
			if(!c_hour){
				// draw minutes
				printf(" %02d",time);
			}else if( i >= c_hour && time >= c_minute) {
				// if found closest time
				printf("%02d:%02d",i,time);
				return;
			}
			
			// add time
			int addInterval = INTERVAL_NORMAL;
			if( hour >= RANO_START && hour <= RANO_END){
				addInterval=INTERVAL_RANO;
			}else if( hour >= POOBEDE_START && hour <= POOBEDE_END){
				addInterval=INTERVAL_POOBEDE;
			}
			realTime += addInterval;
			time += addInterval;
			
		}
		// next hour
		time -= 60;
		
		if(!c_hour)
			printf("\n");
		
	}
	// wait
	printf("\n\n    Stlac ENTER pre menu");
	getchar();
	
}

// menu for closes time
void closestTime(int busStop){
	
	int hour, minute;
	
	CLEAR_SCREEN();
	printf("\n");
	printRepeat(' ',OFFSET);
	printf("Hladanie najblizsieho spoju\n\n");
	printRepeat(' ',OFFSET);
	printf("Hodina: ");
	scanf(" %d",&hour);
	
	printRepeat(' ',OFFSET);
	printf("Minuta: ");
	scanf(" %d",&minute);
	
	printRepeat(' ',OFFSET);
	printf("najblizsi spoj: ");
	drawCP(busStop,hour,minute);
	
	printf("\n\n    Stlac ENTER pre menu");
	getchar();getchar();
	
}

// menu to set bus stop number
int getBusStopNumber(){
	
	int c;
	
	CLEAR_SCREEN();
	printf("\n");
	printRepeat(' ',OFFSET);
	printf("Zadajte cislo zastavky: ");
	
	scanf(" %d",&c);
	
	return c;
}

int main(){
	
	int c;
	int busStop = 1;
	// menu items
	char *menu[] = {"Vybrat zastavku","Ukazat cestovny poriadok","Najst najblizsi spoj","Koniec"};
	
	while(1){
		CLEAR_SCREEN();
		drawMenu("Cestovny poriadok MHD",menu,4,busStop);
		
		scanf("%d",&c);
		getchar();
		
		switch(c){
			case 1:
				busStop = getBusStopNumber();
				break;
			case 2:
				drawCP(busStop-1,0,0);
				break;
			case 3:
				closestTime(busStop-1);
				break;
			case 4:
				return 0;
		}
	}
	
}