// Jan Kucan 85917

#include <stdio.h>
#include <math.h>
#include "robot_race.h"


int random_number(int a, int b) {
	return rand() % (b - a + 1) + a;
}

// inicializacia pre trat
void initTrack(Track* track, int width, int height){
    
	track->width = (width>MAX_TRACK_WIDTH)?MAX_TRACK_WIDTH:width;
	track->height = (height>MAX_TRACK_HEIGHT)?MAX_TRACK_HEIGHT:height;
	
	int obs_count = height / (OBSTACLE_AREA_HEIGHT + ROBOT_SPEED);
	//int obs_count = 4;
	Obstacle obstacles[obs_count];
	
	for(int i=0; i<obs_count; i++){
		
		if(i>=MAX_OBSTACLES)
			break;
	
		// Y
		int randStartYoffset = rand()%(OBSTACLE_AREA_HEIGHT - ROBOT_SPEED); // nahodna Y v bloku pre prekazku
		int randStartY = i*(OBSTACLE_AREA_HEIGHT + ROBOT_SPEED) + 2 + randStartYoffset;
		int randHeight = random_number(ROBOT_SPEED, OBSTACLE_AREA_HEIGHT - randStartYoffset); // vyska bloku
		// X
		int randStartX = rand()%(width - ROBOT_SPEED - 1); // nahodne X aby bola aspon medzera pre jedneho robota
		int randWidth = random_number(ROBOT_SPEED, width - randStartX); // nahodna dlzka
		// init prekazku
		Obstacle obs = {randStartX,randStartY,randWidth,randHeight};
		track->obstacles[i] = obs;
		
	}
	// pocet
	track->obstacles_count = obs_count;
}

// Inicializacia robotov
void initRobots(Robot robots[], int n, Track* track){
    
	// vzdialenost pre robotov na zaciatku
	int dist = track->width/n;
	int start = dist/2;
	
	for(int i = 0; i < n; i++){
		
		Robot robot = {start+(i*dist),0,ROBOT_SPEED,90};
		robots[i] = robot;
		
	}
	
	
}

// vypis zavodu
void print(Robot robots[], int n, Track* track)
{
	// pole zavodu
	char race[track->width][track->height];
	// vyplnenie prazdneho pola
	for(int i = 0; i < track->width; i++){
		for(int j = 0; j < track->height; j++){
			race[i][j] = ' ';
			
		}
	}
	// vyplnenie prekazok
	for(int k = 0; k < track->obstacles_count; k++){
		
		Obstacle *obs = &track->obstacles[k];
		
		for(int i = obs->x; i < obs->x+obs->width; i++){
			for(int j = obs->y; j < obs->y+obs->height; j++){
				race[i][j] = 219;
			}
		}
		
	}
	// vyplnenie robotov
	for(int k = 0; k < n; k++){
		
		race[(int)robots[k].x][(int)robots[k].y] = 'a'+k;
		
	}
	
	// vypis trate
	printf("%*c%s\n",track->width/2-2,' ',"START");
	for(int i = 0; i < track->height; i++){
		printf("%c",179);
		for(int j = 0; j < track->width; j++){
			
			printf("%c",race[j][i]);
			
		}
		printf("%c\n",179);
	}
	printf("%*c%s\n",track->width/2-1,' ',"CIEL");
	
}

// aktualizuje poziciu robota
void updateRobotPosition(Robot* robot){
	
	robot->x += (robot->speed * cos(robot->angle*M_PI/180));
	robot->y += (robot->speed * sin(robot->angle*M_PI/180));
	
}

// upravy smer robota podla prekazky
void updateRobotDirection(Robot* robot, Track* track, int obstacle_id){
	
	// ak nieje id pre prekazku tak nastavy robota ist dole
	if(obstacle_id<0){
		robot->angle = 90;
		return;
	}
	
	// ak je prekazka uplne vpravo na kraji tak pojde dolava inak
	// ak je uplne vlavo alebo je prava strana prekazky blizsie tak pojde vpravo
	// inak pojde dolava
	if( track->obstacles[obstacle_id].x+track->obstacles[obstacle_id].width != track->width && ( track->obstacles[obstacle_id].x == 0 || robot->x > track->obstacles[obstacle_id].x + (track->obstacles[obstacle_id].width/2)) ){
		robot->angle = 0;
	}else{
		robot->angle = 180;
	}
	
}

// kontrola kolizie
int isCollision(Robot* robot, Track* track){
	
	Robot robotCheck = *robot; // skopiruje robota
	updateRobotPosition(&robotCheck); // posunie kopiu
	
    for(int i = 0; i < track->obstacles_count; i++){
		
		Obstacle *obs = &track->obstacles[i];
		// ak by sa zrazil vrati id
		if( robotCheck.x >= obs->x && robotCheck.x < obs->x+obs->width && robotCheck.y >= obs->y && robotCheck.y < obs->y+obs->height )
			return i;
		
	}
	
	// inak vrati -1
	return -1;
	
}

// kontrola vyhry
int checkWin(Robot robots[], int n, Track* track){
	
	for(int i = 0; i < n; i++){
		// ak robot je na konci trate
		if(robots[i].y > track->height - 1)
			return i;
	
	}
	
	return -1;
	
}
	
