/**
 * Modulo saveGame
 * DESCRIZIONE: Modulo per il salvataggio di una partita
 *
 */

#ifndef _SAVE_GAME_H
#define _SAVE_GAME_H

#include "../../../struct/round/Round.h"
#include "../../../global/GlobalConstants.h"
#include "../../converter/converter.h"


void saveGame(Round round, int numFile);


#endif /* _SAVE_GAME_H */
