#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Ship.h"


char readLabel(Ship ship)
{
	char label;
	label = ship.label;

	return label;
}


int readSize(Ship ship)
{
	int size;
	size = ship.size;

	return size;
}


int readLifePoints(Ship ship)
{
	int lifePoints;
	lifePoints = ship.lifePoints;

	return lifePoints;
}


void readCoords(Ship ship, char coords[])
{
	strcpy(coords, ship.coords);
	return;
}


Ship writeLabel(Ship ship, char label)
{
	ship.label = label;
	return ship;
}


Ship writeSize(Ship ship, int size)
{
	ship.size = size;
	return ship;
}


Ship writeLifePoints(Ship ship, int lifePoints)
{
	ship.lifePoints = lifePoints;
	return ship;
}


Ship writeCoords(Ship ship, char coords[])
{
	strcpy(ship.coords, coords);
	return ship;
}



/**
 * @brief Restituisce il carattere della colonna inserito dall'utente.
 * 
 * @return Valore della colonna preso in input. 
 */
char getColumn() 
{
	int error = 0;
	char col = ' ';

	do 
	{
		error = 0;
		printf("Inserisci la colonna di partenza della nave: ");
		col = getchar();
		col = toUpperCase(col);

		if (col < 'A' || col > 'P')
		{
			error = 1;
			printf("\n\nErrore: devi inserire una lettera compresa tra A e P\n\n"); //TODO: Da gestire meglio la stampa dell'errore
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
	int numericRow = 0;

	do 
	{
		printf("Inserisci la riga di partenza della nave: ");
		scanf("%d", &numericRow);
		fflush(stdin); //FIXME: Mettere un controllo migliore nel caso si metta in input un carattere e non un intero
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
	int isValid = 1;
	
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
	int i = 0;
	int j = 2;
	
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
 * @brief Restituisce l'orientamento della nave. Il valore restituito
 * può essere pari a "V", che definisce l'orientamento verticale, oppure pari 
 * a "O" che definisce l'orientamento orizzontale.
 * 
 * @return Carattere che definisce l'orientamento della nave. 
 */
char getDirection() 
{
	int error = 0;
	char direction = ' ';

	do 
	{
		error = 0;
		printf("Inserire V per inserire la nave in verticale, oppure O per inserire la nave in orizzontale: ");
		
		direction = getchar();
		direction = toUpperCase(direction);

		if (direction != 'O' && direction != 'V')
		{
			error = 1;
			printf("\n\nErrore\n\n"); //TODO: Da gestire meglio la stampa dell'errore
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
	int numericRow = 0;
	char nextRow[MAX_ROW_LEN];
	int i = 2;
	
	shipSize--;
	numericRow = stringToNumber(startingCoord, getLength(startingCoord));
	numericRow = calculateBoundaries(numericRow, shipSize);
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
	int numericColumn = 0;
	char startingColumn = ' ';
	char nextColumn = ' ';
	int i = 2;

	startingColumn = startingCoord[0];
	numericColumn = getIntegerColumn(startingColumn);
	shipSize--;

	numericColumn = calculateBoundaries(numericColumn, shipSize);
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


// ? Deciderne l'implementazione
/**
 * @brief Verifica se due punti rispettano i limiti imposti dalle dimensioni 
 * della tabella di gioco, calcolando e restituendo il punto di arrivo corretto. 
 * 
 * @param start Punto di partenza.
 * @param end Punto di arrivo ipotetico.
 * @return Punto di arrivo corretto.
 */
int calculateBoundaries(int start, int end)
{
	if (start + end > TABLE_MAX)
	{
		start -= end;
	}

	else if (start - end < TABLE_MIN)
	{
		start += end;
	}

	else if (start + end >= TABLE_MIN && start + end <= TABLE_MAX)
	{
		start += end;
	}

	return start;
}


/**
 * @brief Converte un carattere, associato ad una colonna, e restituisce
 * la posizione della colonna all'interno della tabella.
 * 
 * @param column Carattere da convertire.
 * @return Posizione della colonna all'interno della tabella.
 */
int getIntegerColumn(char column)
{
	int numericColumn = 0;
	numericColumn = column - START_UPPERCASE_ASCII + 1;

	return numericColumn;
}


/**
 * @brief Converte la posizione di una colonna, e restituisce
 * il carattere associato ad essa nella tabella di gioco.
 * 
 * @param column Valore numerico da convertire.
 * @return Posizione della colonna convertita nel suo carattere associato.
 */
char getCharColumn(int column)
{
	char charColumn = ' ';
	charColumn = column + START_UPPERCASE_ASCII - 1;

	return charColumn;
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
	int i = 0;
	int j = 0;

	while (startCell[i] != '\0') 
	{
		dest[i] = startCell[i];
		i++;
	}

	dest[i] = COORD_SEPARETOR;

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

