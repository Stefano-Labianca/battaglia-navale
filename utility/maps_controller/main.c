#include <stdio.h>
#include <stdlib.h>


#include "../../struct/ship/Ship.c"

int main(void)
{
	Player p;
	
	p = createPlayer(p, 1);
	p = buildPlayerNavy(p);
	

	printf("\n\n\n-- RISULTATO FINALE --\n\n\n");
	showMap(p.playground);
	
	system("pause");
	return 0;
}
