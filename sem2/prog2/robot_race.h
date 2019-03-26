#ifndef ROBOT_RACE_H
#define ROBOT_RACE_H

#define _CRT_SECURE_NO_DEPRECATE
#define _USE_MATH_DEFINES

// MAKRA na vymazanie obsahu konzoly a uspanie programu
#ifdef _WIN32
#include <windows.h>
#define CLEAR_SCREEN() system("cls")
#define SLEEP(sleepMs) Sleep(sleepMs)
#else
#include <unistd.h>
#define CLEAR_SCREEN() system("clear")
#define SLEEP(sleepMs) usleep(sleepMs * 1000)
#endif

// KONSTANTY
#define MAX_ROBOTS 5 // max. pocet robotov na trati
#define MAX_OBSTACLES 100 // max. pocet prekazok na trati (zmente podla potreby)
#define MAX_TRACK_HEIGHT 50 // max. vyska trate (zmente podla potreby)
#define MAX_TRACK_WIDTH 150 // max. sirka trate (zmente podla potreby)
#define ROBOT_SPEED 1 // predvolena rychlost robota (dlzka jedneho kroku)

#define OBSTACLE_AREA_HEIGHT 3 // maximalna vyska prekazok

// Prekazka
typedef struct{
	int x, y;
	int width;
	int height;
} Obstacle;

// Robot
typedef struct{
	float x,y;
	float speed;
	float angle;
} Robot;

// Trat
typedef struct{
	int width;
	int height;
	int obstacles_count;
	Obstacle obstacles[100];
} Track;

// funckie
void initTrack(Track* track, int width, int height); // funkcia, ktora inicializuje trat pred zavodom
void initRobots(Robot robots[], int n, Track* track); // funkcia, ktora inicializuje robotov pred zavodom
void print(Robot robots[], int n, Track* track); // funkcia na vykreslenie aktualneho stavu trate
void updateRobotPosition(Robot* robot); // funkcia na aktualizaciu pozicie robota
void updateRobotDirection(Robot* robot, Track* track, int obstacle_id); // funkcia na aktualizaciu smeru robota
int isCollision(Robot* robot, Track* track); // funkcia, ktora zisti, ci pohyb robota aktualnym smerom nesposobi koliziu
int checkWin(Robot robots[], int n, Track* track); // skontroluje vyhru

#endif // ROBOT_RACE_H