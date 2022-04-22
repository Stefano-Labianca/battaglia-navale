#ifndef _ROUND_H
#define _ROUND_H

#include "../player/Player.h"

typedef struct Round {
    Player activePlayer;
    Player passivePlayer;
    int gameRound;
} Round;


int getGameRound(Round round);
Player getActivePlayer(Round round);
Player getPassivePlayer(Round round);

Round setGameRound(Round round, int gameRound);
Round setActivePlayer(Round round, Player activePlayer);
Round setPassivePlayer(Round round, Player passivePlayer);


#endif