#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./loadGame.h"
#include "../../converter/converter.h"
#include "../../../struct/round/Round.h"
#include "../playGame/playGame.h"


void loadGame(int numFile) {
    system("cls");
	
	Round round;
	char extension[] = ".dat";
	char strNumFile[2];
	FILE *file;
	char path[] = "C:\\battleShip\\savedGames\\match";
	numberToString(numFile, strNumFile);
	strcat(path, strNumFile);
	strcat(path, extension);

	file = fopen(path, "rb");
	if (file == NULL) {
		printf("Errore nel salvataggio!\n ");
	} else {
		fread(&round, sizeof(Round), 1, file);
	}
	
	fclose(file);
	
	if ((getAvailableShips(getActivePlayer(round)) > 0) && (getAvailableShips(getPassivePlayer(round)) > 0)) {
		playGame(round,numFile);
	} else {
		printf("LA PARTITA E' GIA' TERMINATA.\n");
		printf("Premi INVIO per tornare al menu principale...");
		getchar();
		fflush(stdin);
	}
	
	return;
}
