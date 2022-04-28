#ifndef _MAPS_CONTROLLER_H
#define _MAPS_CONTROLLER_H

#include "../../global/GlobalConstants.h"
#include "../../struct/player/Player.c"
#include "../../struct/round/Round.c"    


Player loadVerticalAxis(Player player, int startColumn, int startRow, char label, int shipSize);
Player loadHorizontalAxis(Player player, int startColumn, int startRow, char label, int shipSize);

//TODO: Inserire qui le funzioni di inserimento delle navi, con relativi controlli sull'inserimento, ricerca e 
// e gestione dei vari tipi di attacchi.  

int isImpossible(char cell[], char direction, char coords[], int size, char playground[TABLE_MAX][TABLE_MAX]);
int checkBoundaries(int row, int column, int size, char direction);
int checkCollisions(char playground[TABLE_MAX][TABLE_MAX], char direction, char coords[], int shipSize);

int checkVerticalCollisions(char playground[TABLE_MAX][TABLE_MAX], char coords[], int shiSize);
int checkHorizontalCollisions(char playground[TABLE_MAX][TABLE_MAX], char coords[], int shiSize);

Round hit(int row, int column, Round match);

void getFirstCell(char coords[], char cell[]);
void getLastCell(char coords[], char cell[]);

#endif /* _MAPS_CONTROLLER_H */