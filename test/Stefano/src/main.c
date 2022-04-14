#include <stdio.h>
#include <stdlib.h>
#include "./grid.c"
#include "./ship.c"
#include "./player.c"
#include "./otherFunctions.c"

int main(void) {

		grid playground;
		grid heatMap;
		player p;
		playground=createPlayground();
		printf("\nSTAMPA DELLA TUA MAPPA\n");
		printGrid(playground);
		heatMap=createHeatMap();
		printf("\nSTAMPA DELLA TUA HEATMAP\n");
		printGrid(heatMap);
		playground=fillPlayground(playground,p);
		system("pause");
		return 0;
	}
