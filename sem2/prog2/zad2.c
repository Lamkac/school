// Jan Kucan 85917

// arena
#define ARENA_W 70 // without border d70
#define ARENA_H 16 // without border d16

// symbols
#define P_MONSTER '+'
#define P_DEAD_MONSTER '.'
#define P_HUNTER 'H'

#define BACKGROUND ' '

#define W_LINE 179
#define H_LINE 196
#define CORNER_RIGHT_TOP 191
#define CORNER_LEFT_TOP 218
#define CORNER_RIGHT_BOTTOM 217
#define CORNER_LEFT_BOTTOM 192

// settings
#define MONSTER_COUNT 2
#define MONSTER_PROXIMITY 2
#define HUNTER_STEP 3
#define MONSTER_STEP 2

// console colors
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_GRAY   "\x1b[90m"
#define ANSI_COLOR_RESET   "\x1b[0m"

// controlls
#define FORWARD 'w'
#define LEFT 'a'
#define RIGHT 'd'
#define QUIT 'q'

// macros for clearing console window and sleeping
#ifdef _WIN32
#include <windows.h>
#define CLEAR_SCREEN() system("cls")
#define SLEEP(sleepMs) Sleep(sleepMs)
#else
#include <unistd.h>
#define CLEAR_SCREEN() system("clear")
#define SLEEP(sleepMs) usleep(sleepMs * 1000)
#endif

// headers
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// unit scruct
struct Unit {
   float y;
   float x;
   float angle;
   int alive;
};

float get_new_x(float old_x, int alpha, int dist){
	
	return old_x + (dist * cos(alpha*M_PI/180));
}

float get_new_y(float old_y, int alpha, int dist){
	
	return old_y + (dist * sin(alpha*M_PI/180));
}

float distance(float x1, float y1, float x2, float y2){
	
	return sqrt( pow(x1-x2, 2) + pow(y1-y2, 2) );
}

float distance_units(struct Unit unit1,struct Unit unit2){
	
	return distance(unit1.x,unit1.y,unit2.x,unit2.y);
}

float infi(float *n, float max){
	
	if(*n > max)
		*n -= max;
	
	if (*n < 0)
		*n += max;
	
}

void print_between(char c, float n, float min, float max){
	if(n > min && n < max)
		printf("%c",c);
	else
		printf(" ");
}

int win_check(struct Unit monster[]){
	
	for(int i = 0; i < MONSTER_COUNT; i++){
		if(monster[i].alive)
			return 0;
	}
	
	return 1;
}

