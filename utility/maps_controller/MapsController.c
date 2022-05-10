#include <stdlib.h>
#include <stdio.h>

#include "./MapsController.h"




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
 * @brief Permette al giocatore attivo di colpire una cella
 * della mappa dell'avversario, restituendo il match di gioco
 * modificato.
 *
 * @param row Riga del colpo.
 * @param column Colonna del colpo.
 * @param match Match di gioco da modificare.
 * @return Match di gioco modificato.
 */
Round hit(int row, int column, Round match)
{
	char passivePlayground[TABLE_MAX][TABLE_MAX];
	char activeHeatMap[TABLE_MAX][TABLE_MAX];
	char cell;

	Player passivePlayer;
	Player activePlayer;

	Ship ship;
	int lifePoints;
	int passivePlayerShips;
	char passivePlayerCoords[MAX_COORDS_RANGE];
	char direction;

	passivePlayer = getPassivePlayer(match);
	activePlayer = getActivePlayer(match);
	getPlayground(passivePlayer, passivePlayground);
	getHeatMap(activePlayer, activeHeatMap);
	cell = passivePlayground[row][column];

	if (passivePlayground[row][column] == WATER || passivePlayground[row][column] == PLAYGROUND_HIT)
	{
		activeHeatMap[row][column] = WATER;
		printf("\n%c-%d: ACQUA!\n", (column + START_UPPERCASE_ASCII), (row + 1));
	}

	else
	{
		ship = getShip(passivePlayer, (cell - START_LOWERCASE_ASCII + 1));
		lifePoints = getLifePoints(ship);


		if (lifePoints == 1)
		{
			printf("\n%c-%d: COLPITO E AFFONDATO!\n", (column + START_UPPERCASE_ASCII), (row + 1));
			passivePlayerShips = getAvailableShips(passivePlayer);
			passivePlayerShips--;
			passivePlayer = setAvailableShips(passivePlayer, passivePlayerShips);
			getCoords(ship, passivePlayerCoords);
			direction = getDirection(ship);

			row = pullRow(ship) - 1;	   
			column = pullColumn(ship) - 1; 

			if (direction == 'V')
			{
				while (passivePlayground[row][column] != WATER)
				{
					passivePlayground[row][column] = SUNK;
					activeHeatMap[row][column] = SUNK;
					row++;
				}
			}

			else
			{
				while (passivePlayground[row][column] != WATER)
				{
					passivePlayground[row][column] = SUNK;
					activeHeatMap[row][column] = SUNK;
					column++;
				}
			}
		}
		
		else
		{
			passivePlayground[row][column] = PLAYGROUND_HIT;
			activeHeatMap[row][column] = HEAT_MAP_HIT;
			printf("\n%c-%d: COLPITO!\n", (column + START_UPPERCASE_ASCII), (row + 1));
		}
		ship = setLifePoints(ship, (lifePoints - 1));
		passivePlayer = setShip(passivePlayer, (cell - START_LOWERCASE_ASCII + 1), ship);
	}

	passivePlayer = setPlayground(passivePlayer, passivePlayground);
	activePlayer = setHeatMap(activePlayer, activeHeatMap);

	match = setActivePlayer(match, activePlayer);
	match = setPassivePlayer(match, passivePlayer);

	return match;
}

Round longShot(int row, int column, Round match)
{
	char passivePlayground[TABLE_MAX][TABLE_MAX];
	char activeHeatMap[TABLE_MAX][TABLE_MAX];

	Player passivePlayer;
	Player activePlayer;

	int i;
	int pivotRow;
	int pivotColumn;
	int endColumn;
	int endRow;

	passivePlayer = getPassivePlayer(match);
	activePlayer = getActivePlayer(match);

	getPlayground(passivePlayer, passivePlayground);
	getHeatMap(activePlayer, activeHeatMap);

	row--;
	column--;
	pivotColumn = column - 1;
	pivotRow = row - 1;

	if (pivotColumn < TABLE_MIN - 1)
	{
		pivotColumn = TABLE_MIN - 1;
	}
	
	if (pivotRow < TABLE_MIN - 1)
	{
		pivotRow = TABLE_MIN - 1;
	}
	
	endRow = row + 1;
	endColumn = column + 1;
	
	if (endRow > TABLE_MAX - 1)
	{
		endRow = TABLE_MAX - 1;
	}
	if (endColumn > TABLE_MAX - 1)
	{
		endColumn = TABLE_MAX - 1;
	}

	printf("Row=%d\tColumn=%d\nPivotRow=%d\tPivotColumn=%d\tEndRow=%d\tEndColumn=%d\n", row, column, pivotRow, pivotColumn, endRow, endColumn);
	while (pivotRow <= endRow)
	{
		i = pivotColumn;
		while (i <= endColumn)
		{
			match = hit(pivotRow, i, match);
			i++;
		}
		pivotRow++;
	}

	return match;
}

