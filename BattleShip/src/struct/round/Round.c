#include <stdio.h>
#include <stdlib.h> 

#include "./Round.h"



/**
 * Funzione getGameRound
 * DESCRIZIONE: Leggere il numero del turno
 * 
 * INPUT
 * round - Rounde della partita da cui estrarre il numero di turno - Round - /
 * 
 * OUTPUT
 * gameRound - Turno di gioco - Numero intero - gameRound > 0
 * 
 * LAVORO
 * 
 */
int getGameRound(Round round)
{
    int gameRound;
    gameRound = round.gameRound;
    return gameRound;
}


/**
 * Funzione getWhoPlay
 * DESCRIZIONE: Restituisce l'identificatore del giocatore che deve giocare
 * 
 * INPUT
 * round - Round della partita da cui estrarre il giocatore che attacca - numero intero - /
 * 
 * OUTPUT
 * whoPlay - Indica chi e' il giocatore che attacca - Numero intero - 1 = attacca il player 1, 2 = attacca il player 2
 * 
 * LAVORO
 * 
 */
int getWhoPlay(Round round)
{
    int whoPlay;
    whoPlay = round.whoPlay;
    return whoPlay;
}


/**
 * Funzione getPause
 * DESCRIZIONE: La funzione indica se il gioco deve essere concluso o no
 * 
 * INPUT
 * round - Round della partita da cui estrarre il valore di pause - Round - /
 * 
 * OUTPUT
 * whoPlay - Indica se il gioco deve essere interrotto o meno - Numero intero - 1 = Uscire dalla partita,  0 = Continuare a giocare
 * 
 * LAVORO
 * 
 */
int getPause(Round round)
{
    int pause;
    pause = round.pause;
    return pause;
}


/**
 * Funzione getActivePlayer
 * DESCRIZIONE: Restituisce il giocatore che attacca
 * 
 * INPUT
 * round - Round della partita da cui estrarre il giocatore che attacca - Round - /
 * 
 * OUTPUT
 * activePlayer - Player che attacca - Player - /
 * 
 * LAVORO
 * 
 */
Player getActivePlayer(Round round)
{
    Player activePlayer;
    activePlayer = round.activePlayer;

    return activePlayer;
}



/**
 * Funzione getPassivePlayer
 * DESCRIZIONE: Restituisce il giocatore che subisce l'attacco
 * 
 * INPUT
 * round - Round della partita da cui estrarre il giocatore che subisce l'attacco - Round - /
 * 
 * OUTPUT
 * passivePlayer - Player che subisce l'attacco - Player - /
 * 
 * LAVORO
 * 
 */
Player getPassivePlayer(Round round)
{
    Player passivePlayer;
    passivePlayer = round.passivePlayer;

    return passivePlayer;
}



/**
 * Funzione setGameRound
 * DESCRIZIONE: Imposta il round di gioco
 * 
 * INPUT
 * round - Round della partita a cui aggiornare il turno di gioco - Round - /
 * gameRound - Nuovo turno di gioco - Numero intero - gameRound > 0
 *
 * OUTPUT
 * round - Round della partita con il turno di gioco aggiornato - Round - /
 * 
 * LAVORO
 * 
 */
Round setGameRound(Round round, int gameRound)
{
    round.gameRound = gameRound;
    return round;
}


/**
 * Funzione setWhoPlay
 * DESCRIZIONE: Imposta il giocatore che deve giocare
 * 
 * INPUT
 * round - Round della partita a cui aggiornare il giocatore che attacca - Round - /
 * whoPlay - Nuovo giocatore che attacca - Numero intero -  1 = Attacca il player 1, 2 = Attacca il player 2
 *
 * OUTPUT
 * Round - Round della partita con giocatore che attacca aggiornato - Round - /
 * 
 * LAVORO
 * 
 */
Round setWhoPlay(Round round, int whoPlay)
{
    round.whoPlay = whoPlay;
    return round;
}


/**
 * Funzione setPause
 * DESCRIZIONE: Imposta se il gioco deve continuare o si e' concluso
 * 
 * INPUT
 * round - Round della partita a cui aggiornare lo stato di pausa - Round - /
 * pause - Nuovo stato di pausa - Numero intero - 1 = Uscire dalla partita,  0 = Continuare a giocare
 *
 * OUTPUT
 * Round - Round della partita con lo stato di pausa aggiornato - Round - /
 * 
 * LAVORO
 * 
 */
Round setPause(Round round, int pause) {
    round.pause = pause;
    return round;
}


/**
 * Funzione setActivePlayer
 * DESCRIZIONE: Imposta il giocatore che deve attaccare
 * 
 * INPUT
 * round - Round della partita in cui aggiornare il giocatore che attacca - Round - /
 * activePlayer - Nuovo giocatore che attacca - Player - /
 *
 * OUTPUT
 * Round - Round della partita con il giocatore che attacca aggiornato - Round - /
 * 
 * LAVORO
 * 
 */
Round setActivePlayer(Round round, Player activePlayer)
{
    round.activePlayer = activePlayer;
    return round;
}



/**
 * Funzione setPassivePlayer
 * DESCRIZIONE: Imposta il giocatore che deve subire l'attacco
 * 
 * INPUT
 * round - Round della partita in cui aggiornare il giocatore che subisce l'attacco - Round - /
 * activePlayer - Nuovo giocatore che subisce l'attacco - Player - /
 *
 * OUTPUT
 * Round - Round della partita con il giocatore che subisce l'attacco aggiornato - Round - /
 * 
 * LAVORO
 * 
 */
Round setPassivePlayer(Round round, Player passivePlayer)
{
    round.passivePlayer = passivePlayer;
    return round;
}
