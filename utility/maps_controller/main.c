#include <stdio.h>
#include <stdlib.h>


#include "../../struct/ship/Ship.c"

int main(void)
{
	Ship ship1;
	Ship ship2;

	Player p;
	// Player a;

	// Round match;

	p = createPlayer(p, 1);
	// a = createPlayer(a, 2);

	// match.activePlayer = a;
	// match.passivePlayer = p;

	char coord1[] = "E-4_E-6";
	char coord2[] = "C-2_E-2"; 	

	ship1 = createShip(3, 0, p.playground);
	p = loadHorizontalAxis(p, 4, 4, 'a', 3);


	ship2 = createShip(3, 1, p.playground);
	
	
	// match.passivePlayer = p;
	// match = hit(3, 2, match);


	// showMap(match.passivePlayer.playground);
	// showMap(match.activePlayer.heatMap);

	system("pause");
	return 0;
}
