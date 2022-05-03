#ifndef _ROUND_H
#define _ROUND_H

#include "../../struct/player/Player.h"
#include "../../struct/ship/Ship.h"


typedef struct Round {
    Player activePlayer;
    Player passivePlayer;
    int gameRound;
    int whoPlay;
    int pause;
} Round;


int getGameRound(Round round);
int getWhoPlay(Round round);
int getPause(Round round);
Player getActivePlayer(Round round);
Player getPassivePlayer(Round round);

Round setGameRound(Round round, int gameRound);
Round setWhoPlay(Round round, int whoPlay);
Round setPause(Round round, int pause);
Round setActivePlayer(Round round, Player activePlayer);
Round setPassivePlayer(Round round, Player passivePlayer);

#endif /* _ROUND_H */