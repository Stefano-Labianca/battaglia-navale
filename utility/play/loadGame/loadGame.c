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
	char extention[] = ".dat";
	char strNumFile[2];
	FILE *file;
	char path[] = "C:\\battleShip\\savedGames\\match";
	numberToString(numFile, strNumFile);
	strcat(path, strNumFile);
	strcat(path, extention);
	file = fopen(path, "r");
	if (file == NULL) {
		printf("Errore nel salvataggio!\n ");
	} else {
		fread(&round, sizeof(Round), 1, file);
	}
	fclose(file);
	playGame(round,numFile);
	return;
}
