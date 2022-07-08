/**
 * Nome del progetto: Battleship Enhanced Edition
 * 
 * Gruppo 12
 * 
 * Autori: Curri Mattia, Festa Donato, Fontana Emanuele, Labianca Stefano Antonio
 * 
 * NOTE:
 * - le iterazioni in generale partono da 0
 * - il carattere di fine stringa '\0' e' l'equivalente di ENDSTRING dello pseudocodice
 *  
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./utility/play/newGame/newGame.h"
#include "./utility/play/loadGame/loadGame.h"
#include "utility/play/saveGame/savegame.h"
#include "utility/rule_controller/rulecontroller.h"

// Da non modificare perche' viene generata da sistema
#define LIST_SAVE_PATH "C:\\battleShip\\savedGames\\Elenco.txt" // LIST_SAVE_PATH - percorso del file dell'elenco dei salvataggi esistenti - Stringa

void showLogo();
void mainLoop();
void showMenu();
char userChoice();
int fileChoice();

int isCommandConfirmed(int numFile);

/**
 * Funzione main
 * DESCRIZIONE: Funzione main del programma
 * INPUT
 * match1 - Primo file di salvataggio - file binario - /
 * match2 - Secondo file di salvataggio - file binario - /
 * match3 - Terzo file di salvataggio - file binario - /
 * match4 - Quarto file di salvataggio - file binario - /
 * match5 - Quinto file di salvataggio - file binario - /
 * match6 - Sesto file di salvataggio - file binario - /
 * match7 - Settimo file di salvataggio - file binario - /
 * listSaveFile - Lista dei salvataggi esistenti - file di testo - /
 * rules - File delle regole - file di testo - /
 *
 * OUTPUT
 * match - File di salvataggio della partita - file binario - /
 */
int main()
{
    system("title BattleShip Enhanced Edition"); // Funzione setTitle
    
    mainLoop();

    system("pause"); // Funzione clickToContinue
    return 0;
}

/**
 * Funzione showLogo
 * DESCRIZIONE: Mostra a schermo il logo
 *
 * INPUT - /
 * OUTPUT - /
 * LAVORO - /
 */
