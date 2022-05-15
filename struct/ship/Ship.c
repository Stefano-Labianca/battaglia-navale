#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./Ship.h"
#include "../../utility/converter/converter.h"


/**
 * @brief Restituisce l'etichetta associata ad una nave, all'interno
 * della mappa di gioco.
 *
 * @param ship Nave da cui prendere l'etichetta.
 * @return Carattere che identifica l'etichetta della nave.
 */
char getLabel(Ship ship)
{
	char label;
	label = ship.label;

	return label;
}

/**
 * @brief Restituisce le dimensioni della nave.
 *
 * @param ship Nave da cui prendere le sue dimensioni.
 * @return Dimensioni della nave.
 */
int getSize(Ship ship)
{
	int size;
	size = ship.size;

	return size;
}

/**
 * @brief Restituisce il numero di punti vita disponibili di una nave.
 *
 * @param ship Nave da cui estrarre i punti vita.
 * @return Punti vita della nave.
 */
int getLifePoints(Ship ship)
{
	int lifePoints;
	lifePoints = ship.lifePoints;

	return lifePoints;
}

/**
 * @brief Restituisce un array contenente la cella di partenza e di
 * arrivo di una nave, contenute nel parametro coords.
 *
 * @param ship Nave da cui prendere la cella di partenza e di arrivo.
 * @param  coords Contiene le celle della nave.
 */
void getCoords(Ship ship, char coords[])
{
	int i;
	i = 0;

	while (ship.coords[i] != '\0')
	{
		coords[i] = ship.coords[i];
		i++;
	}

	coords[i] = '\0';

	return;
}

/**
 * @brief Restituisce la direzione della nave, il valore restituito puo'
 * essere pari 'V', nel caso di orientamento verticale, oppure pari a 'O'
 * per l'orientamento orizzontale.
 *
 * @param ship Nave da cui prendere l'orientamento.
 * @return Carattere che rappresenta l'orientamento della nave.
 */
char getDirection(Ship ship)
{
	char direction;
	direction = ship.direction;

	return direction;
}

/**
 * @brief Imposta un'etichetta alla nave, che la indentificherà all'interno della
 * mappa di gioco, restituendo il dato aggiornato.
 *
 * @param ship Nave a cui assegnare un'etichetta.
 * @param label Etichetta da assegnare alla nave.
 * @return Nave aggiornata.
 */
Ship setLabel(Ship ship, char label)
{
	ship.label = label;
	return ship;
}

/**
 * @brief Imposta le dimensioni di una nave, restituendo il dato aggiornato.
 *
 * @param ship Nave a cui assegnare delle dimensioni.
 * @param size Dimensioni della nave.
 * @return Nave aggiornata.
 */
Ship setSize(Ship ship, int size)
{
	ship.size = size;
	return ship;
}

/**
 * @brief Imposta i punti della nave, restituendo il dato aggiornato.
 *
 * @param ship Nave a cui aggiornare i punti vita.
 * @param lifePoints Punti vita della nave.
 * @return Nave aggiornata.
 */
Ship setLifePoints(Ship ship, int lifePoints)
{
	ship.lifePoints = lifePoints;
	return ship;
}

/**
 * @brief Imposta la cella di partenza e di arrivo della nave, restituendo il
 * dato aggiornato.
 *
 * @param ship Nave a cui assegnare la cella di partenza e di arrivo.
 * @param coords Contiene la cella di partenza e di arrivo della nave.
 * @return Nave aggiornata.
 */
Ship setCoords(Ship ship, char coords[])
{
	int i;
	i = 0;

	while (coords[i] != '\0')
	{
		ship.coords[i] = coords[i];
		i++;
	}

	ship.coords[i] = '\0';

	return ship;
}

/**
 * @brief Imposta l'orientamento della nave, restituendo il dato strutturato
 * modificato.
 *
 * @param ship Nave a cui impostare la direzione.
 * @param direction Direzione della nave.
 * @return Nave modificata.
 */
Ship setDirection(Ship ship, char direction)
{
	ship.direction = direction;
	return ship;
}

/**
 * @brief Restituisce il carattere della colonna inserito dall'utente.
 *
 * @return Valore della colonna preso in input.
 */
char getColumn()
{
	int error;
	char col;
	col = ' ';

	do
	{
		error = 0;
		printf("Inserisci la colonna di partenza della nave: ");
		col = getchar();
		col = toUpperCase(col);

		if (col < 'A' || col > 'P')
		{
			error = 1;
			printf("\n\nErrore: devi inserire una lettera compresa tra A e P\n\n"); // TODO: Da gestire meglio la stampa dell'errore
		}

		fflush(stdin);
	} while (error == 1);

	return col;
}

/**
 * @brief Restituisce, sotto forma di stringa, il valore della riga inserito dall'utente.
 *
 * @param row Contiene il valore della riga inserito dall'utente.
 */
