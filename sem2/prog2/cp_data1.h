// Jan Kucan 85917

#ifndef CP_DATA_H_INCLUDED
#define CP_DATA_H_INCLUDED

// matematicke konstanty
#define _USE_MATH_DEFINES

// pre Visual C++
#define _CRT_SECURE_NO_DEPRECATE

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

// pravidla cestovneho poriadku

#define DELTA 3 // casovy usek (v minutach) medzi dvomi po sebe iducimi zastavkami

#define PRVY_SPOJ_H 4 // hodina odchodu prveho spoja zo startovacej zastavky
#define PRVY_SPOJ_M 25 // minuta odchodu prveho spoja zo startovacej zastavky

#define POSLED_SPOJ_H 23 // posledna hodina, kedy linka premava

#define RANO_START 5 // hodina zaciatku rannej spicky
#define RANO_END 8 // hodina konca rannej spicky

#define POOBEDE_START 14 // hodina zaciatku poobednej spicky
#define POOBEDE_END 18 // hodina konca poobednej spicky

#define INTERVAL_NORMAL 20 // frekvencia premavania linky (v minutach) mimo spicky
#define INTERVAL_RANO 6 // frekvencia premavania linky (v minutach) v rannej spicke
#define INTERVAL_POOBEDE 10 // frekvencia premavania linky (v minutach) v poobednej spicke

#endif // CP_DATA_H_INCLUDED
