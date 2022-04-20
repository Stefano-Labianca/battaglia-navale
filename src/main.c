#include <stdio.h>
#include <stdlib.h>
// #include "./Grid.c"
// #include "./Ship.c"
// #include "./Player.c"
#include "./otherFunctions.c"

int main(void)
{

	char row[3];
	char coord[MAX_COORD_LEN];
	char col = getColumn();
	getRow(row);
	buildShipCoordinate(col, row, coord);

	char nextCoord[MAX_COORD_LEN];
	buildNextCoord('O', coord, 4, nextCoord);

	// printf("Prossima Coordinata: %s\n", nextCoord);

	// printf("Colonna Numero: %d \nColonna Carattere: %c\n", getIntegerColumn('K'), getCharColumn(11));
	char completeCoord[MAX_DIM_COORDS];
	concatCoordinates(coord, nextCoord, completeCoord);
	printf("Coodinata Completa: %s\n\n", completeCoord);
	

	system("pause");
	return 0;
}