void getRow(char row[])
{
	int numericRow;

	numericRow = 0;

	do
	{
		printf("Inserisci la riga di partenza della nave: ");
		scanf("%d", &numericRow);
		fflush(stdin); // FIXME: Mettere un controllo migliore nel caso si metta in input un carattere e non un intero
	} while (isValidRow(numericRow) == 0);

	numberToString(numericRow, row);

	return;
}

/**
 * @brief Verifica se la riga inserita dall'utente sia compresa fra 1 e 16, restituendo
 * 1 se la riga è valida, altrimenti restituisce 0.
 *
 * @param row Numero della riga da controllare.
 * @return Valore di conferma se row è valido o no.
 */
int isValidRow(int row)
{
	int isValid;

	isValid = 1;

	if (row < TABLE_MIN || row > TABLE_MAX)
	{
		isValid = 0;
	}

	return isValid;
}

/**
 * @brief Costruisce una coppia di coordinate, nel formato "colonna-riga", per poi salvare
 * il risultato all'interno dell'array coord.
 *
 * @param column Primo valore della coordinata.
 * @param row Secondo valore della coordinata.
 * @param coord Coordinata nel formato "colonna-riga".
 */
void buildShipCoordinate(char column, char row[], char coord[])
{
	int i;
	int j;

	i = 0;
	j = 2;

	coord[i] = column;
	coord[i + 1] = SEPARATOR;

	while (row[i] != '\0')
	{
		coord[j] = row[i];
		i++;
		j++;
	}

	coord[j] = '\0';

	return;
}

/**
 * @brief Restituisce l'orientamento della nave, preso in input
 * dall'utente. Il valore restituito può essere pari a "V", che definisce
 * l'orientamento verticale, oppure pari a "O" che definisce
 * l'orientamento orizzontale.
 *
 * @return Carattere che definisce l'orientamento della nave.
 */
char getShipDirection()
{
	int error;
	char direction;

	direction = ' ';

	do
	{
		error = 0;
		printf("Inserire V per inserire la nave in verticale, oppure O per inserire la nave in orizzontale: ");

		direction = getchar();
		direction = toUpperCase(direction);

		if (direction != 'O' && direction != 'V')
		{
			error = 1;
			printf("\n\nErrore\n\n"); // TODO: Da gestire meglio la stampa dell'errore
		}

		fflush(stdin);
	} while (error == 1);

	return direction;
}

/**
 * @brief Costruisce e restituisce la successiva coordinata, prendendo in considerazione
 * la coordinata di partenza, le dimensioni della nave e la sua direzione.
 * La coordinata costruita verrà salvata all'interno di nextCoord.
 *
 * @param direction Direzione della nave e può avere un valore pari a 'V' o a 'O'.
 * @param startingCoord Coordinate di partenza della nave.
 * @param shipSize Dimensioni della nave.
 * @param nextCoord Coordinata successiva calcolata.
 */
void buildNextCoord(char direction, char startingCoord[], int shipSize, char nextCoord[])
{
	if (direction == 'V')
	{
		buildVerticalCoord(startingCoord, shipSize, nextCoord);
	}

	else if (direction == 'O')
	{
		buildHorizontalCoord(startingCoord, shipSize, nextCoord);
	}

	return;
}

/**
 * @brief Determina e restituisce, all'interno di nextCoord, la coordinata successiva
 * a quella di partenza, utilizzando le dimensioni della nave.
 *
 * La nuova coordinata calcolata è quella presa sull'asse delle ordinate.
 *
 * @param startingCoord Coordinata di partenza.
 * @param shipSize Dimensioni della nave.
 * @param nextCoord Contiene la coppia di coordinate successive alla prima.
 */
void buildVerticalCoord(char startingCoord[], int shipSize, char nextCoord[])
{
	int numericRow;
	char nextRow[MAX_ROW_LEN];
	int i;

	numericRow = 0;
	i = 2;

	numericRow = stringToNumber(startingCoord, getLength(startingCoord)) + shipSize - 1;
	numberToString(numericRow, nextRow);

	nextCoord[0] = startingCoord[0];
	nextCoord[1] = SEPARATOR;

	while (nextRow[i - 2] != '\0')
	{
		nextCoord[i] = nextRow[i - 2];
		i++;
	}

	nextCoord[i] = '\0';

	return;
}

/**
 * @brief Determina e restituisce, all'interno di nextCoord, la coordinata successiva
 * a quella di partenza, utilizzando le dimensioni della nave.
 *
 * La nuova coordinata calcolata è quella presa sull'asse delle ascisse.
 *
 * @param startingCoord Coordinata di partenza.
 * @param shipSize Dimensioni della nave.
 * @param nextCoord Contiene la coppia di coordinate successive alla prima.
 */
void buildHorizontalCoord(char startingCoord[], int shipSize, char nextCoord[])
{
	int numericColumn;
	char startingColumn;
	char nextColumn;
	int i;

	numericColumn = 0;
	nextColumn = ' ';
	startingColumn = ' ';
	i = 2;

	startingColumn = startingCoord[0];
	numericColumn = getIntegerColumn(startingColumn) + shipSize - 1;
	nextColumn = getCharColumn(numericColumn);

	nextCoord[0] = nextColumn;
	nextCoord[1] = SEPARATOR;

	while (startingCoord[i] != '\0')
	{
		nextCoord[i] = startingCoord[i];
		i++;
	}

	nextCoord[i] = '\0';

	return;
}

