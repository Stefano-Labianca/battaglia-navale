#include <stdio.h>
#include <stdlib.h>

#include "./struct/player/Player.c"

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