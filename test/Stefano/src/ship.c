#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIM_COORDS 6

typedef struct {
	char label;
	int sunk;
	int lifePoints;
	int size;
	char direction;
	char coords[DIM_COORDS];
} ship;

char readLabel(ship ship);
int readSunk(ship ship);
int readSize(ship ship);
int readLifePoints(ship ship);
char readDirection(ship ship);
void readCoords(ship ship, char coords[]);
ship writeLabel(ship ship, char label);
ship writeSunk(ship ship, int sunk);
ship writeSize(ship ship, int size);
ship writeLifePoints(ship ship, int lifePoints);
ship writeDirection(ship ship, char direction);
ship writeCoords(ship ship, char coords[]);

char readLabel(ship ship) {
	char label;
	label = ship.label;
	return label;
}

int readSunk(ship ship) {
	int sunk;
	sunk = ship.sunk;
	return sunk;
}

int readSize(ship ship) {
	int size;
	size = ship.size;
	return size;
}

int readLifePoints(ship ship) {
	int lifePoints;
	lifePoints = ship.lifePoints;
	return lifePoints;
}

char readDirection(ship ship) {
	char direction;
	direction = ship.direction;
	return direction;
}

void readCoords(ship ship, char coords[]) {
	strcpy(coords, ship.coords);
	return;
}

ship writeLabel(ship ship, char label) {
	ship.label = label;
	return ship;
}

ship writeSunk(ship ship, int sunk) {
	ship.sunk = sunk;
	return ship;
}

ship writeSize(ship ship, int size) {
	ship.size = size;
	return ship;
}

ship writeLifePoints(ship ship, int lifePoints) {
	ship.lifePoints = lifePoints;
	return ship;
}

ship writeDirection(ship ship, char direction) {
	ship.direction = direction;
	return ship;
}

ship writeCoords(ship ship, char coords[]) {
	strcpy(ship.coords, coords);
	return ship;
}
