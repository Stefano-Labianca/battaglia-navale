#ifndef _PLAYER_H
#define _PLAYER_H

#include "../../struct/ship/Ship.h"

typedef struct Player {
	int id;
	char playground[TABLE_MAX][TABLE_MAX];
	char heatMap[TABLE_MAX][TABLE_MAX];
	int longShots;
	int radar;
	int aistrike;
	int availableShips;
	Ship ships[SHIP_NUMB];
} Player;


void createPlayground(char playground[TABLE_MAX][TABLE_MAX]);
void createHeatMap(char heatMap[TABLE_MAX][TABLE_MAX]);
void showMap(char map[TABLE_MAX][TABLE_MAX]);

int getId(Player player);
int getLongShots(Player player);
int getRadar(Player player);
int getAirstrike(Player player);
int getAvailableShips(Player player);
Ship getShip(Player player, int index);
void getPlayground(Player player, char playground[TABLE_MAX][TABLE_MAX]);
void getHeatMap(Player player, char heatMap[TABLE_MAX][TABLE_MAX]);


Player setId(Player player, int id);
Player setLongshots(Player player, int longShotsAmount);
Player setRadar(Player player, int radarAmount);
Player setAirstrike(Player player, int airstrikeAmount);
Player setAvailableShips(Player player, int availableShips);
Player setShip(Player player, int index, Ship ship);
Player setPlayground(Player player, char playground[TABLE_MAX][TABLE_MAX]);
Player setHeatMap(Player player, char heatMap[TABLE_MAX][TABLE_MAX]);

Player createPlayer(Player player, int id);

#endif /* _PLAYER_H */