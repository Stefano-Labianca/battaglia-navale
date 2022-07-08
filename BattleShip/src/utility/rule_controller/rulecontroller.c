#include "./rulecontroller.h"

#include <stdio.h>
#include <stdlib.h>


/**
 * Funzione showRules
 * DESCRIZIONE: Mostra le regole di gioco
 * 
 * INPUT
 * rulesFile - File contenente le regole di gioco - File di testo - /
 * c - Carattere letto da tastiera - Carattere - /
 * RULES_PATH - Percorso del file delle regole - Stringa - /
 * 
 * OUTPUT - /
 * 
 * LAVORO
 * buffer - Stringa contenente una riga del file rulesFile - Stringa - /
 */
void showRules()
{   
	system("cls"); // Funzione cleanScreen
    FILE* rulesFile;

    char buffer[BUFFER_SIZE];

    rulesFile = fopen(RULES_PATH, "r");

    // se rulesFile non e' stato aperto correttamente
    if (rulesFile == NULL) {
        printf("Errore nell'apertura delle regole!\n");
    } else {
        printf("\n  --- REGOLE DI GIOCO ---\n\n");

        while (fgets(buffer, BUFFER_SIZE, rulesFile) != NULL)
        {
            printf("  %s", buffer);
        }

        printf("\n  -----------------------\n\n");
    }
    fclose(rulesFile);

    system("pause"); // Funzione clickToContinue
    fflush(stdin);
    return;
}
