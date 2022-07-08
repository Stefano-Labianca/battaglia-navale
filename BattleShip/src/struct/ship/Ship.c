#include <stdio.h>
#include <stdlib.h>

#include "./Ship.h"
#include "../player/Player.h"
#include "../../utility/converter/converter.h"

/**
 * Funzione getLabel
 * 
 * DESCRIZIONE: Restituisce l'etichetta associata ad una nave, all'interno
 * della mappa di gioco.
 *
 * INPUT 
 * ship -  Nave da cui prendere l'etichetta - ship - /
 * 
 * OUTPUT 
 * label - Carattere che identifica l'etichetta della nave - Carattere - Le label vanno dalla 'a' (prima nave) alla 'o' (quindicesima nave)
 * 
 */
char getLabel(Ship ship)
{
	char label;
	label = ship.label;

	return label;
}

/**
 * Funzione getSize
 * 
 * DESCRIZIONE: Restituisce le dimensioni della nave.
 *
 * INPUT
 * ship - Nave da cui prendere le sue dimensioni - ship - /
 * 
 * OUTPUT 
 * size - Dimensioni della nave - numero intero - size >= MIN_SHIP_SIZE AND size <= MAX_SHIP_SIZE
 *
 * 
 *
 */
int getSize(Ship ship)
{
	int size;
	size = ship.size;

	return size;
}

/**
 * Funzione: getLifePoints
 * 
 * DESCRIZIONE:  Restituisce il numero di punti vita disponibili di una nave.
 *
 * INPUT
 * ship - Nave da cui estrarre i punti vita - ship - /
 * 
 * OUTPUT 
 * lifePoints - Punti vita della nave - Numero intero - lifePoints >= 0 AND lifePoints <= MAX_LIFE_POINTS
 * 
 *
 */
int getLifePoints(Ship ship)
{
	int lifePoints;
	lifePoints = ship.lifePoints;

	return lifePoints;
}

/**
 * Funzione getCoords
 * 
 * DESCRIZIONE:  Restituisce un array contenente la cella di partenza e di
 * arrivo di una nave, contenute nel parametro coords.
 *
 * INPUT 
 * ship - Nave da cui prendere la cella di partenza e di arrivo - ship - /
 * 
 * OUTPUT
 * coords - Contiene le celle della nave - Stringa - Formato: primaCella_ultimaCella
 * 
 * LAVORO
 * i - Contatore per le posizioni all'interno delle stringhe - Numero intero - i > 0
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
 * Funzione getDirection
 * 
 * DESCRIZIONE:  Restituisce la direzione della nave, il valore restituito puo'
 * essere pari 'V', nel caso di orientamento verticale, oppure pari a 'O'
 * per l'orientamento orizzontale.
 *
 * INPUT 
 * ship - Nave da cui prendere l'orientamento - ship - /
 * 
 * OUTPUT 
 * direction - Carattere che rappresenta l'orientamento della nave - Carattere - V = Verticale, O = Orizzontale
 * 
 * LAVORO
 */
char getDirection(Ship ship)
{
	char direction;
	direction = ship.direction;

	return direction;
}

/**
 * Funzione setLabel
 * 
 * DESCRIZIONE:  Imposta un'etichetta alla nave, che la indentifichera' all'interno della
 * mappa di gioco, restituendo il dato aggiornato.
 *
 * INPUT
 * ship - Nave a cui assegnare un'etichetta - ship - /
 * label - Etichetta da assegnare alla nave - Carattere - Le label vanno dalla 'a' (prima nave) alla 'o' (quindicesima nave)
 *
 * OUTPUT
 * ship - Nave aggiornata - ship - /
 */
Ship setLabel(Ship ship, char label)
{
	ship.label = label;
	return ship;
}

/**
 * Funzione setSize
 * 
 * DESCRIZIONE:  Imposta le dimensioni di una nave, restituendo il dato aggiornato.
 *
 * INPUT
 * ship - Nave a cui assegnare delle dimensioni - ship - /
 * size - Dimensioni della nave - Numero intero - size >= MIN_SHIP_SIZE AND size <= MAX_SHIP_SIZE
 * 
 * OUTPUT
 * ship - Nave aggiornata - ship - /
 * 
 * LAVORO
 */
