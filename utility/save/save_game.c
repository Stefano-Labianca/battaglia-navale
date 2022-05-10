#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./save_game.h"
#include "../../global/GlobalConstants.h"
#include "../converter/converter.h"

/**
 * @brief Mostra gli slot di salvataggio del gioco
 */

void saveGame(Round round, int numFile) {

	char extention[] = ".dat";
	char strNumFile[2];
	char nameFile[]="\\match";
	FILE *file;
	char path[] = "C:\\battleShip\\savedGames";
	numberToString(numFile, strNumFile);
	strcat(nameFile, strNumFile);
	strcat(nameFile, extention);
	strcat(path,nameFile);
	file = fopen(path, "w");
	if (file == NULL) {
		printf("Errore nel salvataggio!\n ");
	} else {
		fwrite(&round, sizeof(Round), 1, file);
	}
	fclose(file);
	return;
}