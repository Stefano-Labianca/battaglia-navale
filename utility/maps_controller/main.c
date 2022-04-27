#include <stdio.h>
#include <stdlib.h>


#include "../../struct/ship/Ship.c"

int main(void)
{
	Ship ship1;
	Ship ship2;

	Player p;
	p = createPlayer(p, 1);

	char coord1[] = "E-4_E-6";
	char coord2[] = "C-2_E-2"; 	

	ship1 = createShip(3, 0, p.playground);
	p = loadVerticalAxis(p, 5, 4, 'a', 3);

	ship2 = createShip(3, 1, p.playground);
	p = loadHorizontalAxis(p, 3, 2, 'b', 3);

	showMap(p.playground);


	system("pause");
	return 0;
}