Ship setSize(Ship ship, int size)
{
	ship.size = size;
	return ship;
}

/**
 * DESCRIZIONE: Imposta i punti vita della nave, restituendo il dato aggiornato.
 *
 * INPUT
 * ship - Nave a cui aggiornare i punti vita - ship	- /
 * lifePoints - Punti vita della nave - Numero intero - lifePoints > 0 AND lifePoints < MAX_SHIP_SIZE
 *
 * OUTPUT
 * ship	- Nave aggiornata - ship - /
 *
 */
Ship setLifePoints(Ship ship, int lifePoints)
{
	ship.lifePoints = lifePoints;
	return ship;
}

/**
 * Funzione setCoords 
 * 
 * DESCRIZIONE: Imposta la cella di partenza e di arrivo della nave.
 *
 * INPUT
 * ship - Nave a cui assegnare la cella di partenza e di arrivo - ship - /
 * coords - Contiene la cella di partenza e di arrivo della nave - Stringa - Formato: primaCella_ultimaCella
 *  
 * OUTPUT 
 * ship - Nave aggiornata - ship - /
 *
 * LAVORO
 * i - Contatore per le posizioni all'interno delle stringhe - Numero intero - i > 0
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
 * Funzione setDirection
 * DESCRIZIONE:  Imposta l'orientamento della nave, restituendo il dato strutturato
 * modificato.
 *
 * INPUT
 * ship - Nave a cui impostare la direzione - ship - / 
 * direction - Direzione della nave - Carattere - V = Verticale, O = Orizzontale
 * 
 * OUTPUT
 * ship - Nave modificata - ship - /
 * 
 * LAVORO
 */
Ship setDirection(Ship ship, char direction)
{
	ship.direction = direction;
	return ship;
}

/**
 * Funzione getColumn
 * 
 * DESCRIZIONE:  Restituisce il carattere della colonna inserito dall'utente.
 * 
 * INPUT
 * column - Contiene il valore della colonna inserito dall'utente - Carattere - Compreso tra 'A' e 'P'
 * 
 * OUTPUT 
 * column - Contiene il valore della colonna inserito dall'utente - Carattere - Compreso tra 'A' e 'P'
 * 
 * LAVORO
 * error - Indica se il carattere inserito e' valido o meno - numero intero - 1 = carattere inserito non valido, 0 = carattere inserito valido
 */
char getColumn()
{
	int error;
	char column;
	column = ' ';

	do
	{
		error = 0;
		printf("Inserisci la colonna di partenza della nave: ");

		column = getchar();
		column = toUpperCase(column);
		
		if (column < 'A' || column > 'P')
		{
			error = 1;
			printf("\nErrore: devi inserire una lettera compresa tra A e P\n\n");
		}
		
		fflush(stdin);
	} while (error == 1);
	return column;
}

/**
 * Funzione getRow
 * 
 * DESCRIZIONE: Restituisce, sotto forma di stringa, il valore della riga inserito dall'utente.
 *
 * INPUT
 * row - Contiene il valore della riga inserito dall'utente - Numero intero - numericRow >= TABLE_MIN AND numericRow <= TABLE_MAX
 *
 * OUTPUT
 * row - Contiene il valore della riga inserito dall'utente - Numero intero - numericRow >= TABLE_MIN AND numericRow <= TABLE_MAX
 * 
 * LAVORO
 * isValid - Indica se il valore inserito dall'utente e' valido o meno - Numero intero - 0 = valore non valido, 1 = valore valido
 * 
 */
void getRow(char row[])
{
	int numericRow;

	do
	{
		printf("Inserisci la riga di partenza della nave: ");
		scanf("%d", &numericRow);
		fflush(stdin);
	} while (isValidRow(numericRow) == 0);
	
	numberToString(numericRow, row);
	return;
}