void showLogo()
{
    // INIZIO LOGO
	printf("                                  _/|                           \n");
	printf("                                 _|:|                           \n");
	printf("                               _|:::|                           \n");
	printf("                         _ /|  |::::|                           \n");
	printf("                         |::|  |::::|                           \n");
	printf("                         |::|  |:::::)__                        \n");
	printf("                       /:|:::: |::::::::|                       \n");
	printf("                      :::|::::_|::::::::|                       \n");
	printf("                ____(:::::::::::::::::::|___ _______         __ \n");
	printf("               (::::::::::::::::::::::::|:::|::::::|  ______|::)\n");
	printf("     ___________\\:::::::::::::::::::::::::::|:::|___|:::::::::|\n");
	printf("     \\::::::::::::::::::::::::::::::::::::::::::::::::::::::::|\n");
	printf("      |:::::::::::::::::::::::::::::::::::::::::::::::::::::::| \n");
    printf("     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("  ____        _   _              _ _         _   _                  _      \n");
	printf(" | __ )  __ _| |_| |_ __ _  __ _| (_) __ _  | \\ | | __ ___   ____ _| | ___ \n");
	printf(" |  _ \\ / _` | __| __/ _` |/ _` | | |/ _` | |  \\| |/ _` \\ \\ / / _` | |/ _ \\ \n");
	printf(" | |_) | (_| | |_| || (_| | (_| | | | (_| | | |\\  | (_| |\\ V / (_| | |  __/\n");
	printf(" |____/ \\__,_|\\__|\\__\\__,_|\\__, |_|_|\\__,_| |_| \\_|\\__,_| \\_/ \\__,_|_|\\___|\n");
	printf("                           |___/                                           \n");
	// FINE LOGO
    return;
}


/**
 * Funzione mainLoop
 * DESCRIZIONE: Rappresenta il menu' principale a cui l'utente puo' accedere
 * non appena avvia il programma. Da qui puo' scegliere se giocare una
 * nuova partita, oppure se vuole continuare una partita salvata in
 * precedenza, visualizzare le regole di gioco oppure uscire dal
 * programma.
 *
 * INPUT
 * choice - Indica la scelta dell'utente - Carattere - Compreso tra '1' e '4'
 * numFile - Indica il numero di file (slot di salvataggio)	- Intero - Compreso tra FIRST_SLOT e LAST_SLOT
 *
 * OUTPUT - /
 *
 * LAVORO
 * end - Indica la fine del programma - Numero intero - 1 = Programma terminato; 0 = Programma in esecuzione
 *
 */
void mainLoop()
{
    int end;
    char choice;
	choice = ' ';
    int numFile;

    /**
     * Il sistema andra' a creare nel percorso indicato la cartella in cui verranno inseriti i salvataggi
     * Se la cartella gia' esiste il sistema ritornera' un avviso per indicare che la cartella gia' esiste
     */
    system("mkdir C:\\battleShip\\savedGames"); // Funzione setSaveDirectory
    system("cls"); // Funzione cleanScreen

    end = 0;
    while (end == 0)
    {
    	showLogo();
        showMenu();
        choice = userChoice();

        if (choice == '1')
        {
           	do {
           		numFile = fileChoice();
           		if (numFile != 0) {
           			if (isCommandConfirmed(numFile) == 1) {
           				system("cls"); // Funzione cleanScreen
           				newGame(numFile);
           				numFile = 0;
           			}
           		}
           	} while(numFile != 0);
        }

        else if (choice == '2')
        {
            numFile = fileChoice();
            if (numFile != 0) {
            	loadGame(numFile);
            }
        }

        else if (choice == '3')
        {
            showRules();
        }

        else if (choice == '4')
        {
            end = 1;
        } else {
            printf("  Comando non valido\n\n");
        }
        system("cls"); // Funzione cleanScreen
    }
    return;
}

/**
 * Funzione showMenu
 * DESCRIZIONE: Mostra a video il menu' di gioco
 *
 * INPUT - /
 * OUTPUT - /
 * LAVORO - /
 */
void showMenu()
{
    // INIZIO MENU
    printf("\n  --- MENU' PRINCIPALE ---\n");
    printf("  1. Nuova partita\n");
    printf("  2. Carica partita\n");
    printf("  3. Visualizza regole\n\n");
    printf("  4. Esci dal gioco\n");
    printf("  -------------------------\n\n");
    // FINE MENU
    return;
}

/**
 * Funzione userChoice
 * DESCRIZIONE: Fornisce la possibilita' all'utente di scegliere cosa fare
 * all'interno del menu' di gioco, restituendo un carattere, che
 * rappresenta la sua scelta.
 *
 * INPUT
 * Input - Scelta dell'utente per la mossa successiva - Carattere - Compreso tra '1' e '4'
 *
 * OUTPUT
 * Input - Scelta dell'utente per la mossa successiva - Carattere - Compreso tra '1' e '4'
 *
 * LAVORO - /
 */
char userChoice()
{
    char input;
    input = ' ';

    do
    {
        printf("  Inserisci una scelta valida tra le opzioni disponibili: ");
        scanf("%c", &input);
        fflush(stdin);
        if (input < '1' || input > '4') {
        	printf("\n  Errore: inserire una scelta valida\n\n");
        }
    } while (input < '1' || input > '4');

    return input;
}

/**
 * Funzione fileChoice
 * DESCRIZIONE: Fornisce la possibilita' di scegliere il numero di salvataggio da caricare all'utente
 *
 * INPUT
 * numFile - Scelta dell'utente per il file da caricare/scrivere - Intero - Compreso tra FIRST_SLOT e LAST_SLOT
 * FIRST_SLOT - Primo slot di salvataggio - Numero intero - 1
 * LAST_SLOT - Ultimo slot di salvataggio - Numero intero - 7
 *
 * OUTPUT
 * numFile - Scelta dell'utente per il file da caricare/scrivere - Intero - Compreso tra FIRST_SLOT e LAST_SLOT
 *
 * LAVORO - /
 *
 */
int fileChoice()
{
    int numFile;

    do
    {
        printf("\n  Inserisci il numero di salvataggio (da %d a %d) oppure 0 per tornare al menu': ", FIRST_SLOT, LAST_SLOT);
        scanf("%d", &numFile);
        fflush(stdin);
        if (numFile < FIRST_SLOT - 1|| numFile > LAST_SLOT) {
        	printf("\n  Errore: inserire un numero tra %d e %d\n", FIRST_SLOT - 1, LAST_SLOT);
        }
    } while (numFile < FIRST_SLOT - 1 || numFile > LAST_SLOT);
    return numFile;
}

/**
 * Funzione isCommandConfirmed
 * DESCRIZIONE: la funzione chiede all'utente se vuole sovrascrivere un salvataggio nel caso in cui questo esista
 *
 * INPUT
 * numFile - Scelta dell’utente per il file da caricare/scrivere - Intero - Compreso tra FIRST_SLOT e LAST_SLOT
 * listSaveFile - Lista dei salvataggi esistenti - File di testo - /
 * LIST_SAVE_PATH - Percorso del file dell'elenco dei salvataggi esistenti - Stringa - "C:\\battleShip\\savedGames\\Elenco.txt"
 * MIN_DIGIT - 0 in codice ASCII - Numero intero - 48
 * NUM_SAVE - Posizione contenente il numero del salvataggio - Numero intero - 6
 * overwriting - Indica se l’utente vuole sovrascrivere o meno il file di salvataggio scelto - Carattere - S = il file viene sovrascritto; N = torna alla scelta del salvataggio
 * BUFFER_SIZE - Numero massimo di caratteri presenti in una riga - Numero intero - 256
 *
 * OUTPUT
 * wantToContinue - Indica se verrà iniziata una nuova partita - Numero intero - 0 = la partita non verrà iniziata; 1 = la partita verrà iniziata
 *
 * LAVORO
 * buffer - Stringa contenente il nome di un salvataggio - Stringa - /
 */
int isCommandConfirmed(int numFile) {
	int wantToContinue;
	FILE* listSaveFile;
	char overwriting;
	char buffer[BUFFER_SIZE];

	wantToContinue = 1;

	/**
	 * dir e' un comando utilizzato per visualizzare l'elenco di file in 'C:/battleShip/savedGames/' (equivalente all'input savePath),
	 * piu' nello specifico solo i file che hanno nel nome 'match' seguito da un altro carattere, di estensione .dat,
	 * ignorando i file di sistema, i file nascosti, le directory e i file di sola lettura.
	 * Le informazioni, raccolte in modo sintetico (nome.estensione), vengono scritte in un file di testo salvato in
	 * 'C:/battleShip/savedGames/' e chiamato 'Elenco.txt' (equivalente all'input nameFile)
	*/
	system("dir C:\\battleShip\\savedGames\\match?.dat /a:-d-r-s-h /b > C:\\battleShip\\savedGames\\Elenco.txt"); // Funzione createListSaveFile

	listSaveFile = fopen(LIST_SAVE_PATH, "r");

	// se listSaveFile non e' aperto correttamente
	if (listSaveFile == NULL) {
		printf("  Non e' stato possibile recuperare l'elenco dei salvataggi presenti.\n");
		system("pause"); // Funzione clickToContinue
	} else {
		while (fgets(buffer, BUFFER_SIZE, listSaveFile) != NULL) {
			if (buffer[NUM_SAVE] == (numFile + MIN_DIGIT)) {
				printf("\n  Salvataggio gia' esistente.\n");
				do {
					printf("  Vuoi sovrascrivere il salvataggio? (il file verra' sovrascritto dopo aver giocato il primo turno)\n");
					printf("  S: Si; N: No: ");
					overwriting = getchar();
					overwriting = toUpperCase(overwriting);
					if (overwriting != 'S' && overwriting != 'N') {
						printf("  Errore: inserire una scelta valida\n");
					}
					fflush(stdin);
				} while(overwriting != 'S' && overwriting != 'N');
				if (overwriting == 'N') {
					wantToContinue = 0;
				}
			}
		}
	}

	fclose(listSaveFile);

	return wantToContinue;
}


