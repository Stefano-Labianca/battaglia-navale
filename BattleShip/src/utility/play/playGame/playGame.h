/**
 * Modulo playGame
 * DESCRIZIONE: Contiene tutte le funzioni relative allo svolgimento di una partita
 */
#ifndef _PLAY_GAME_H
#define _PLAY_GAME_H

#include "../../../utility/converter/converter.h"
#include "../../../struct/round/Round.h"
#include "../../../struct/player/Player.h"
#include "../saveGame/savegame.h"

void playGame(Round round, int numFile);
Round newTurn(Round round);
char nextMoveChoice();
int rowChoice();
int columnChoice();

Round hit(int row, int column, Round match);
Round longShot(int row, int column, Round match);
char axisChoice();
Round airStrikeRow(Round match, int row);
Round airStrikeColumn(Round match, int column);
Round scan(int row, int column, Round match);
Round radar(Round match, int row, int column);


#endif /* _PLAY_GAME_H */
