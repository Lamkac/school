// Jan Kucan 85917

#ifndef CHESS_H
#define CHESS_H

// 1 Oznacenia na sachovnici

#define EMPTY_SQUARE 0  // policko bez figurky

// 1.1 Kody figuriek cierneho hraca

#define B_PAWN -1   // pesiak
#define B_ROOK -2   // veza
#define B_KNIGHT -3 // jazdec
#define B_BISHOP -4 // strelec
#define B_QUEEN -5  // dama
#define B_KING -6   // kral

// 1.2 Kody figuriek bieleho hraca

#define W_PAWN 1    // pesiak
#define W_ROOK 2    // veza
#define W_KNIGHT 3  // jazdec
#define W_BISHOP 4  // strelec
#define W_QUEEN 5   // dama
#define W_KING 6    // kral

// 2 Pomocne konstanty

#define L 8 // rozmer sachovnice
#define WHITE_PLAYER_ID 0 // id bieleho hraca
#define BLACK_PLAYER_ID 1 // id cierneho hraca

// 3 Deklaracie premennych
extern int chessboard[L][L]; // sachovnica
extern const char UNITS_BLACK[7];
extern const char UNITS_WHITE[7];

// 4 Deklaracie povinnych funkcii (rozhranie sachoveho modulu)
void print_chessboard(); // funkcia vypis aktualnej sachovnice
void init_chessboard(); // funkcia na pociatocne rozostavenie figurok na sachovnici
int move(int srow, int scol, int trow, int tcol, int p_id); // funkcia na realizaciu pohybu figurkou

#endif // CHESS_H