char axisChoice()
{
	char axis;
	int error;

	axis = ' ';
	error = 0;

	do
	{
		error = 0;
		printf("Inserire R se si vuole colpire la riga, oppure C se si vuole colpire la colonna: ");

		axis = getchar();

		if (axis != 'C' && axis != 'R')
		{
			error = 1;
			printf("\n\nErrore\n\n"); // TODO: Da gestire meglio la stampa dell'errore
		}

		fflush(stdin);
	} while (error == 1);

	return axis;
}

Round airStrikeRow(Round match, int row)
{
	char passivePlayground[TABLE_MAX][TABLE_MAX];
	char activeHeatMap[TABLE_MAX][TABLE_MAX];

	Player passivePlayer;
	Player activePlayer;

	int i;

	passivePlayer = getPassivePlayer(match);
	activePlayer = getActivePlayer(match);

	getPlayground(passivePlayer, passivePlayground);
	getHeatMap(activePlayer, activeHeatMap);

	row--;
	i = 0;

	while (i < TABLE_MAX)
	{
		match = hit(row, i, match);
		i++;
	}

	return match;
}

Round airStrikeColumn(Round match, int column)
{
	char passivePlayground[TABLE_MAX][TABLE_MAX];
	char activeHeatMap[TABLE_MAX][TABLE_MAX];

	Player passivePlayer;
	Player activePlayer;

	int i;

	passivePlayer = getPassivePlayer(match);
	activePlayer = getActivePlayer(match);

	getPlayground(passivePlayer, passivePlayground);
	getHeatMap(activePlayer, activeHeatMap);

	column--;
	i = 0;

	while (i < TABLE_MAX)
	{
		match = hit(i, column, match);
		i++;
	}

	return match;
}

Round scan(int row, int column, Round match)
{
	char passivePlayground[TABLE_MAX][TABLE_MAX];
	char activeHeatMap[TABLE_MAX][TABLE_MAX];

	Player passivePlayer;
	Player activePlayer;

	passivePlayer = getPassivePlayer(match);
	activePlayer = getActivePlayer(match);

	getPlayground(passivePlayer, passivePlayground);
	getHeatMap(activePlayer, activeHeatMap);

	if (passivePlayground[row][column] == WATER || passivePlayground[row][column] == PLAYGROUND_HIT)
	{
		activeHeatMap[row][column] = WATER;
		printf("\n%c-%d: VUOTO!\n", (column + START_UPPERCASE_ASCII), (row + 1));
	}

	else
	{
		activeHeatMap[row][column] = HEAT_MAP_SUCCESSFUL_SCAN;
		printf("\n%c-%d: NAVE!\n", (column + START_UPPERCASE_ASCII), (row + 1));
	}

	passivePlayer = setPlayground(passivePlayer, passivePlayground);
	activePlayer = setHeatMap(activePlayer, activeHeatMap);

	match = setActivePlayer(match, activePlayer);
	match = setPassivePlayer(match, passivePlayer);

	return match;
}

Round radar(Round match, int row, int column)
{
	char passivePlayground[TABLE_MAX][TABLE_MAX];
	char activeHeatMap[TABLE_MAX][TABLE_MAX];

	Player passivePlayer;
	Player activePlayer;

	int i;
	int pivotRow;
	int pivotColumn;
	int endColumn;
	int endRow;

	passivePlayer = getPassivePlayer(match);
	activePlayer = getActivePlayer(match);

	getPlayground(passivePlayer, passivePlayground);
	getHeatMap(activePlayer, activeHeatMap);
	row--;
	column--;
	pivotColumn = column - 1;
	pivotRow = row - 1;
	if (pivotColumn < TABLE_MIN - 1)
	{
		pivotColumn = TABLE_MIN - 1;
	}
	if (pivotRow < TABLE_MIN - 1)
	{
		pivotRow = TABLE_MIN - 1;
	}
	endRow = row + 1;
	endColumn = column + 1;
	if (endRow > TABLE_MAX - 1)
	{
		endRow = TABLE_MAX - 1;
	}
	if (endColumn > TABLE_MAX - 1)
	{
		endColumn = TABLE_MAX - 1;
	}

	printf("Row=%d\tColumn=%d\nPivotRow=%d\tPivotColumn=%d\tEndRow=%d\tEndColumn=%d\n", row, column, pivotRow, pivotColumn, endRow, endColumn);
	while (pivotRow <= endRow)
	{
		i = pivotColumn;
		while (i <= endColumn)
		{
			match = scan(pivotRow, i, match);
			i++;
		}
		pivotRow++;
	}
	return match;
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