/**
 * @brief Concatena e restituisce il valore di startCell e endCell, all'interno
 * dell'array dest. Il contenuto delle due coordinate viene suddiviso
 * dal simbolo "_".
 *
 * Esempio:
 * Input: startCell = A-1, endCell = A-5
 * Output: A-1_A-5
 *
 * @param startCell Coordinata che contiene la cella di partenza della nave.
 * @param endCell Coordinata che contiene la cella di arrivo della nave.
 * @param dest Contiene il contenuto di first e second.
 */
void concatCoordinates(char startCell[], char endCell[], char dest[])
{
	int i;
	int j;

	i = 0;
	j = 0;

	while (startCell[i] != '\0')
	{
		dest[i] = startCell[i];
		i++;
	}

	dest[i] = COORD_SEPARATOR;

	j = i + 1;
	i = 0;

	while (endCell[i] != '\0')
	{
		dest[j] = endCell[i];
		i++;
		j++;
	}

	dest[j] = '\0';

	return;
}

/**
 * @brief Estrae e restituisce, sottoforma di numero naturale,  il valore della
 * colonna di partenza di una nave.
 *
 * Il valore restituito varia da 1 a 16.
 *
 * @param ship Nave da cui estrarre il valore della colonna.
 * @return Rappresentazione numerica della colonna.
 */
int pullColumn(Ship ship)
{
	char range[MAX_COORDS_RANGE];
	int integerColumn;

	getCoords(ship, range);
	integerColumn = getIntegerColumn(range[0]);

	return integerColumn;
}

/**
 * @brief Estrae e restituisce, sottoforma di numero naturale,  il valore della
 * riga di partenza di una nave.
 *
 * Il valore restituito varia da 1 a 16.
 *
 * @param ship Nave da cui estrarre il valore della riga.
 * @return Rappresentazione numerica della riga.
 */
int pullRow(Ship ship)
{
	char range[MAX_COORDS_RANGE];
	char row[MAX_ROW_LEN];
	int integerRow;
	int rowLen;
	int i;

	i = 2;
	getCoords(ship, range);

	while (range[i] != COORD_SEPARATOR)
	{
		row[i - 2] = range[i];
		i++;
	}

	row[i - 2] = '\0';
	rowLen = getLength(row);

	integerRow = stringToNumber(row, rowLen);

	return integerRow;
}

/**
 * @brief Costrutisce e restituisce una nave. La funzione verifica anche
 * se è possibile inserirla all'interno della mappa di gioco del giocatore.
 *
 * @param size Dimensioni della nave.
 * @param number Numero della nave inserita.
 * @param playground Mappa di gioco del giocatore.
 * @return Nave del giocatore.
 */
Ship createShip(int size, int number, char playground[TABLE_MAX][TABLE_MAX])
{
	Ship ship;
	char cell[MAX_COORD_LEN];
	char nextCell[MAX_COORD_LEN];
	char coords[MAX_COORDS_RANGE];

	char column;
	char row[MAX_ROW_LEN];
	char direction;

	printf("IL TUO PLAYGROUND FIN ORA\n");
	showMap(playground);

	do
	{
		printf("\n-- Inserimento navi di dimensioni pari a %d --\n\n", size);
		column = getColumn();
		getRow(row);
		direction = getShipDirection();

		buildShipCoordinate(column, row, cell);
		buildNextCoord(direction, cell, size, nextCell);
		concatCoordinates(cell, nextCell, coords);

	} while (isImpossible(cell, direction, coords, size, playground) == 1);

	ship = setLabel(ship, (number + START_LOWERCASE_ASCII));
	ship = setLifePoints(ship, size);
	ship = setSize(ship, size);
	ship = setCoords(ship, coords);

	ship = setDirection(ship, direction);

	return ship;
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

	i = 0;
	j = 0;

	while (coords[i] != COORD_SEPARATOR)
	{
		i++;
	}

	i++;

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
 * @brief Mostra il contenuto di una mappa di gioco.
 *
 * @param map Mappa di gioco in cui mostrare il contenuto.
 */
void showMap(char map[TABLE_MAX][TABLE_MAX])
{
	int i;
	int j;
	char startColumnSymbol;

	startColumnSymbol = 'A';
	i = 0;

    printf("    ");
	while (i < TABLE_MAX)
    {
		printf(" %c ", startColumnSymbol);
		startColumnSymbol++;
		i++;
	}

	printf("\n");
	i = 0;

    while (i < TABLE_MAX)
    {
		if (i < 9)
        {
			printf(" ");
		}

		j = 0;
		printf(" %d ", i + 1);

		while (j < TABLE_MAX)
        {
			printf(" %c ", map[i][j]); //FIXME: Richiamare la funzione di accesso di Player.c
			j++;
		}

		printf("\n");
		i++;
	}

    return;
}

