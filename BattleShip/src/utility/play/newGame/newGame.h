/**
 * Modulo newGame
 * DESCRIZIONE: Modulo per preparare il campo da gioco di una nuova partita
 *
 */
#ifndef _NEW_GAME_H
#define _NEW_GAME_H

#include "../playGame/playGame.h"
#include "../../../struct/round/Round.h"

void newGame(int numFile);
Player loadVerticalAxis(Player player, int startColumn, int startRow, char label, int shipSize);
Player loadHorizontalAxis(Player player, int startColumn, int startRow, char label, int shipSize);
Player buildPlayerNavy(Player player);

#endif /* _NEW_GAME_H */
