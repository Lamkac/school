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

#define DELTA 6 // casovy usek (v minutach) medzi dvomi po sebe iducimi zastavkami

#define PRVY_SPOJ_H 5 // hodina odchodu prveho spoja zo startovacej zastavky
#define PRVY_SPOJ_M 0 // minuta odchodu prveho spoja zo startovacej zastavky

#define POSLED_SPOJ_H 22 // posledna hodina, kedy linka premava

#define RANO_START 6 // hodina zaciatku rannej spicky
#define RANO_END 9 // hodina konca rannej spicky

#define POOBEDE_START 13 // hodina zaciatku poobednej spicky
#define POOBEDE_END 17 // hodina konca poobednej spicky

#define INTERVAL_NORMAL 15 // frekvencia premavania linky (v minutach) mimo spicky
#define INTERVAL_RANO 8 // frekvencia premavania linky (v minutach) v rannej spicke
#define INTERVAL_POOBEDE 12 // frekvencia premavania linky (v minutach) v poobednej spicke

#endif // CP_DATA_H_INCLUDED