void print_arena(struct Unit hunter, struct Unit monster[], int end){
	
	CLEAR_SCREEN(); // clean console
    printf("ARENA SIZE: %dx%d\n", ARENA_W, ARENA_H); // arena size
    printf("(%c)    Hunter: (%5.2f,%5.2f) angle: %3.0f\n",P_HUNTER,hunter.x,hunter.y,hunter.angle); //hunter
	// all monsters
	for(int i = 0; i < MONSTER_COUNT; i++) {
		printf("(%c) Monster %d: (%5.2f,%5.2f) angle: %3.0f distance: %6.2f ",P_MONSTER,i+1,monster[i].x,monster[i].y,monster[i].angle,distance_units(hunter,monster[i]));
		if(!monster[i].alive)
			printf("DEAD");
		printf("\n");
	}
	
	// inverting Y-axis for both hunter and monster
    hunter.y = ARENA_H-1-hunter.y;
	for(int i = 0; i < MONSTER_COUNT; i++)
		monster[i].y = ARENA_H-1-monster[i].y;
	
	// main draw loop for x
	for(int i=-1; i<=ARENA_H; i++){
		
		// draw corners
		if(i == -1)
			printf("%c",CORNER_LEFT_TOP);
		else if (i == ARENA_H)
			printf("%c",CORNER_LEFT_BOTTOM);
		else
			printf("%c",W_LINE);
		
		// draw you won on center of screen
		if(end && i == ARENA_H/2){
			int left = (ARENA_W/2)-4;
			for(int j = 0;j < left; j++)
				printf(" ");
			printf("YOU WON!");
			for(int j = 0;j < ARENA_W-left-8; j++)
				printf(" ");
		}
		
		for(int j=0; j<ARENA_W; j++){
			
			// ignore center screen for win text
			if(end && i == ARENA_H/2)
				continue;
			
			// corners
			if(i<0 || i == ARENA_H){
				printf("%c",H_LINE);
				continue;
			}
			
			// draw hunter
			if(i == round(hunter.y) && j == round(hunter.x)) {
				printf(ANSI_COLOR_GREEN "%c" ANSI_COLOR_RESET,P_HUNTER);
			} else {
				// draw only one monster on one place
				int c = 0;
				for(int k = 0; k < MONSTER_COUNT; k++){
					if(i == round(monster[k].y) && j == round(monster[k].x)){
						
						c++;
						if(monster[k].alive)
							printf(ANSI_COLOR_RED "%c" ANSI_COLOR_RESET,P_MONSTER); // monster alive
						else
							printf(ANSI_COLOR_GRAY "%c" ANSI_COLOR_RESET,P_DEAD_MONSTER); // monster dead
						
						break;
					}
				}
				// if no monster or hunter draw empty space
				if(!c)
					printf("%c",BACKGROUND);
			}
		
		}
		
		// draw corners
		if(i == -1)
			printf("%c\n",CORNER_RIGHT_TOP);
		else if (i == ARENA_H)
			printf("%c\n",CORNER_RIGHT_BOTTOM);
		else
			printf("%c\n",W_LINE);
	}
	
	// inverting back Y-axis for monsters because using pointers for array
	for(int i = 0; i < MONSTER_COUNT; i++)
		monster[i].y = ARENA_H-1-monster[i].y;
	
	// list of controlls
	printf("Controls:       Angle (%.0f):\n",hunter.angle);
	printf(" %c - forward     ", FORWARD);
	// draw angle for hunter
	print_between('\\',hunter.angle,112.5,157.5);
	print_between('|',hunter.angle,67.5,112.5);
	print_between('/',hunter.angle,22.5,67.5);
	printf("\n");
	
	// list of controlls
	printf(" %c - left        ", LEFT);
	// draw angle for hunter
	print_between('-',hunter.angle,157.5,202.5);
	printf("%c", P_HUNTER);
	if(hunter.angle > 337.5 || hunter.angle < 22.5)
		printf("-");
	else
		printf(" ");
	printf("\n");
	
	// list of controlls
	printf(" %c - right       ", RIGHT);
	// draw angle for hunter
	print_between('/',hunter.angle,202.5,247.5);
	print_between('|',hunter.angle,247.5,292.5);
	print_between('\\',hunter.angle,292.5,337.5);
	printf("\n");
	
	//last controlls
	printf(" %c - quit        ", QUIT);
	printf("\n",W_LINE);
	
}

int main(){
	
	// suradnice lovca a priser
	struct Unit hunter, monster[MONSTER_COUNT];
    float x_H, y_H, a_H;
    float x_M, y_M, a_M;
	char c = FORWARD;
	
	srand(time(NULL)); // init random seed
	
	// placing the hunter randomly
	hunter.x = rand()%ARENA_W;
	hunter.y = rand()%ARENA_H;
	hunter.angle = rand()%360;

	// placing the monster randomly
	for(int i = 0; i < MONSTER_COUNT; i++){
		monster[i].x = rand()%ARENA_W;
		monster[i].y = rand()%ARENA_H;
		monster[i].angle = rand()%360;
		monster[i].alive = 1;
	}
		
	while(!win_check(monster)){
        // printing arena with stats
        print_arena(hunter,monster,0);
		
		//input
		printf("Input: ");
		scanf(" %c", &c);
		switch(c){
			case FORWARD:
				break;
			case LEFT:
				hunter.angle += 30;
				break;
			case RIGHT:
				hunter.angle -= 30;
				break;
			case QUIT:
				return 1; // stop game
			default:
				continue; // waiting for correct input
		}
		
		// new position for hunter
		hunter.x = get_new_x(hunter.x,hunter.angle,HUNTER_STEP);
		hunter.y = get_new_y(hunter.y,hunter.angle,HUNTER_STEP);
		// squeeze position and angle
		infi(&hunter.angle,360);
		infi(&hunter.x,ARENA_W-1);
		infi(&hunter.y,ARENA_H-1);
		
		// new position for monters
		for(int i = 0; i < MONSTER_COUNT; i++){
			if(!monster[i].alive)
				continue;
			
			// new random angle
			monster[i].angle = rand()%360;
			// new position
			monster[i].x = get_new_x(monster[i].x,monster[i].angle,MONSTER_STEP);
			monster[i].y = get_new_y(monster[i].y,monster[i].angle,MONSTER_STEP);
			// squeeze positions
			infi(&monster[i].x,ARENA_W-1);
			infi(&monster[i].y,ARENA_H-1);
			
			// kill if near player
			if(distance_units(hunter,monster[i])<MONSTER_PROXIMITY)
				monster[i].alive = 0;
		}
		
	};
	// print last one screen
    print_arena(hunter,monster,1);
	
}