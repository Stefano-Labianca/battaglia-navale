#include <stdlib.h>
#include <stdio.h>

#include "./newGame.h"


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

    printf("CREAZIONE DI PLAYER1\n");
    id = 1;
    player1 = createPlayer(player1, id);
    player1 = buildPlayerNavy(player1);

    printf("\nSTAMPA DEL PLAYGROUND\n");
    getPlayground(player1, map);
    showMap(map);


    printf("CREAZIONE DI PLAYER2\n");
    id = 2;
    player2 = createPlayer(player2, id);
    player2 = buildPlayerNavy(player2);

    printf("\nSTAMPA PLAYGROUND\n");
    getPlayground(player2, map);
    showMap(map);


    round = setActivePlayer(round, player1);
    round = setPassivePlayer(round, player2);

    playGame(round,numFile);
    return;
}



/**
 * @brief Carica una nave in verticale all'interno del playground del giocatore.
 *
 * @param player Giocatore a cui inserire una nave.
 * @param startColumn Colonna di partenza della nave.
 * @param startRow Riga di partenza usata della nave.
 * @param label Etichetta della nave.
 * @param shipSize Dimensioni della nave.
 * @return Giocatore aggiornato con all'interno del suo playground una nave.
 */
Player loadVerticalAxis(Player player, int startColumn, int startRow, char label, int shipSize)
{
	int i;
	char playground[TABLE_MAX][TABLE_MAX];

	i = 0;
	getPlayground(player, playground);

	startColumn--;
	startRow--;

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
 * @brief Carica una nave in orizzontale all'interno del playground del giocatore.
 *
 * @param player Giocatore a cui inserire una nave.
 * @param startColumn Colonna di partenza della nave.
 * @param startRow Riga di partenza usata della nave.
 * @param label Etichetta della nave.
 * @param shipSize Dimensioni della nave.
 * @return Giocatore aggiornato con all'interno del suo playground una nave.
 */
Player loadHorizontalAxis(Player player, int startColumn, int startRow, char label, int shipSize)
{
	int i;
	char playground[TABLE_MAX][TABLE_MAX];

	i = 0;
	getPlayground(player, playground);

	startColumn--;
	startRow--;

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
 * @brief Permette al giocatore di crearsi la sua flotta di navi, da inserire nel playground di gioco. Alla fine
 * dell'inserimento delle navi nella mappa di gioco, verrà restituito il dato strutturato Player modificato.
 *
 * @param player Player a cui far inserire le navi nella sua mappa di gioco.
 * @return Player con le navi inserite nella mappa di gioco.
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
	 * 		amountModifier: number = 1 -> Rappresenta la quantità di navi da inserire, per una specifica dimensione;
	 *
	 * Immagina di avere due array di numeri, entrambi di lunghezza pari a 5:
	 * 		sizeCollection: number[] = [5, 4, 3, 2, 1];
	 * 		amountCollection: number[] = [1, 2, 3, 4, 5];
	 *
	 * sizeCollection, contiene le possibili dimensioni di una nave, mentre amountCollection le possibili dimensioni della nave.
	 * Attraverso l'uso dell'indice dei due array, possiamo creare un'associazione del tipo size-amount.
	 * Per esempio: se index = 0, allora posso creare 1 nave di dimensioni pari a 5.
	 *
	 * Il principio è simile all'uso delle due variabili sizeModifier e amountModifier, solamente che non abbiamo indici di alcun tipo
	 * ma andiamo ad aumentare gradualmente la quantità di navi da inserire e, nel mentre, diminuiamo il modificatore delle dimensioni.
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

			player = setShip(player, (index + 1), ship);

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
