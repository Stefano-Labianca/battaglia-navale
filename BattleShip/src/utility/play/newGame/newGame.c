#include <stdlib.h>
#include <stdio.h>

#include "./newGame.h"

/**
 * Funzione newGame
 * DESCRIZIONE: la funzione permette ai giocatori di inizializzare la partita, posizionando le navi sui rispettivi campi di battaglia
 * 
 * INPUT
 * numFile - Numero file di salvataggio - Intero - numFile >= FIRST_SLOT AND numFile <= LAST_SLOT
 * 
 * OUTPUT
 * file - file di salvataggio della partita - File binario - /
 *
 * LAVORO
 * round - Round della partita - Round - /
 * whoPlay - Indica il player che attacca - Intero - 1 = Attacca il player 1; 2 = Attacca il player 2
 * turn - Indica il turno della partita - Intero - turn > 0
 * Pause - Indica lo stato di pausa - Intero - 1 = Uscire dalla partita; 0 = Continuare a giocare
 * id - Indica l'id del giocatore - Intero - 1 = id player 1; 2 = id player 2
 * player1 - Primo player - Player - /
 * player2 - Secondo player - Player - /
 * Map - Mappa di gioco - Array bidimensionale di caratteri - Dimensione 16x16;
 * Caratteri consentiti:
 * Da 'a' a 'o' per le navi
 * '~' per il mare
 * 'x' nave colpita
 * '*' nave affondata
 *
 */
void newGame(int numFile)
{
    Round round;
    int whoPlay;
    int turn;
    int id;
    Player player1;
    Player player2;
    char map[TABLE_MAX][TABLE_MAX];
    int pause;

    turn = 1;
    whoPlay = 1;
    pause = 0;

    round = setGameRound(round, turn);
    round = setWhoPlay(round, whoPlay);
    round = setPause(round, pause);

    printf("PIAZZA LE NAVI IL GIOCATORE 1\n");
    id = 1;
    player1 = createPlayer(player1, id);
    player1 = buildPlayerNavy(player1);

    printf("\nPLAYGROUND FINALE\n");
    getPlayground(player1, map);
    showMap(map);

    printf("\nOra tocca al tuo avversario piazzare le navi!\n");
    system("pause"); // Funzione clickToContinue
    system("cls"); // Funzione cleanScreen

    printf("PIAZZA LE NAVI IL GIOCATORE 2\n");
    id = 2;
    player2 = createPlayer(player2, id);
    player2 = buildPlayerNavy(player2);

    printf("\nPLAYGROUND FINALE\n");
    getPlayground(player2, map);
    showMap(map);

    printf("\nLa partita sta per cominciare!\n");
    system("pause"); // Funzione clickToContinue
    system("cls"); // Funzione cleanScreen

    round = setActivePlayer(round, player1);
    round = setPassivePlayer(round, player2);

    playGame(round,numFile);
    return;
}


/**
 * Funzione loadVerticalAxis
 * DESCRIZIONE: Carica una nave in verticale all'interno del playground del giocatore.
 *
 * INPUT
 * player - Giocatore a cui inserire una nave - Player - \
 * startColumn - Colonna di partenza della nave - intero - startColumn >= TABLE_MIN AND startColumn <= TABLE_MAX
 * startRow - Riga di partenza della nave - intero - startRow >= TABLE_MIN AND startRow <= TABLE_MAX
 * label - Etichetta della nave - carattere - label >= 'a' AND label <= 'o'
 * shipSize - Dimensioni della nave - intero - shipSize >= MIN_SHIP_SIZE AND shipSize <= MAX_SHIP_SIZE
 * 
 * OUTPUT
 * player - Giocatore aggiornato con all'interno del suo playground una nave - Player - \
 * 
 * LAVORO
 * i - Contatore utilizzato per inserire correttamente la nave nel suo range di coordinate - intero - i > 0
 * playground - Campo da gioco del giocatore player - Array di caratteri a due dimensioni - Dimensione 16x16
 * Caratteri consentiti:
 * da 'a' o 'o' per le navi
 * '~' per il mare
 * 'x' per nave colpita
 * '*' per nave affondata
 */
Player loadVerticalAxis(Player player, int startColumn, int startRow, char label, int shipSize)
{
	int i;
	char playground[TABLE_MAX][TABLE_MAX];

	i = 0;
	getPlayground(player, playground);

	startColumn--; // Dato che iteriamo partendo da 0, e' necessario diminuire di 1 la colonna di partenza
	startRow--; // Dato che iteriamo partendo da 0, e' necessario diminuire di 1 la riga di partenza

	while (i < shipSize)
	{
		playground[startRow][startColumn] = label;
		startRow++;
		i++;
	}

	player = setPlayground(player, playground);

	return player;
}

/**
 * Funzione loadHorizontalAxis
 * DESCRIZIONE: Carica una nave in orizzontale all'interno del playground del giocatore.
 *
 * INPUT
 * player - Giocatore a cui inserire una nave - Player - \
 * startColumn - Colonna di partenza della nave - intero - startColumn >= TABLE_MIN AND startColumn <= TABLE_MAX
 * startRow	- Riga di partenza della nave - intero - startRow >= TABLE_MIN AND startRow <= TABLE_MAX
 * label - Etichetta della nave - carattere - label >= 'a' AND label <= 'o'
 * shipSize	- Dimensioni della nave - intero - shipSize >= MIN_SHIP_SIZE AND shipSize <= MAX_SHIP_SIZE
 * 
 * OUTPUT
 * player - Giocatore aggiornato con all'intero del suo playground una nave	- Player - \
 * 
 * LAVORO
 * i - Contatore utilizzato per inserire correttamente la nave nel suo range di coordinate - intero - i > 0
 * playground - Campo da gioco del giocatore player	- Array di caratteri a due dimensioni - Dimensione 16x16;
 * Caratteri consentiti:
 * da 'a' a 'o' per le navi
 * '~' per il mare
 * 'x' per nave colpita
 * '*' per nave affondata
 */