/**
 * Funzione isValidRow
 * 
 * DESCRIZIONE:  Verifica se la riga inserita dall'utente sia compresa fra 1 e 16, restituendo
 * 1 se la riga e' valida, altrimenti restituisce 0.
 *
 * INPUT
 * row - Numero della riga da controllare. - Numero intero - /
 * TABLE_MIN - Riga/Colonna minima - Numero intero - 1
 * TABLE_MAX - Riga/Colonna massima - Numero intero - 16
 * 
 * OUTPUT
 * isValid - Valore di conferma se row e' valido o no. Per essere valido deve essere compreso
 * fra TABLE_MIN e TABLE_MAX - Numero intero - 1 = valore valido, 0 = valore non valido
 * 
 * LAVORO
 */
int isValidRow(int row)
{
	int isValid;

	isValid = 1;
	if (row < TABLE_MIN || row > TABLE_MAX)
	{
		isValid = 0;
		printf("\nErrore: devi inserire un numero compreso tra 1 e 16\n\n");
	}
	return isValid;
}

/**
 * Funzione buildShipCoordinate
 * 
 * DESCRIZIONE: Costruisce una coppia di coordinate, nel formato "colonna-riga", per poi salvare
 * il risultato all'interno dell'array coord.
 *
 * INPUT
 * column - Primo valore della coordinata - carattere - column >= 'A' AND column <= 'P' 
 * row - Secondo valore della coordinata - Stringa - Contiene un numero compreso tra 1 e 16
 * START_ROW_COORD - Inizio della riga nelle coordinate - Numero intero - 3
 * SEPARATOR - Separatore tra riga e colonna - Carattere - '-'
 * 
 * OUTPUT
 * coord - Coordinata nel formato "colonna-riga" - Stringa - Formato: Colonna - Riga
 * 
 * LAVORO
 * i - Indice di scorrimento per le stringhe - Numero intero - i > 0
 * j - Indice di scorrimento per le stringhe - Numero intero - j > 0
 */
