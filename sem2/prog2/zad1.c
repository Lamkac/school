// Jan Kucan 85917

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// generovanie nahodneho cisla
int random_number(int a, int b) {
	return rand() % (b - a + 1) + a;
}

// skontroluje ci este bezia
int game_status(int runners[][2],int runners_count, int race_length){
	
	for(int i = 0; i < runners_count; i++){
		if(runners[i][1] >= race_length*100)
			return i+1;
	}
	
	return 0;
	
}

// vrati novu rychlost podla starej
int get_speed(int old_speed){
	
	// ak je rychlost 0 tak vrati novu rychlost
	if(!old_speed)
		return random_number(350,450);
	
	// ak nie tak prida nahodnu novu rychlost
	return old_speed + random_number(-5,20);
}

int obstacle_test(int runner_distance, int obstacles, int race_length){
	
	return (!((runner_distance / 100) % obstacles)) && ((runner_distance / 100) != race_length);
	
}

void print_header(int count){
	printf("|");
	for(int i = 0; i < count; i++){
		printf(" Runner%d |", i+1);
	}
	printf("\n|");
	for(int i = 0; i < count; i++){
		printf(" spd dis |");
	}
	printf("\n|");
	for(int i = 0; i < count; i++){
		printf("---------|");
	}
	printf("\n");
}

int main(){
	
	int runners_count = 2; // pocet bezcov
	int race_length = 400; // dlzka trate v metroch
	int obstacles = 50; // dlzka medzi prikazkami v metroch
	
	// pole bezcov
	int runners[runners_count][2];
	int winner;
	
	// inicializacia
	srand(time(NULL)); // init random seed
	for(int i = 0; i < runners_count; i++){
		runners[i][0] = 0;
		runners[i][1] = 0;
	}
	
	// vypise pekne co kde je v tabulke
	print_header(runners_count);
	
	//hlavny cyklus
	while(!(winner = game_status(runners,runners_count,race_length))){
		
		printf("|");
		for(int i = 0; i < runners_count; i++){
			
			// nastavu novu rychlost a posunie bezca
			runners[i][0] = get_speed(runners[i][0]);
			runners[i][1] += runners[i][0];
			
			// ak narazi do prekazky tak sa resetuje rychlost
			if(obstacle_test(runners[i][1], obstacles, race_length))
				runners[i][0] = 0;
			
			printf(" %3d %3d |", runners[i][0], runners[i][1]/100);
		
		}
		
		printf("\n");
		
	}
	
	printf("\nVyhral bezec cislo %d\n",winner);
	
	return 0;
}