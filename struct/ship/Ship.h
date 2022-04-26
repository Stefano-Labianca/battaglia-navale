#ifndef _SHIP_H
#define _SHIP_H

#include "../../global/GlobalConstants.h"

enum COORDS_CONSTANTS {
	SEPARATOR = '-',  
	COORD_SEPARETOR = '_',
	MAX_COORD_LEN = 7, 
	MAX_ROW_LEN = 3, 
	MAX_COORDS_RANGE = 11
};

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
int calculateBoundaries(int start, int end);
void buildShipCoordinate(char column, char row[], char coord[]);
void buildNextCoord(char direction, char startingCoord[], int shipSize, char nextCoord[]);
void buildVerticalCoord(char startingCoord[], int shipSize, char nextCoord[]);
void buildHorizontalCoord(char startingCoord[], int shipSize, char nextCoord[]);
void concatCoordinates(char first[], char second[], char dest[]); 
char getCharColumn(int column);
int getIntegerColumn(char column);

int pullColumn(Ship ship);
int pullRow(Ship ship);

#endif