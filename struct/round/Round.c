#include <stdio.h>
#include <stdlib.h> 

#include "./Round.h"


/**
 * @brief Leggere il numero del turno
 * 
 * @param round Contiene le informazioni relative al turno corrente (player che attacca, player che subisce, numero del turno)
 * @return Numero del turno 
 */
int getGameRound(Round round)
{
    int gameRound;
    gameRound = round.gameRound;
    return gameRound;
}



/**
 * @brief Leggere il player attaccante
 * 
 * @param round Contiene le informazioni relative al turno corrente (player che attacca, player che subisce, numero del turno) 
 * @return Player attaccante 
 */
Player getActivePlayer(Round round)
{
    Player activePlayer;
    activePlayer = round.activePlayer;

    return activePlayer;
}



/**
 * @brief Leggere il player che subisce
 * 
 * @param round Contiene le informazioni relative al turno corrente (player che attacca, player che subisce, numero del turno) 
 * @return Player che subisce gli attacchi 
 */
Player getPassivePlayer(Round round)
{
    Player passivePlayer;
    passivePlayer = round.passivePlayer;

    return passivePlayer;
}



/**
 * @brief Modificare il numero del turno
 * 
 * @param round Contiene le informazioni relative al turno corrente (player che attacca, player che subisce, numero del turno)
 * @param gameRound Numero del turno
 * @return Round modificato 
 */
Round setGameRound(Round round, int gameRound)
{
    round.gameRound = gameRound;
    return round;
}


/**
 * @brief Modificare il player attaccante
 * 
 * @param round Contiene le informazioni relative al turno corrente (player che attacca, player che subisce, numero del turno) 
 * @param activePlayer Player attaccante
 * @return Player attaccante aggiornato 
 */
Round setActivePlayer(Round round, Player activePlayer)
{
    round.activePlayer = activePlayer;
    return round;
}



/**
 * @brief Modificare il player che subisce
 * 
 * @param round Contiene le informazioni relative al turno corrente (player che attacca, player che subisce, numero del turno) 
 * @param passivePlayer Player che subisce
 * @return Player che subisce gli attacchi aggiornato  
 */
Round setPassivePlayer(Round round, Player passivePlayer)
{
    round.passivePlayer = passivePlayer;
    return round;
}