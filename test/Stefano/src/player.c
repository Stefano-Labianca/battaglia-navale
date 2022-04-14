#include <stdio.h>
#include <stdlib.h>
#include "./grid.c"
#include "./ship.c"

#define SHIP_NUMB 15

typedef struct {
	int id;
	grid playground;
	grid heatMap;
	int longShots;
	int radar;
	int aistrike;
	int availableShips;
	ship ships[SHIP_NUMB];
}player;

int readId(player player);
grid readPlayground(player player);
grid readHeatMap(player player);
int readLongshots(player player);
int readRadar(player player);
int readAirstrike(player player);
int readAvailableShips(player player);
ship readShip(player player, int index);
player writeId(player player, int id);
player writePlayground(player player, grid playground);
player writeHeatMap(player player, grid heatMap);
player writeLongshots(player player, int longShots);
player writeRadar(player player, int radar);
player writeAirstrike(player player, int airstrike);
player writeAvailableShips(player player, int availableShips);
player writeShip(player player, int index, ship ship);

int readId(player player) {
	int id;
	id = player.id;
	return id;
}

grid readPlayground(player player) {
	grid playground;
	playground = player.playground;
	return playground;
}

grid readHeatMap(player player) {
	grid heatMap;
	heatMap = player.heatMap;
	return heatMap;
}

int readLongshots(player player) {
	int longShots;
	longShots = player.longShots;
	return longShots;
}

int readRadar(player player) {
	int radar;
	radar = player.radar;
	return radar;
}

int readAirstrike(player player) {
	int airstrike;
	airstrike = player.aistrike;
	return airstrike;
}

int readAvailableShips(player player) {
	int availableShips;
	availableShips = player.availableShips;
	return availableShips;
}

ship readShip(player player, int index) {
	ship ship;
	ship = player.ships[index - 1];
	return ship;
}

player writeId(player player, int id) {
	player.id = id;
	return player;
}

player writePlayground(player player, grid playground) {
	player.playground = playground;
	return player;
}

player writeHeatMap(player player, grid heatMap) {
	player.heatMap = heatMap;
	return player;
}

player writeLongshots(player player, int longShots) {
	player.longShots = longShots;
	return player;
}

player writeRadar(player player, int radar) {
	player.radar = radar;
	return player;
}

player writeAirstrike(player player, int airstrike) {
	player.aistrike = airstrike;
	return player;
}

player writeAvailableShips(player player, int availableShips) {
	player.availableShips = availableShips;
	return player;
}

player writeShip(player player, int index, ship ship) {
	player.ships[index - 1] = ship;
	return player;
}
