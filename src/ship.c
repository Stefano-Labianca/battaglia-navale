#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIM_COORDS 6

typedef struct Ship{
	char label;
	int sunk;
	int lifePoints;
	int size;
	char direction;
	char coords[DIM_COORDS];
} Ship;

char readLabel(Ship ship);
int readSunk(Ship ship);
int readSize(Ship ship);
int readLifePoints(Ship ship);
char readDirection(Ship ship);
void readCoords(Ship ship, char coords[]);
Ship writeLabel(Ship ship, char label);
Ship writeSunk(Ship ship, int sunk);
Ship writeSize(Ship ship, int size);
Ship writeLifePoints(Ship ship, int lifePoints);
Ship writeDirection(Ship ship, char direction);
Ship writeCoords(Ship ship, char coords[]);

char readLabel(Ship ship) {
	char label;
	label = ship.label;

	return label;
}

int readSunk(Ship ship) {
	int sunk;
	sunk = ship.sunk;

	return sunk;
}

int readSize(Ship ship) {
	int size;
	size = ship.size;

	return size;
}

int readLifePoints(Ship ship) {
	int lifePoints;
	lifePoints = ship.lifePoints;

	return lifePoints;
}

char readDirection(Ship ship) {
	char direction;
	direction = ship.direction;
	
	return direction;
}

void readCoords(Ship ship, char coords[]) {
	strcpy(coords, ship.coords);
	return;
}

Ship writeLabel(Ship ship, char label) {
	ship.label = label;
	return ship;
}

Ship writeSunk(Ship ship, int sunk) {
	ship.sunk = sunk;
	return ship;
}

Ship writeSize(Ship ship, int size) {
	ship.size = size;
	return ship;
}

Ship writeLifePoints(Ship ship, int lifePoints) {
	ship.lifePoints = lifePoints;
	return ship;
}

Ship writeDirection(Ship ship, char direction) {
	ship.direction = direction;
	return ship;
}

Ship writeCoords(Ship ship, char coords[]) {
	strcpy(ship.coords, coords);
	return ship;
}
