#ifndef _ROUND_H
#define _ROUND_H

#include "../../struct/player/Player.h"
typedef struct Round {
    Player activePlayer;
    Player passivePlayer;
    int gameRound;
    int whoPlay;
} Round;


int getGameRound(Round round);
int getWhoPlay(Round round);
Player getActivePlayer(Round round);
Player getPassivePlayer(Round round);

Round setGameRound(Round round, int gameRound);
Round setWhoPlay(Round roun, int whoPlay);
Round setActivePlayer(Round round, Player activePlayer);
Round setPassivePlayer(Round round, Player passivePlayer);

#endif /* _ROUND_H */