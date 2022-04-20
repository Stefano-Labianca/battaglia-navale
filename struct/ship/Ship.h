#include "./global/GlobalCostant.h"

enum COORDS_CONSTANTS {
	SEPARATOR = '-',  
	COORD_SEPARETOR = '_',
	MAX_COORD_LEN = 7, 
	MAX_ROW_LEN = 3, 
	MAX_DIM_COORDS = 11
};

typedef struct Ship {
	char label;
	int lifePoints;
	int size;
	char coords[MAX_COORD_LEN];
} Ship;


char readLabel(Ship ship);
int readSize(Ship ship);
int readLifePoints(Ship ship);
void readCoords(Ship ship, char coords[]);

Ship writeLabel(Ship ship, char label);
Ship writeSize(Ship ship, int size);
Ship writeLifePoints(Ship ship, int lifePoints);
Ship writeCoords(Ship ship, char coords[]);

char getColumn();
char getDirection();
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


