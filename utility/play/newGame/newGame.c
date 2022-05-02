#include <stdlib.h>
#include <stdio.h>

#include "./newGame.h"
#include "../playGame/playGame.h"
#include "../../../struct/round/Round.h"
#include "../../../struct/player/Player.h"
#include "../../../global/GlobalConstants.h"
#include "../../maps_controller/MapsController.h"

void newGame(int numFile)
{
    Round round;
    int whoPlay;
    int turn;
    int id;
    Player player1;
    Player player2;
    char map[TABLE_MAX][TABLE_MAX];
    int pause;

    turn = 1;
    whoPlay = 1;
    pause = 0;

    round = setGameRound(round, turn);
    round = setWhoPlay(round, whoPlay);
    round = setPause(round, pause);

    printf("CREAZIONE DI PLAYER1\n");
    id = 1;
    player1 = createPlayer(player1, id);
    player1 = buildPlayerNavy(player1);

    printf("\nSTAMPA DEL PLAYGROUND\n");
    getPlayground(player1, map);
    showMap(map);


    printf("CREAZIONE DI PLAYER2\n");
    id = 2;
    player2 = createPlayer(player2, id);
    player2 = buildPlayerNavy(player2);

    printf("\nSTAMPA PLAYGROUND\n");
    getPlayground(player2, map);
    showMap(map);


    round = setActivePlayer(round, player1);
    round = setPassivePlayer(round, player2);

    playGame(round,numFile);
    return;
}