void buildShipCoordinate(char column, char row[], char coord[])
{
	int i;
	int j;

	i = 0;
	j = START_ROW_COORD;

	// formato coord: colonna-riga
	// la colonna ha un carattere, il secondo carattere di coord e' quindi il SEPARATOR
	coord[i] = column;
	coord[i + 1] = SEPARATOR;

	// copia della riga
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
 * Funzione getShipDirection
 *
 * DESCRIZIONE:  Restituisce l'orientamento della nave, preso in input
 * dall'utente. Il valore restituito puo' essere pari a "V", che definisce
 * l'orientamento verticale, oppure pari a "O" che definisce
 * l'orientamento orizzontale.
 * 
 * INPUT
 * direction - Orientamento della nave preso in input - Carattere - V = Verticale, O = Orizzontale
 * 
 * OUTPUT
 * direction - Orientamento della nave preso in input - Carattere - V = Verticale, O = Orizzontale
 * 
 * error - Indica se il carattere inserito rappresenta o meno una direzione - numero intero - 1 = carattere inserito non 
 * valido, 0 = carattere inserito valido 
 * 
 */
char getShipDirection()
{
	int error;
	char direction;

	do
	{
		error = 0;
		printf("\nInserire V per inserire la nave in verticale, oppure O per inserire la nave in orizzontale: ");

		direction = getchar();
		direction = toUpperCase(direction);

		if (direction != 'O' && direction != 'V')
		{
			error = 1;
			printf("\nErrore: inserire un'opzione valida\n");
		}

		fflush(stdin);
	} while (error == 1);

	return direction;
}

/**
 * Funzione buildNextCoord
 * 
 * DESCRIZIONE:  Costruisce e restituisce la successiva coordinata, prendendo in considerazione
 * la coordinata di partenza, le dimensioni della nave e la sua direzione.
 * La coordinata costruita verra' salvata all'interno di nextCoord.
 *
 * INPUT
 * direction - Direzione della nave e puo' avere un valore pari a 'V' o a 'O'. - Carattere - V = Verticale, O = Orizzontale
 * startingCoord - Coordinate di partenza della nave. - Stringa - Formato: riga-colonna
 * shipSize - Dimensioni della nave. - Numero intero - shipSize >= MIN_SHIP_SIZE AND shipSize <= MAX_SHIP_SIZE
 * 
 * OUTPUT
 * nextCoord - Coordinata successiva calcolata - Stringa - Formato: riga-colonna
 *
 *
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
 * Funzione buildVerticalCoord
 * 
 * DESCRIZIONE:  Determina e restituisce, all'interno di nextCoord, la coordinata successiva
 * a quella di partenza, utilizzando le dimensioni della nave.
 *
 * La nuova coordinata calcolata e' quella presa sull'asse delle ordinate.
 *
 * INPUT
 * startingCoord - Coordinata di partenza - Carattere - Formato: riga-colonna
 * shipSize - Dimensioni della nave - Numero intero - shipSize >= MIN_SHIP_SIZE AND shipSize <= MAX_SHIP_SIZE
 * START_ROW_COORD - Inizio della riga nelle coordinate - Numero intero - 3
 * SEPARATOR - Separatore tra riga e colonna - Carattere - '-'
 *
 * OUTPUT
 * nextCoord - Coordinata finale - Stringa -  Formato: riga-colonna
 *
 * LAVORO
 * numericRow - Valore della riga della coordinata finale - Numero intero - numericRow >= TABLE_MIN AND numericRow <= TABLE_MAX
 * nextRow - Valore della riga della coordinata finale - Stringa -  Contiene il valore di numericRow
 * i - Indice di scorrimento delle stringhe - Numero intero - i > 0 
 * len - Lunghezza di startingCoord - Intero - Lunghezza compresa tra 3 e 4 (ENDSTRING escluso)
 */
void buildVerticalCoord(char startingCoord[], int shipSize, char nextCoord[])
{
	int numericRow;
	char nextRow[MAX_ROW_LEN];
	int i;
	int len;

	i = START_ROW_COORD;
	len = getLength(startingCoord); // varia tra 3 e 4 a seconda che la riga sia tra 1 e 9 oppure tra 10 e 16
	
	// Calcolo la riga finale, convertendo la coordinata di partenza in numero,
	// aggiungo la dimensione della nave e decremento di 1 per ottenere l'ultima cella occupata dalla nave
	numericRow = stringToNumber(startingCoord, len) + shipSize - 1;

	// Converto la riga in stringa
	numberToString(numericRow, nextRow);
	nextCoord[0] = startingCoord[0];
	nextCoord[1] = SEPARATOR;
	
	// Parto da i - 2 perche' parto dall'inizio di nextRow e inserisco la riga dopo il SEPARATOR in nextCoord
	while (nextRow[i - 2] != '\0')
	{
		nextCoord[i] = nextRow[i - 2];
		i++;
	}
	nextCoord[i] = '\0';
	
	return;
}

/**
 * Funzione buildHorizontalCoord
 * 
 * DESCRIZIONE:  Determina e restituisce, all'interno di nextCoord, la coordinata successiva
 * a quella di partenza, utilizzando le dimensioni della nave.
 *
 * La nuova coordinata calcolata e' quella presa sull'asse delle ordinate.
 *
 * INPUT
 * startingCoord - Coordinata di partenza - Carattere - Formato: riga-colonna
 * shipSize - Dimensioni della nave - Numero intero - shipSize >= MIN_SHIP_SIZE AND shipSize <= MAX_SHIP_SIZE
 * START_ROW_COORD - Inizio della riga nelle coordinate - Numero intero - 3
 * SEPARATOR - Separatore tra riga e colonna - Carattere - '-'
 *
 * OUTPUT
 * nextCoord - Coordinata finale - Stringa -  Formato: riga-colonna
 *
 * LAVORO
 * numericColumn - Valore della colonna della coordinata finale - Numero intero - numericColumn >= TABLE_MIN AND numericColumn <= TABLE_MAX
 * startingColumn - Colonna della prima coordinata - Carattere - startingColumn >= 'A' AND startingColumn <= 'P'
 * nextColumn - Colonna dell'ultima coordinata - Carattere - nextColumn >= 'A' AND nextColumn <= 'P'
 * i - Indice di scorrimento per le stringhe - Numero intero - i > 0
 */
void buildHorizontalCoord(char startingCoord[], int shipSize, char nextCoord[])
{
	int numericColumn;
	char startingColumn;
	char nextColumn;
	int i;

	i = START_ROW_COORD;
	startingColumn = startingCoord[0];
	// Calcolo la colonna finale, convertendo la coordinata di partenza in numero,
	// aggiungo la dimensione della nave e decremento di 1 per ottenere l'ultima cella occupata dalla nave
	numericColumn = getIntegerColumn(startingColumn) + shipSize - 1;
	nextColumn = getCharColumn(numericColumn);

	nextCoord[0] = nextColumn;
	nextCoord[1] = SEPARATOR;

	// Copio la riga
	while (startingCoord[i] != '\0') 
	{
		nextCoord[i] = startingCoord[i];
		i++;
	}
	
	nextCoord[i] = '\0';
	return;
}

/**
 * Funzione concatCoordinates
 * DESCRIZIONE: Concatena e restituisce il valore di startCell e endCell, all'interno
 * dell'array dest. Il contenuto delle due coordinate viene suddiviso
 * dal simbolo "_".
 *
 * Esempio:
 * Input: startCell = A-1, endCell = A-5
 * Output: A-1_A-5
 *
 * INPUT
 * startCell - Prima coordinata della nave - Stringa - Formato: riga-colonna
 * endCell - Ultima coordinata della nave - Stringa - Formato: riga-colonna
 * COORD_SEPARATOR - Separatore di coordinate - Carattere - '_'
 * 
 * OUTPUT
 * dest - Concatenazione delle coordinate - Stringa - formato startCell_endCell
 *
 * LAVORO
 * i - Indice di scorrimento delle stringhe - Numero intero - i > 0
 * j - Indice di scorrimento delle stringhe - Numero intero - j > 0
 */
void concatCoordinates(char startCell[], char endCell[], char dest[])
{
	int i;
	int j;

	i = 0;
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
 * Funzione pullColumn
 * 
 * DESCRIZIONE:  Estrae e restituisce, sottoforma di numero naturale, il valore della
 * colonna di partenza di una nave.
 *
 * Il valore restituito varia da 1 a 16.
 *
 * INPUT
 * ship - Nave da cui estrarre il valore della colonna - ship - /
 * 
 * OUTPUT
 * integerColumn - Valore numerico della colonna - Numero intero - integerColumn >= TABLE_MIN AND integerColumn <= TABLE_MAX
 *  
 * LAVORO
 * range - Range di coordinate della nave - Stringa - Formato: primaCella_ultimaCella
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
 * Funzione pullRow
 * DESCRIZIONE:  Estrae e restituisce, sottoforma di numero naturale,  il valore della
 * riga di partenza di una nave.
 *
 * INPUT
 * Ship - Nave da cui estrarre il valore della riga - Ship - /
 * COORD_SEPARATOR - Separatore di coordinate - Carattere - '_'
 * START_ROW_COORD - Inizio della riga nelle coordinate - Numero intero - 3
 * 
 * OUTPUT
 * integerRow - Valore numerico della riga - Numero intero - integerRow >= TABLE_MIN AND integerRow <= TABLE_MAX
 * 
 * LAVORO
 * range - Range di coordinate della nave - Stringa - Formato: primaCella_ultimaCella
 * row - Valore della riga - Stringa - Contiene un numero compreso tra 1 e 16
 * rowLen - Lunghezza della stringa row - Numero intero - Lunghezza compresa tra 1 e 2 (ENDSTRING escluso)
 * i - Indice di scorrimento per le stringhe - Numero intero - i > 0
 */
int pullRow(Ship ship)
{
	char range[MAX_COORDS_RANGE];
	char row[MAX_ROW_LEN];
	int integerRow;
	int rowLen;
	int i;

	i = START_ROW_COORD; // Parto da 2 per risparmiare un indice
	getCoords(ship, range);

	// Copio la riga
	while (range[i] != COORD_SEPARATOR)
	{
		// Parto da i - 2 perche' parto dall'inizio di row e inserisco la riga della prima cella di range
		row[i - 2] = range[i];
		i++;
	}
	
	row[i - 2] = '\0';
	rowLen = getLength(row);
	integerRow = stringToNumber(row, rowLen);

	return integerRow;
}

/**
 * Funzione createShip
 * DESCRIZIONE:  Costruisce e restituisce una nave. La funzione verifica anche
 * se e' possibile inserirla all'interno della mappa di gioco del giocatore.
 *
 * INPUT
 * size - Dimensione della nave - Numero intero - size >= MIN_SHIP_SIZE AND size <= MAX_SHIP_SIZE
 * number - Numero della nave - Numero intero - number >= 1 AND number <= MAX_SHIP_AMOUNT
 * Playground - Playground nel quale deve essere caricata la nave - Array bidimensionale di caratteri - Dimensione 16x16;
 * Caratteri consentiti:
 * Da 'a' a 'o' per le navi
 * '~' per il mare
 * 'x' nave colpita
 * '*' nave affondata
 * START_LOWERCASE_ASCII - Prima lettera dell'alfabeto minuscola in ASCII - Numero intero - 97
 * 
 * OUTPUT
 * ship - Nave del giocatore - Ship - /
 * 
 * LAVORO
 * cell - Prima coordinata della nave - Stringa - Formato: riga-colonna
 * nextCell - Ultima coordinata della nave - Stringa - Formato: riga-colonna
 * coords - Range di coordinate della nave - Stringa - Formato: primaCella_ultimaCella
 * column - Indica la colonna della prima coordinata della nave - Carattere - column >= 'A' AND column <= 'P'
 * row - Contiene il valore della riga della prima coordinata della nave - Stringa - Contiene un numero tra 1 e 16
 * direction - Orientamento della nave - Stringa - V = Verticale; O = Orizzontale
 * isImpossibileToDo - Indica l'impossibilita' di inserire una nave nel range di coordinate scelto - Numero intero - 1 = Impossibile inserire nave; 0 = La nave puo' essere inserita
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
	int isImpossibleToDo;

	printf("\nIL TUO PLAYGROUND FINO AD ORA\n");
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
	
		isImpossibleToDo = isImpossible(cell, direction, coords, size, playground);
	} while (isImpossibleToDo == 1);

	ship = setLabel(ship, (number + START_LOWERCASE_ASCII));
	ship = setLifePoints(ship, size);
	ship = setSize(ship, size);
	ship = setCoords(ship, coords);
	ship = setDirection(ship, direction);
	return ship;
}

/**
 * Funzione isImpossible
 * DESCRIZIONE: Verifica se e' possibile inserire, all'interno del playground, posizionare una nave
 * in una data posizione. La funzione restituisce 1, se non e' possibile inserire la nave in una data
 * posizione, altrimenti restituisce 0 se e' possibile inserire la nave in una data posizione.
 *
 * INPUT
 * cell - Posizione di partenza della nave - Stringa - Formato: riga-colonna
 * direction - Direzione della nave - carattere - V = Verticale; O = Orizzontale
 * coords - Range di coordinate della nave - Stringa - Formato: primaCella_ultimaCella
 * size - Dimensioni della nave - Stringa - Size >= MIN_SHIP_SIZE AND size <= MAX_SHIP_SIZE
 * playground - Mappa di gioco del giocatore - Array a due dimensioni di caratteri - Dimensione 16x16;
 * Caratteri consentiti:
 * da 'a' a 'o' per le navi
 * '~' per il mare
 * 'x' per nave colpita
 * '*' per nave affondata
 * 
 * OUTPUT
 * error - Valore numerico pari a 1 o 0 che rappresenta l'esito del controllo - Intero - 1 = inserimento impossibile; 0 = inserimento possibile
 * 
 * LAVORO
 * row - Riga della cella - intero - row >= TABLE_MIN AND row <= TABLE_MAX
 * column - Colonna della cella - intero - column >= TABLE_MIN AND column <= TABLE_MAX
 * len - Lunghezza della stringa cella - Intero - len compreso tra 3 e 4 (carattere di ENDSTRING escluso)
 * checkMapBoundaries - Indica se si stanno violando i confini della mappa - Intero	- 1 = confini violati; 0 = confini non violati
 * checkShipCollisions - Indica se si e' in contatto con un'altra nave - Intero - 1 = si e' in contatto con un'altra nave; 0 = non si e' in contatto con un'altra nave
 */
int isImpossible(char cell[], char direction, char coords[], int size, char playground[TABLE_MAX][TABLE_MAX])
{
	int error;
	int row;
	int column;
	int len;
	int checkMapBoundaries;
	int checkShipCollisions;

	error = 0;
	len = getLength(cell);
	row = stringToNumber(cell, len);
	column = getIntegerColumn(cell[0]);
	checkMapBoundaries = checkBoundaries(row, column, size, direction);

	if (checkMapBoundaries == 0)
	{
		checkShipCollisions = checkCollisions(playground, coords);
		if (checkShipCollisions == 1)
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
 * Funzione checkBoundaries
 * DESCRIZIONE: Controlla se la posizione della nave non vada oltre i limiti della mappa
 * di gioco, restituendo 1 se va oltre i limiti della mappa, altrimenti restituisce 0
 * se rispetta i limiti della mappa.
 *
 * INPUT
 * row - Riga di partenza della nave - intero - row >= TABLE_MIN AND row <= TABLE_MAX
 * column - Colonna di partenza della nave - intero - column >= TABLE_MIN AND column <= TABLE_MAX
 * size - Dimensioni della nave - intero - Size >= MIN_SHIP_SIZE AND size <= MAX_SHIP_SIZE
 * direction - Direzione della nave - Carattere - V = Verticale; O = Orizzontale
 * TABLE_MAX - Riga/Colonna massima - Numero intero - 16
 * 	
 * OUTPUT
 * error - Valore numerico pari a 1 o 0 che rappresenta l'esito del controllo - intero - 1 = La nave viola i limiti della mappa; 0 = la nave non viola i limiti della mappa
 */
int checkBoundaries(int row, int column, int size, char direction)
{
	int error;
	error = 0;

	if (direction == 'V')
	{
		// la row va da 1 a 16 (input utente) ma gli indici della mappa vanno da 0 a 15 quindi decremento di 1
		// aggiungo size per verificare se la nave va oltre i limiti della mappa
		if (row - 1 + size > TABLE_MAX)
		{
			error = 1;
		}
	}
	else if (direction == 'O')
	{
		// la column va da 1 a 16 (input utente) ma gli indici della mappa vanno da 0 a 15 quindi decremento di 1
		// aggiungo size per verificare se la nave va oltre i limiti della mappa
		if (column - 1 + size > TABLE_MAX)
		{
			error = 1;
		}
	}
	return error;
}

/**
 * Funzione checkCollisions
 * DESCRIZIONE: Verifica se una nave sta entrando in collisione con un'altra nave o se
 * supera i confini della mappa di gioco, restituendo 1 se vengono violati uno dei
 * due vincoli altrimenti, se vengono rispettati entrambi, restituisce 0.
 *
 * INPUT
 * playground - Playground di un giocatore - Array a due dimensioni di caratteri - Dimensione 16x16;
 * Caratteri consentiti:
 * da 'a' a 'o' per le navi
 * '~' per il mare
 * 'x' per nave colpita
 * '*' per nave affondata
 * coords - Range di coordinate di una nave - Stringa - Formato: primaCella_secondaCella
 * TABLE_MIN - Riga/Colonna minima - Numero intero - 1
 * TABLE_MAX - Riga/Colonna massima - Numero intero - 16
 * WATER - Carattere che indica la presenza di acqua nel playground e nell'heatMap - Carattere - '~'
 * 
 * OUTPUT
 * error - Restituisce un valore numerico pari a 1 o 0 che rappresenta l'esito del controllo - intero - 1 = la nave entra in collisione con altre navi; 0 = nessuna collisione
 * 
 * LAVORO
 * firstCell - Prima cella della nave - Stringa - Formato: riga-colonna
 * lastCoord - Ultima cella della nave - Stringa - Formato: riga-colonna
 * pivotRow - Riga di inizio del controllo - Numero intero - pivotRow >= TABLE_MIN AND pivotRow <= TABLE_MAX
 * pivotColumn - Colonna di inizio del controllo - Numero intero - pivotColumn >= TABLE_MIN AND pivotColumn <= TABLE_MAX
 * endRow - Riga di fine del controllo - Numero intero - endRow >= TABLE_MIN AND endRow <= TABLE_MAX
 * endColumn - Colonna di fine del controllo - Numero intero - endColumn >= TABLE_MIN AND endColumn <= TABLE_MAX
 * i - Contatore delle colonne - Numero intero - i > 0
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
	int firstCellLength;
	int lastCoordLength;

	error = 0;
	getFirstCell(coords, firstCell);
	firstCellLength = getLength(firstCell);
	getLastCell(coords, lastCoord);
	lastCoordLength = getLength(lastCoord);

	/**
	 * Il pivot rappresenta la cella da cui iniziare il controllo sulle collisioni di una nave;
	 * pivotColumn e pivotRow sono rispettivamente la colonna e la riga della cella pivot.
	 *
	 * La cella del pivot viene determinata in base alla posizione della cella di partenza della nave, infatti
	 * la cella predisposta al pivot e' quella che si trova in alto a sinistra
	 */

	/*
	 * Sottraggo 1 per passare da colonna a indice nella mappa, dato che gli indici partono da 0.
	 * Sottraggo nuovamente 1 per spostarmi alla colonna precedente.
	 *
	 * Analogo ragionamento per pivotRow
	 */
	pivotColumn = getIntegerColumn(firstCell[0]) - 2;
	pivotRow = stringToNumber(firstCell, firstCellLength) - 2;
	
	// controllo se il pivot esce dal limite minimo della mappa
	if (pivotColumn < TABLE_MIN - 1) 
	{
		pivotColumn = TABLE_MIN - 1; // Mi posiziono alla colonna precedente
	}

	if (pivotRow < TABLE_MIN - 1)
	{
		pivotRow = TABLE_MIN - 1; // Mi posiziono alla riga precedente
	}

	/**
	 * Prendiamo la cella finale della nave
	 */
	endColumn = getIntegerColumn(lastCoord[0]);
	endRow = stringToNumber(lastCoord, lastCoordLength);
	
	if (endColumn > TABLE_MAX - 1)
	{
		endColumn = TABLE_MAX - 1; // Mi posiziono alla colonna precedente
	}

	if (endRow > TABLE_MAX - 1)
	{
		endRow = TABLE_MAX - 1; // Mi posiziono alla riga precedente
	}

	// Per ogni riga dalla pivotRow alla endRow controllo se le colonne da pivotColumn a endColumn contengono una nave o meno
	// Se contengono una nave viene restituito error = 1
	while (pivotRow <= endRow && error == 0)
	{
		i = pivotColumn;
		while (i <= endColumn && error == 0)
		{
			if (playground[pivotRow][i] != WATER)
			{
				if (playground[pivotRow][i] >= 'a' && playground[pivotRow][i] <= 'p')
				{
					error = 1;
				}
			}

			i++;
		}
		pivotRow++;
	}

	return error;
}

/**
 * Funzione getFirstCell
 * DESCRIZIONE: Restituisce la prima cella del range di coordinate di
 * una nave, riportandola all'interno del parametro cell.
 * 
 * INPUT
 * coords -Range di coordinate di una nave - Stringa - Formato: primaCella_ultimaCella
 * COORD_SEPARATOR - Separatore di coordinate - Carattere - '_'
 * 
 * OUTPUT
 * cell - Prima cella della nave - Stringa - Formato: riga-colonna
 * 
 * LAVORO
 * i - Contatore per le posizioni delle stringhe - intero - i > 0
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
 * Funzione getLastCell
 * DESCRIZIONE: Restituisce l'ultima cella del range di coordinate di
 * una nave, riportandola all'interno del parametro cell.
 * 
 * INPUT
 * coords - Range di coordinate di una nave - Stringa - Formato: primaCella_ultimaCella
 * COORD_SEPARATOR - Separatore di coordinate -Carattere - '_'
 * 
 * OUTPUT
 * cell - Ultima cella della nave - Stringa - Formato: riga-colonna
 * 
 * LAVORO
 * i - Contatore per le posizioni delle stringhe - intero - i > 0
 * j - Contatore per le posizioni delle stringhe - intero - j > 0
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

