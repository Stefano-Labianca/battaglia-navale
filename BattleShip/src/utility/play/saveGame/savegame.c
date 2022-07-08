#include "./savegame.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Funzione saveGame
 * DESCRIZIONE: Mostra gli slot di salvataggio del gioco
 * 
 * INPUT
 * round - Round della partita da salvare - Round - /
 * numFile - Scelta dell'utente per il file - Intero - Compreso tra FIRST_SLOT e LAST_SLOT
 * file - File su cui scrivere la partita - File binario - /
 * 
 * OUTPUT
 * file - File con partita salvata - File binario - /
 * 
 * LAVORO
 * round - Round della partita da caricare - Round - /
 * extension - Indica l'estensione del file da aprire - Stringa - /
 * strNumFile - Contiene il valore di numFile - Stringa - /
 * path - Percorso del file da aprire - Stringa - /
 */
void saveGame(Round round, int numFile) {
	char extension[] = ".dat";
	char strNumFile[2];
	char nameFile[] = "\\match";
	FILE *file;
	char path[] = "C:\\battleShip\\savedGames";
	numberToString(numFile, strNumFile);
	strcat(nameFile, strNumFile); // Funzione concatString
	strcat(nameFile, extension); // Funzione concatString
	strcat(path, nameFile); // Funzione concatString
	file = fopen(path, "wb");

	// se file non e' aperto correttamente
	if (file == NULL) {
		printf("Errore nel salvataggio!\n");
		system("pause"); // Funzione clickToContinue
	} else {
		fwrite(&round, sizeof(Round), 1, file);
	}

	fclose(file);
	return;
}
