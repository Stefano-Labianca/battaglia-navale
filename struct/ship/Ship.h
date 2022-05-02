#ifndef _SHIP_H
#define _SHIP_H

#include "../../global/GlobalConstants.h"
#include "../../utility/converter/converter.h"

typedef struct Ship {
	char label;
	int lifePoints;
	int size;
	char coords[MAX_COORDS_RANGE];
	char direction;
} Ship;


char getLabel(Ship ship);
int getSize(Ship ship);
int getLifePoints(Ship ship);
void getCoords(Ship ship, char coords[]);
char getDirection(Ship ship);

Ship setLabel(Ship ship, char label);
Ship setSize(Ship ship, int size);
Ship setLifePoints(Ship ship, int lifePoints);
Ship setCoords(Ship ship, char coords[]);
Ship setDirection(Ship ship, char direction);


char getColumn();
char getShipDirection();
int isValidRow(int row);
void getRow(char row[]);

void buildShipCoordinate(char column, char row[], char coord[]);
void buildNextCoord(char direction, char startingCoord[], int shipSize, char nextCoord[]);
void buildVerticalCoord(char startingCoord[], int shipSize, char nextCoord[]);
void buildHorizontalCoord(char startingCoord[], int shipSize, char nextCoord[]);
void concatCoordinates(char first[], char second[], char dest[]); 

int pullColumn(Ship ship);
int pullRow(Ship ship);

Ship createShip(int size, int number, char playground[TABLE_MAX][TABLE_MAX]);

#endif /* _SHIP_H */
