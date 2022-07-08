#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./loadGame.h"
#include "../../converter/converter.h"
#include "../../../struct/round/Round.h"
#include "../playGame/playGame.h"

/**
 * Funzione loadGame
 * DESCRIZIONE: Carica la partita dallo slot selezionato dall'utente
 *
 * INPUT
 * numFile - Scelta dell'utente per il file - Intero - Compreso tra FIRST_SLOT e LAST_SLOT
 * file	- File contenente la partita da caricare - File binario - /
 *
 * OUTPUT
 * file - file di salvataggio della partita - File binario - /
 *
 */
void loadGame(int numFile) {
    system("cls"); // Funzione cleanScreen
	
	Round round;
	char extension[] = ".dat";
	char strNumFile[2];
	FILE *file;
	char path[] = "C:\\battleShip\\savedGames\\match";

	numberToString(numFile, strNumFile);
	strcat(path, strNumFile); // Funzione concatString
	strcat(path, extension); // Funzione concatString

	file = fopen(path, "rb");

	// se file non e' aperto correttamente
	if (file == NULL) {
		printf("Errore nel salvataggio o salvataggio inesistente!\n");
		system("pause"); // Funzione clickToContinue
	} else {
		fread(&round, sizeof(Round), 1, file);

		if ((getAvailableShips(getActivePlayer(round)) > 0) && (getAvailableShips(getPassivePlayer(round)) > 0)) {
			playGame(round, numFile);
		} else {
			printf("La partita e' gia' terminata.\n");
			system("pause"); // Funzione clickToContinue
			fflush(stdin);
		}
	}
	
	fclose(file);
	
	return;
}
