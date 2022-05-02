#include <stdlib.h>
#include <stdio.h>

#include "./MapsController.h"
#include "../../global/GlobalConstants.h"
#include "../../struct/round/Round.h"
#include "../../struct/player/Player.h"

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

			row = pullRow(ship) - 1;	   // - 1 not in pseudo
			column = pullColumn(ship) - 1; // - 1 not in pseudo

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

Round scan(int row, int column, Round match) {
	char passivePlayground[TABLE_MAX][TABLE_MAX];
	char activeHeatMap[TABLE_MAX][TABLE_MAX];
	char cell;

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

Round radar(Round match, int row, int column) {
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
 * @brief Verifica se è possibile inserire, all'interno del playground, posizionare una nave
 * in una data posizione. La funzione restituisce 1, se non è possibile inserire la nave in una data
 * posizione, altrimenti restituisce 0 se è possibile inserire la nave in una data posizione.
 *
 * @param cell Posizione di partenza della nave.
 * @param direction Direzione della nave.
 * @param coords Range di coordinate della nave.
 * @param size Dimensioni della nave.
 * @param playground Mappa di gioco del giocatore.
 * @return Valore numerico pari a 1 o 0, che rappresenta l'esito del controllo.
 */
int isImpossible(char cell[], char direction, char coords[], int size, char playground[TABLE_MAX][TABLE_MAX])
{
	int error;
	int row;
	int column;

	error = 0;
	row = stringToNumber(cell, getLength(cell));
	column = getIntegerColumn(cell[0]);

	if (checkBoundaries(row, column, size, direction) == 0)
	{
		if (checkCollisions(playground, coords) == 1)
		{
			printf("\n\nCoordinate non valide: sei in contatto con un altra nave\n\n");
			error = 1;
		}
	}

	else
	{
		printf("\n\nCoordinate non valide: stai violando i confini della mappa\n\n");
		error = 1;
	}

	return error;
}

/**
 * @brief Controlla se la posizione della nave, non vada oltre i limiti della mappa
 * di gioco, restituendo 1 se va oltre i limiti della mappa, altrimenti restituisce 0
 * se rispetta i limiti della mappa.
 *
 * @param row Riga di partenza della nave.
 * @param column Colonna di partenza della nave.
 * @param size Dimensioni della nave.
 * @param direction Direzione della nave.
 * @return Valore numerico pari a 1 o 0, che rappresenta l'esito del controllo.
 */
int checkBoundaries(int row, int column, int size, char direction)
{
	int error;
	error = 0;

	if (direction == 'V')
	{
		if (row - 1 + size > TABLE_MAX)
		{
			error = 1;
		}
	}

	else if (direction == 'O')
	{
		if (column - 1 + size > TABLE_MAX)
		{
			error = 1;
		}
	}

	return error;
}

/**
 * @brief Verifica se una nave sta entrando in collisione con un'altra nave o se
 * supera i confini della mappa di gioco, restituendo 1 se vengono violati uno dei
 * due vincoli altrimenti, se vengono rispettati entrambi,	 restituisce 0.
 *
 * @param playground Playground di un giocatore.
 * @param direction Direzione della nave.
 * @param coords Range di coordinate di una nave.
 * @param shipSize Dimensioni della nave.
 * @return Restituisce un valore numerico pari a 1 o 0, che rappresentano
 * l'esito della verifica dei vincoli.
 */
int checkCollisions(char playground[TABLE_MAX][TABLE_MAX], char coords[])
{
	int error;
	char firstCell[MAX_COORD_LEN];
	char lastCoord[MAX_COORD_LEN];
	int pivotRow;
	int pivotColumn;
	int i;
	int endRow;
	int endColumn;

	error = 0;
	getFirstCell(coords, firstCell);
	getLastCell(coords, lastCoord);

	pivotColumn = getIntegerColumn(firstCell[0]) - 2;
	pivotRow = stringToNumber(firstCell, getLength(firstCell)) - 2;

	if (pivotColumn < TABLE_MIN - 1)
	{
		pivotColumn = TABLE_MIN - 1;
	}
	if (pivotRow < TABLE_MIN - 1)
	{
		pivotRow = TABLE_MIN - 1;
	}

	endColumn = getIntegerColumn(lastCoord[0]);
	endRow = stringToNumber(lastCoord, getLength(lastCoord));
	if (endColumn > TABLE_MAX - 1)
	{
		endColumn = TABLE_MAX - 1;
	}

	if (endRow > TABLE_MAX - 1)
	{
		endRow = TABLE_MAX - 1;
	}

	while (pivotRow <= endRow)
	{
		i = pivotColumn;
		while (i <= endColumn)
		{
			if (playground[pivotRow][i] != WATER)
			{
				if (playground[pivotRow][i] >= 'a' && playground[pivotRow][i] <= 'p')
				{
					{
						error = 1;
					}
				}
			}

			i++;
		}
		pivotRow++;
	}

	return error;
}

/**
 * @brief Verifica la possibilità di inserire una nave in verticale, all'interno del playground
 * di gioco. Restituisce 0 se l'inserimento è avvenuto con successo, altrimenti restituisce 1
 * in caso si sia verificato un errore.
 *
 * @param playground Mappa di gioco di un giocatore.
 * @param coords Range di coordinate di una nave.
 * @param shipSize Dimensioni della nave.
 * @return Valore numerico pari a 1 o 0, che rappresentano l'esito del controllo.
 */
// int checkVerticalCollisions(char playground[TABLE_MAX][TABLE_MAX], char coords[], int shipSize)
// {
// 	int error;
// 	char firstCell[MAX_COORD_LEN];
// 	char lastCoord[MAX_COORD_LEN];
// 	int pivotRow;
// 	int pivotColumn;
// 	int i;
// 	int endRow;
// 	int endColumn;

// 	/**
// 	 * Allora breve spiegazione.
// 	 *
// 	 * Il pivot rappresenta un punto dove si inizia la ricerca
// 	 * della collisione. Prendiamo la cella di partenza e l'ultima cella della nave, dalla
// 	 * cella di partenza, converto in valore numerico le colonne e le righe, così da manipolarle
// 	 * meglio:
// 	 * 		firstCell: char[] = ['E', '-', '4']
// 	 * 		relativePivotColumn: int = 5 -> (converto la 'E' nel numero di colonna relativo, ovvero 5)
// 	 * 		relativePivotRow: int = 4 -> (converto il '4' nel numero di riga relativo, ovvero 4)

// 	 * Dico relativo perchè parte tutto da zero e la funzione che converte i valori dati li restituisce
// 	 * senza diminuire di 1 i valori dati
// 	 *
// 	 * Ora converti relativePivotColumn e relativePivotRow nel loro valore assoluto:
// 	 * 		absolutePivotColumn: int = relativePivotColumn - 1 = 4
// 	 * 		absolutePivotRow: int = relativePivotRow - 1 = 3
// 	 *
// 	 * Ora ricavati la posizione del pivot, andando in alto a sinistra (in diagonale a sinistra) di una cella rispetto
// 	 * alla cella di partenza della nave:
// 	 * 		pivotColumn: int = absolutePivotColumn - 1 = 3
// 	 * 		pivotRow: int = absolutePivotRow - 1 = 2
// 	 *
// 	 * Per questo motivo nel codice ho messo -2 :)
// 	*/
// 	error = 0;
// 	getFirstCell(coords, firstCell);
// 	getLastCell(coords, lastCoord);

// 	pivotColumn = getIntegerColumn(firstCell[0]) - 2;
// 	pivotRow = stringToNumber(firstCell, getLength(firstCell)) - 2;

// 	if (pivotColumn < 0)
// 	{
// 		pivotColumn = 0;
// 	}
// 	if (pivotRow < 0)
// 	{
// 		pivotRow = 0;
// 	}

// 	endColumn = getIntegerColumn(lastCoord[0]);
// 	endRow = stringToNumber(lastCoord, getLength(lastCoord));
// 	if (endColumn > 15)
// 	{
// 		endColumn = 15;
// 	}

// 	if (endRow > 15)
// 	{
// 		endRow = 15;
// 	}

// 	while (pivotRow <= endRow)
// 	{
// 		i = pivotColumn;
// 		while (i <= endColumn)
// 		{
// 			if (playground[pivotRow][i] != WATER)
// 			{
// 				if (playground[pivotRow][i] >= 'a' && playground[pivotRow][i] <= 'p')
// 				{
// 					{
// 						error = 1;
// 					}
// 				}
// 			}

// 			i++;
// 		}
// 		pivotRow++;
// 	}

	/*if (pivotColumn < 0) {
		pivotColumn = 0;
	}

	if (pivotRow < 0) {
		pivotRow = 0;
	}

	i = pivotColumn; // Scansiona le colonne
	j = pivotRow;	 // Scansiona le righe
	k = 0;

	limit = pivotRow + shipSize + 1;

	if (limit > 15) {
		limit = 15;
	}

	while (k < SEARCH_RADIUS)
	{
		j = pivotRow;

		while (j <= limit)
		{
			printf("[ROW=%d][COL=%d]=%c\n",j,i,playground[j][i]);
			if (playground[j][i] != WATER)
			{
				if (playground[j][i] >= 'a' && playground[j][i] <= 'p')
				{
					error = 1;
					j = limit;
					k = SEARCH_RADIUS;
				}
			}

			j++;
		}

		k++;
		i++;
	}*/

// 	return error;
// }

/**
 * @brief Verifica la possibilità di inserire una nave in orizzontale, all'interno del playground
 * di gioco. Restituisce 0 se l'inserimento è avvenuto con successo, altrimenti restituisce 1
 * in caso si sia verificato un errore.
 *
 * @param playground Mappa di gioco di un giocatore.
 * @param coords Range di coordinate di una nave.
 * @param shipSize Dimensioni della nave.
 * @return Valore numerico pari a 1 o 0, che rappresentano l'esito del controllo.
 */
/*int checkHorizontalCollisions(char playground[TABLE_MAX][TABLE_MAX], char coords[], int shipSize)
{
	int error;
	char firstCell[MAX_COORD_LEN];
	char lastCoord[MAX_COORD_LEN];
	int pivotRow;
	int pivotColumn;
	int i;
	int j;
	int k;
	int limit;

	/**
	 * Allora breve spiegazione.
	 *
	 * Il pivot rappresenta un punto dove si inizia la ricerca
	 * della collisione. Prendiamo la cella di partenza e l'ultima cella della nave, dalla
	 * cella di partenza, converto in valore numerico le colonne e le righe, così da manipolarle
	 * meglio:
	 * 		firstCell: char[] = ['D', '-', '4']
	 * 		relativePivotColumn: int = 4 -> (converto la 'D' nel numero di colonna relativo, ovvero 4)
	 * 		relativePivotRow: int = 4 -> (converto il '4' nel numero di riga relativo, ovvero 4)

	 * Dico relativo perchè si parte tutto da zero e la funzione che converte i valori dati li restituisce
	 * senza diminuire di 1 i valori dati (big brain power potevi pensarci prima brutto str*nzo)
	 *
	 * Ora converti relativePivotColumn nel loro valore assoluto:
	 * 		absolutePivotColumn: int = relativePivotColumn - 1 = 3
	 *
	 * Ora ricavati la posizione del pivot, andando in basso a sinistra (in diagonale a sinistra) di una cella rispetto
	 * alla cella di partenza della nave:
	 * 		pivotColumn: int = absolutePivotColumn - 1 = 2
	 *
	 * Per questo motivo nel codice ho messo -2 alla colonna :)
	 *
	 * Non faccio questo ragionamento per la riga del pivot perchè, se la posizione relativa è 4 e la sua posizione
	 * assoluta è 3. Dato che devo andare in basso a sinistra nella ricerca, devo incrementare di uno la riga e
	 * quindi 4 -1 + 1 = 4 e allora lascio la posizione relativa della riga.


	getFirstCell(coords, firstCell);
	getLastCell(coords, lastCoord);

	pivotColumn = getIntegerColumn(firstCell[0]) - 2;
	pivotRow = stringToNumber(firstCell, getLength(firstCell));

	i = pivotRow;	 // Scansiona le righe
	j = pivotColumn; // Scansiona le colonne
	k = 0;
	limit = pivotColumn + shipSize + 1;

	while (k < SEARCH_RADIUS)
	{
		j = pivotColumn;

		while (j <= limit)
		{
			if (playground[i][j] != WATER)
			{
				if (playground[i][j] >= 'a' && playground[i][j] <= 'p')
				{
					error = 1;
					j = limit;
					k = SEARCH_RADIUS;
				}
			}

			j++;
		}

		k++;
		i--;
	}

	return error;
}*/

/**
 * @brief Restituisce la prima cella del range di coordinate di
 * una nave, riportandola all'interno del parametro cell.
 *
 * @param coords Range di coordinate di una nave.
 * @param cell Array che contiene la prima cella.
 */
void getFirstCell(char coords[], char cell[])
{
	int i;
	i = 0;

	while (coords[i] != COORD_SEPARATOR)
	{
		cell[i] = coords[i];
		i++;
	}

	cell[i] = '\0';

	return;
}

/**
 * @brief Restituisce l'ultima cella del range di coordinate di
 * una nave, riportandola all'interno del parametro cell.
 *
 * @param coords Range di coordinate di una nave.
 * @param cell Array che contiene l'ultima cella.
 */
void getLastCell(char coords[], char cell[])
{
	int i;
	int j;
	int underScorePosition;

	i = 0;
	j = 0;
	underScorePosition = 0;

	while (coords[i] != COORD_SEPARATOR)
	{
		underScorePosition++;
		i++;
	}

	i = underScorePosition + 1;

	while (coords[i] != '\0')
	{
		cell[j] = coords[i];
		j++;
		i++;
	}

	cell[j] = '\0';

	return;
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
