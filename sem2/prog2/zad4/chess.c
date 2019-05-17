// Jan Kucan 85917

#include "chess.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

// Definicia globalnej sachovnice
int chessboard[L][L];
const char UNITS_BLACK[] = {' ','p','v','j','s','d','k'};
const char UNITS_WHITE[] = {' ','P','V','J','S','D','K'};

// Funkcia na vykreslenie sachovnice (pracuje s globalnou sachovnicou)
void print_chessboard(){
	printf("\n             CIERNY\n\n");
	for(int i = L-1; i >= 0; i--){
		printf(" %d  ",i+1);
		
		for(int j = 0; j < L; j++)
			printf("[%c]",(chessboard[i][j]>0)?UNITS_WHITE[chessboard[i][j]]:UNITS_BLACK[abs(chessboard[i][j])]);
		
		printf("\n");
	}
	printf("     a  b  c  d  e  f  g  h \n\n             BIELY\n");
}

// Funkcia na pociatocne rozostavenie figurok na sachovnici
void init_chessboard(){
	for(int i = 0; i < L; i++){
		for(int j = 0; j < L; j++){
			
			switch(i){
				case 1:
					chessboard[i][j] = W_PAWN;
					break;
				case L-2:
					chessboard[i][j] = B_PAWN;
					break;
				case 0:
				
					switch(j){
						case 0:
						case L-1:
							chessboard[i][j] = W_ROOK;
							break;
						case 1:
						case L-2:
							chessboard[i][j] = W_KNIGHT;
							break;
						case 2:
						case L-3:
							chessboard[i][j] = W_BISHOP;
							break;
						case 3:
							chessboard[i][j] = W_QUEEN;
							break;
						case 4:
							chessboard[i][j] = W_KING;
					}
					
					break;
				case L-1:
				
					switch(j){
						case 0:
						case L-1:
							chessboard[i][j] = B_ROOK;
							break;
						case 1:
						case L-2:
							chessboard[i][j] = B_KNIGHT;
							break;
						case 2:
						case L-3:
							chessboard[i][j] = B_BISHOP;
							break;
						case 3:
							chessboard[i][j] = B_QUEEN;
							break;
						case 4:
							chessboard[i][j] = B_KING;
					}
					
					break;
				default:
				chessboard[i][j] = EMPTY_SQUARE;
			}
		}
	}
		
}

// ak je na policku nepriatel
int check_enemy(int row, int col, int p_id){
	return ((chessboard[row][col] > 0 && p_id == BLACK_PLAYER_ID)||(chessboard[row][col] < 0 && p_id == WHITE_PLAYER_ID));
}

// ak je na policku nepriatel alebo je prazdne
int check_enemy_or_empty(int row, int col, int p_id){
	return ((chessboard[row][col] >= 0 && p_id == BLACK_PLAYER_ID)||(chessboard[row][col] <= 0 && p_id == WHITE_PLAYER_ID));
}

int move_pawn(int srow, int scol, int trow, int tcol, int p_id){
	int way = 1;
	if(p_id == WHITE_PLAYER_ID)
		way = -1;
		
	// ak sa pohybuje iba do predu o jedno a nestoji tam figurka
	if(scol == tcol && srow == trow+(1*way) && chessboard[trow][tcol] == 0)
		return 1;
	
	// ak sa pohybuje na zaciatku o dve a nestoji pred nim ziadna figurka
	if(scol == tcol && srow == trow+(2*way) && ((srow == L-2 && p_id == BLACK_PLAYER_ID)||(srow == 1 && p_id == WHITE_PLAYER_ID)) &&  chessboard[trow+(1*way)][tcol] == 0 && chessboard[trow][tcol] == 0)
		return 1;
	
	// ak ide vyhadzovat
	if((scol == tcol+1 || scol == tcol-1) && srow == trow+(1*way) && check_enemy(trow,tcol,p_id))
		return 1;
	
	return 0;
}

int move_rook(int srow, int scol, int trow, int tcol, int p_id){
	// ak sa bohybuje po stlpci
	if(srow == trow){
		// nastavenia smeru
		int way = 1;
		if(tcol < scol)
			way = -1;
		// kontrola pohybu
		for(int i = scol+(1*way); i != tcol; i+=way){
			if(chessboard[srow][i] != 0)
				return 0;
		}
		
		return 1;
	}
	// ak sa pohybuje po riadkoch
	else if(scol == tcol){
		// nastavenia smeru
		int way = 1;
		if(trow < srow)
			way = -1;
		// kontrola pohybu
		for(int i = srow+(1*way); i != trow; i+=way){
			if(chessboard[i][scol] != 0)
				return 0;
		}
		
		return 1;
	}
	
	return 0;
}

int move_knight(int srow, int scol, int trow, int tcol, int p_id){
	return ((abs(srow-trow)==1&&abs(scol-tcol)==2)||(abs(srow-trow)==2&&abs(scol-tcol)==1));
}

int move_bishop(int srow, int scol, int trow, int tcol, int p_id){
	// ak jeho cesta nieje diagonalne
	if(abs(srow-trow)!=abs(scol-tcol))
		return 0;
	// nastavenia smeru
	int way_col = 1;
	if(tcol < scol)
		way_col = -1;
	int way_row = 1;
	if(trow < srow)
		way_row = -1;
	// kontrola pohybu
	for(int i = 1; i < abs(srow-trow); i++){
		if(chessboard[srow+(i*way_row)][scol+(i*way_col)] != 0)
			return 0;
	}
	
	return 1;
}

int move_queen(int srow, int scol, int trow, int tcol, int p_id){
	// skus sa pohnut ako veza a ak nepojde tak skus strelca
	if(!move_rook(srow,scol,trow,tcol,p_id))
		return move_bishop(srow,scol,trow,tcol,p_id);
	return 1;
	
}

int move_king(int srow, int scol, int trow, int tcol, int p_id){
	return(abs(srow-trow)<=1&&abs(scol-tcol)<=1);
}

int move(int srow, int scol, int trow, int tcol, int p_id){
	
	// ak su suradnice vo vnutri
	if (!((srow >= 0 && srow < L)&&(scol >= 0 && scol < L)&&(trow >= 0 && trow < L)&&(tcol >= 0 && tcol < L))){
		return 0;
	}
	
	// ak je to jeho figurka
	if (!((p_id==BLACK_PLAYER_ID && chessboard[srow][scol]<0) || (p_id==WHITE_PLAYER_ID && chessboard[srow][scol]>0))){
		return 0;
	}
	
	// ak ciel nieje platny
	if(!check_enemy_or_empty(trow,tcol,p_id))
		return 0;
	
	int result = 0;
			
	switch(abs(chessboard[srow][scol])){
		case 1:
			result = move_pawn(srow, scol, trow, tcol, p_id);
			break;
		case 2:
			result = move_rook(srow, scol, trow, tcol, p_id);
			break;
		case 3:
			result = move_knight(srow, scol, trow, tcol, p_id);
			break;
		case 4:
			result = move_bishop(srow, scol, trow, tcol, p_id);
			break;
		case 5:
			result = move_queen(srow, scol, trow, tcol, p_id);
			break;
		case 6:
			result = move_king(srow, scol, trow, tcol, p_id);
			break;
	}
	
	if(result){
		chessboard[trow][tcol] = chessboard[srow][scol];
		chessboard[srow][scol] = EMPTY_SQUARE;
	}
	
	return result;
}
