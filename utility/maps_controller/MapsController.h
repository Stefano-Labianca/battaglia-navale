#ifndef _MAPS_CONTROLLER_H
#define _MAPS_CONTROLLER_H

#include "../../struct/round/Round.h"
// #include "../../struct/player/Player.h"
// #include "../../struct/ship/Ship.h"
// #include "../../utility/checker/Checker.h"


Player loadVerticalAxis(Player player, int startColumn, int startRow, char label, int shipSize);
Player loadHorizontalAxis(Player player, int startColumn, int startRow, char label, int shipSize);
Player buildPlayerNavy(Player player);

Round hit(int row, int column, Round match);
Round longShot(int row, int column, Round match);
char axisChoice();
Round airStrikeRow(Round match, int row);
Round airStrikeColumn(Round match, int column);
Round scan(int row, int column, Round match);
Round radar(Round match, int row, int column);



#endif /* _MAPS_CONTROLLER_H */