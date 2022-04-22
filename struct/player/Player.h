#ifndef _PLAYER_H
#define _PLAYER_H

#include "../ship/Ship.h" 

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

#endif