Player loadHorizontalAxis(Player player, int startColumn, int startRow, char label, int shipSize)
{
	int i;
	char playground[TABLE_MAX][TABLE_MAX];

	i = 0;
	getPlayground(player, playground);

	startColumn--; // Dato che iteriamo partendo da 0, e' necessario diminuire di 1 la colonna di partenza
	startRow--; // Dato che iteriamo partendo da 0, e' necessario diminuire di 1 la riga di partenza

	while (i < shipSize)
	{
		playground[startRow][startColumn] = label;
		startColumn++;
		i++;
	}

	player = setPlayground(player, playground);

	return player;
}


/**
 * Funzione buildPlayerNavy
 * DESCRIZIONE: Permette al giocatore di crearsi la sua flotta di navi, da inserire nel playground di gioco. Alla fine
 * dell'inserimento delle navi nella mappa di gioco, verra'� restituito il dato strutturato Player modificato.
 *
 * INPUT
 * player - player a cui far inserire le navi nel suo playGround - Player - /
 * MAX_SHIP_AMOUNT - Numero massimo di navi in un playground - Numero intero - 15
 * MAX_SHIP_SIZE - Dimensione massima di una nave - Numero intero - 5
 * 
 * OUTPUT
 * player - player con le navi inserite nel suo playGround - Player - /
 * 
 * LAVORO
 * i - Contatore del numero di navi da creare mancanti - intero - i > 0
 * j - Contatore del numero di navi da creare di dimensione - intero - sizeModifier	- j > 0
 * ship - Nave del giocatore - ship - /
 * shipDirection - Direzione della nave - carattere - V = Verticale; O = Orizzontale
 * label - Etichetta della nave - carattere - label >= 'a' AND label <= 'o'
 * integerColumn - Colonna di partenza di una nave - numero intero - integerColumn >= TABLE_MIN AND integerColumn <= TABLE_MAX
 * integerRow - Riga di partenza di una nave - numero intero - integerRow >= TABLE_MIN AND integerRow <= TABLE_MAX
 * sizeModifier - Dimensioni della nave da inserire - numero intero - sizeModifier >= 1 AND sizeModifer <=  MAX_SHIP_SIZE
 * amountModifier -	Quantita'� di navi da inserire per una specifica dimensione - numero intero - amountModifer >= 1 AND amountModifier <= MAX_SHIP_AMOUNT 
 * Index - Posizione che indica quale nave leggere - Numero intero - index > 1 AND index < MAX_SHIP_AMOUNT
 * playground - Campo da gioco del giocatore player - Array di caratteri a due dimensioni - Dimensione 16x16; 
 * Caratteri consentiti:
 * da 'a' a 'o' per le navi
 * '~' per il mare
 * 'x' per nave colpita
 * '#' per nave affondata
 */
Player buildPlayerNavy(Player player)
{
	Ship ship;
	char playground[TABLE_MAX][TABLE_MAX];
	char shipDirection;
	char label;
	int integerColumn;
	int integerRow;
	int sizeModifier;
	int amountModifier;
	int index;
	int i;
	int j;

	/**
	 * In pratica cosa faccio:
	 * 		sizeModifier: number = MAX_SHIP_SIZE -> Rappresenta le dimensioni della nave da inserire (MAX_SHIP_AMOUNT = 5);
	 * 		amountModifier: number = 1 -> Rappresenta la quantita'�di navi da inserire, per una specifica dimensione;
	 *
	 * Immaginiamo di avere due array di numeri, entrambi di lunghezza pari a 5:
	 * 		sizeCollection: number[] = [5, 4, 3, 2, 1];
	 * 		amountCollection: number[] = [1, 2, 3, 4, 5];
	 *
	 * sizeCollection contiene le possibili dimensioni di una nave, mentre amountCollection quante navi per ogni dimensione.
	 * Utilizzando l'indice dei due array, possiamo creare un'associazione del tipo size-amount.
	 * Per esempio: se index = 0, allora posso creare 1 nave di dimensioni pari a 5.
	 *
	 * Il principio e' simile all'uso delle due variabili sizeModifier e amountModifier, solamente che non abbiamo indici di alcun tipo
	 * ma andiamo ad aumentare gradualmente la quantita' di navi da inserire e, nel mentre, diminuiamo il modificatore delle dimensioni.
	 */

	sizeModifier = MAX_SHIP_SIZE;
	amountModifier = 1;
	index = 0;
	i = 0;
	j = 0;

	while (i < MAX_SHIP_AMOUNT)
	{
		j = 0;

		while (j < amountModifier)
		{
			getPlayground(player, playground);
			ship = createShip(sizeModifier, index, playground);
			player = setShip(player, (index + 1), ship); // Aggiungo 1 perche' index parte da 0
			shipDirection = getDirection(ship);
			label = getLabel(ship);
			integerColumn = pullColumn(ship);
			integerRow = pullRow(ship);

			if (shipDirection == 'V')
			{
				player = loadVerticalAxis(player, integerColumn, integerRow, label, sizeModifier);
			}

			else if (shipDirection == 'O')
			{
				player = loadHorizontalAxis(player, integerColumn, integerRow, label, sizeModifier);
			}

			j++;
			i++;
			index++;
		}

		amountModifier++;
		sizeModifier--;
	}

	return player;
}
