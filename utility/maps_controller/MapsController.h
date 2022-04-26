#ifndef _MAPS_CONTROLLER_H
#define _MAPS_CONTROLLER_H

#include "../../global/GlobalConstants.h"
#include "../../struct/ship/Ship.h"
#include "../../struct/player/Player.h"

enum PLAYGROUND_SYMBOLS { WATER = '~', PLAYGROUND_HIT = 'X', SUNK = '*' };
enum HEAT_MAP_SYMBOLS { UNKNOWN = '?',  HEAT_MAP_HIT = '!' };

void createPlayground(char playground[TABLE_MAX][TABLE_MAX]);
void createHeatMap(char heatMap[TABLE_MAX][TABLE_MAX]);
void showMap(char map[TABLE_MAX][TABLE_MAX]);

Player loadVerticalAxis(Player player, int startColumn, int startRow, int label, int shipSize);
Player loadHorizontalAxis(Player player, int startColumn, int startRow, int label, int shipSize);

//TODO: Inserire qui le funzioni di inserimento delle navi, con relativi controlli sull'inserimento, ricerca e 
// e gestione dei vari tipi di attacchi.  

#endif