#include <stdio.h>
#include <stdlib.h>
#include "./Ship.c"

#define SHIP_NUMB 15
#define GRID_SIZE 16 

typedef struct Player {
	int id;
	char playground[GRID_SIZE][GRID_SIZE];
	char heatMap[GRID_SIZE][GRID_SIZE];
	int longShots;
	int radar;
	int aistrike;
	int availableShips;
	Ship ships[SHIP_NUMB];
} Player;

int readId(Player player);

int readLongshots(Player player);
int readRadar(Player player);
int readAirstrike(Player player);
int readAvailableShips(Player player);
Ship readShip(Player player, int index);
Player writeId(Player player, int id);
Player writeLongshots(Player player, int longShots);
Player writeRadar(Player player, int radar);
Player writeAirstrike(Player player, int airstrike);
Player writeAvailableShips(Player player, int availableShips);
Player writeShip(Player player, int index, Ship ship);

// Player writePlayground(Player player, char playground[GRID_SIZE][GRID_SIZE]);
// Player writeHeatMap(Player player, char heatMap[GRID_SIZE][GRID_SIZE]);

int readId(Player player)
{
	int id;
	id = player.id;
	return id;
}


int readLongshots(Player player)
{
	int longShots;
	longShots = player.longShots;
	return longShots;
}

int readRadar(Player player)
{
	int radar;
	radar = player.radar;
	return radar;
}

int readAirstrike(Player player)
{
	int airstrike;
	airstrike = player.aistrike;
	return airstrike;
}

int readAvailableShips(Player player)
{
	int availableShips;
	availableShips = player.availableShips;
	return availableShips;
}

Ship readShip(Player player, int index)
{
	Ship ship;
	ship = player.ships[index - 1];
	return ship;
}

Player writeId(Player player, int id)
{
	player.id = id;
	return player;
}

//FIXME: Invece che Grid hai un array 2D di caratteri

// Player writePlayground(Player player, char playground[GRID_SIZE][GRID_SIZE])
// {
//  	player.playground[][] = playground[][];
//  	return player;
// }

// Player writeHeatMap(Player player, char heatMap[GRID_SIZE][GRID_SIZE])
// {
// 	player.heatMap = heatMap;
// 	return player;
// }

Player writeLongshots(Player player, int longShots)
{
	player.longShots = longShots;
	return player;
}

Player writeRadar(Player player, int radar)
{
	player.radar = radar;
	return player;
}

Player writeAirstrike(Player player, int airstrike)
{
	player.aistrike = airstrike;
	return player;
}

Player writeAvailableShips(Player player, int availableShips)
{
	player.availableShips = availableShips;
	return player;
}

Player writeShip(Player player, int index, Ship ship)
{
	player.ships[index - 1] = ship;
	return player;
}
