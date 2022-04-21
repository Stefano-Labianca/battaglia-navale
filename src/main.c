#include <stdio.h>
#include <stdlib.h>
#include "./grid.c"
#include "./ship.c"
#include "./player.c"


int main(void)
{

	Grid playground;
	Grid heatMap;
	player p;
	playground = createPlayground();
	printf("\nSTAMPA DELLA TUA MAPPA\n");
	printGrid(playground);
	heatMap = createHeatMap();
	printf("\nSTAMPA DELLA TUA HEATMAP\n");
	printGrid(heatMap);
	playground = fillPlayground(playground, p);
	system("pause");
	return 0;
}
