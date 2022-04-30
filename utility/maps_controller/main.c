#include <stdio.h>
#include <stdlib.h>

#include "../../struct/ship/Ship.c"

int main(void)
{
	Player p;
	Player p2;
	Round match;
	p = createPlayer(p, 1);

	p2 = createPlayer(p, 2);
	p2 = buildPlayerNavy(p2);

	showMap(p2.playground);

	match = setActivePlayer(match, p);
	match = setPassivePlayer(match, p2);

	printf("\n");
	printf("MOSSE");
	printf("\n");

	char c[1];
	int r;
	printf("INSERISCI COLONNA: ");
	scanf("%c", &c);
	printf("INSERISCI RIGA: ");
	scanf("%d", &r);
	int col;
	col = getIntegerColumn(c[0]);
	
	// match = longShot(r, col, match);
	// char input;
	// input = ' ';
	// input = axisChoice();
	// if (input == 'R') {
	// 	match = airStrikeRow(match, r);
	// } else if (input == 'C') {
	// 	match = airStrikeColumn(match, col);
	// }
	match = radar(match, r, col);
	p2 = getPassivePlayer(match);

	printf("P2 PLAYGROUND: \n");
	showMap(p2.playground);
	p = getActivePlayer(match);

	printf("\n\n P HEATMAP: \n");
	showMap(p.heatMap);
	
	system("pause");
	return 0;
}
