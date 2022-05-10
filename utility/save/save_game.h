/**
 * File usato per la gestione del salvataggio del gioco e per il caricamento
 * dei dati delle partite salvate.
 */

#ifndef _SAVE_GAME_H
#define _SAVE_GAME_H

#include "../../struct/round/Round.h"


void saveGame(Round round, int numFile);


#endif /* _SAVE_GAME_H */