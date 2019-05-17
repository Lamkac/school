// Jan Kucan 85917

#include <stdio.h>
#include <time.h>
#include "robot_race.h"

int main(int argc, char* argv[]){
	
	int robots_count = 10; // pocet hracov
	int race_width = 20;
	int race_height = 40;
	Track track;
	Robot robots[robots_count];
	
	srand(time(NULL)); // init random seed
	initTrack(&track,race_width,race_height); // init trate
	initRobots(robots,robots_count,&track); // init robotov
	
	
    do{
		// vypisat trat
		CLEAR_SCREEN();
		print(robots,robots_count,&track);

		SLEEP(200);
		
		for(int i = 0; i < robots_count; i++){
			
			// skontrolovat zrazku
			int col = isCollision(&robots[i],&track);
			if(col > -1){
				updateRobotDirection(&robots[i],&track,col);
			}
			// posunut robota
			updateRobotPosition(&robots[i]);
			// resetovat natocenie ak nieje
			updateRobotDirection(&robots[i],&track,-1);
			
		
		}
		
    }while(checkWin(robots,robots_count,&track)<0);
	
	printf("   Robot '%c' vyhral zavod",checkWin(robots,robots_count,&track)+'a');

    return 0;
}