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


int getId(Player player);
int getLongShots(Player player);
int getRadar(Player player);
int getAirstrike(Player player);
int getAvailableShips(Player player);
Ship getShip(Player player, int index);


Player setId(Player player, int id);
Player setLongshots(Player player, int longShotsAmount);
Player setRadar(Player player, int radarAmount);
Player setAirstrike(Player player, int airstrikeAmount);
Player setAvailableShips(Player player, int availableShips);
Player setShip(Player player, int index, Ship ship);

#endif