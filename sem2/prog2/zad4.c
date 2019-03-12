// Jan Kucan 85917

#include <stdio.h>
#include <string.h>
// hlavickovy subor "sachoveho" modulu
#include "chess.h"

// makra pre vycistenie konzoly a uspanie
#ifdef _WIN32
#include <windows.h>
#define CLEAR_SCREEN() system("cls")
#define SLEEP(sleepMs) Sleep(sleepMs)
#else
#include <unistd.h>
#define CLEAR_SCREEN() system("clear")
#define SLEEP(sleepMs) usleep(sleepMs * 1000)
#endif

int check_move(char input[],int player){
	
	return move(input[1]-49,input[0]-97,input[3]-49,input[2]-97,player);
	
}

int main(){
	int player = WHITE_PLAYER_ID;
	char input[10];
	
	init_chessboard();
		
	while(1){
		//CLEAR_SCREEN();
		print_chessboard();
		
		printf("\n%s na tahu: ",(player == WHITE_PLAYER_ID)?"Biely":"Cierny");
		scanf("%s",input);
		
		if(!strcmp(input,"exit"))
			return 0;
		
		
		if(check_move(input,player)){
			if(player == WHITE_PLAYER_ID)
				player = BLACK_PLAYER_ID;
			else
				player = WHITE_PLAYER_ID;
		}
			
	}
	
    return 0;
}