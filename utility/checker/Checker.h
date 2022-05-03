#ifndef _CHECKER_H
#define _CHECKER_H

// #include "../../global/GlobalConstants.h"
#include "../../utility/converter/converter.h"

// #include "../../utility/maps_controller/MapsController.h"


int isImpossible(char cell[], char direction, char coords[], int size, char playground[TABLE_MAX][TABLE_MAX]);
int checkBoundaries(int row, int column, int size, char direction);
int checkCollisions(char playground[TABLE_MAX][TABLE_MAX], char coords[]);

void getFirstCell(char coords[], char cell[]);
void getLastCell(char coords[], char cell[]);

#endif /* _CHECKER_H */