#ifndef _MAPS_CONTROLLER_H
#define _MAPS_CONTROLLER_H

#include "../../global/GlobalConstants.h"
#include "../../struct/player/Player.c"
#include "../../struct/round/Round.c"    

Player loadVerticalAxis(Player player, int startColumn, int startRow, char label, int shipSize);
Player loadHorizontalAxis(Player player, int startColumn, int startRow, char label, int shipSize);
Player buildPlayerNavy(Player player);

Round hit(int row, int column, Round match);
Round longShot(int row, int column, Round match);
Round airStrikeRow(Round match, int row);
Round airStrikeColumn(Round match, int column);
Round scan(int row, int column, Round match);
Round radar(Round match, int row, int column);

int isImpossible(char cell[], char direction, char coords[], int size, char playground[TABLE_MAX][TABLE_MAX]);
int checkBoundaries(int row, int column, int size, char direction);
int checkCollisions(char playground[TABLE_MAX][TABLE_MAX], char coords[]);

void getFirstCell(char coords[], char cell[]);
void getLastCell(char coords[], char cell[]);

#endif /* _MAPS_CONTROLLER_H */