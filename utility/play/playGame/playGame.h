#ifndef _PLAY_GAME_H
#define _PLAY_GAME_H

#include "../../../utility/maps_controller/MapsController.h"
#include "../../../utility/converter/converter.h"

void playGame(Round round, int numFile);
Round newTurn(Round round);
char nextMoveChoice();
int rowChoice();
int columnChoice();

#endif /* _PLAY_GAME_H */
