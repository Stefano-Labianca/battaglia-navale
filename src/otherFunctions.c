#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "./Grid.c"
// #include "./Ship.c"
// #include "./Player.c"


//TODO: Migliorare le funzioni
//TODO: Suddividere le funzioni in file appositi in base al loro scopo -> Consulta file "divisore.txt"


#define LOWER_TO_UPPER 32
#define START_UPPERCASE_ASCII 65

enum COORDS_CONSTANTS {
	SEPARATOR = '-',  
	COORD_SEPARETOR = '_',
	MAX_COORD_LEN = 7, 
	MAX_ROW_LEN = 3, 
	MAX_DIM_COORDS = 11
};

enum TABLE_RANGE{TABLE_MIN = 1, TABLE_MAX = 16};
enum ASCII_DIGIT_RANGE{MIN_DIGIT = 48, MAX_DIGIT = 57};

char getColumn();
char toUpperCase(char letter);
char getDirection();
char getCharColumn(int column);

int stringToNumber(char str[], int len);
int isValidRow(int row);
int getLength(char str[]);
int getIntegerColumn(char column);
int calculateBoundaries(int start, int end);

void getRow(char row[]);
void numberToString(int number, char buffer[]);
void buildShipCoordinate(char column, char row[], char coord[]);
void buildNextCoord(char direction, char startingCoord[], int shipSize, char nextCoord[]);
void buildVerticalCoord(char startingCoord[], int shipSize, char nextCoord[]);
void buildHorizontalCoord(char startingCoord[], int shipSize, char nextCoord[]);
void concatCoordinates(char first[], char second[], char dest[]); //TODO: Da fare ancora



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
			printf("\n\nErrore\n\n"); //TODO: Da gestire meglio la stampa dell'errore
		}

		fflush(stdin);
	} while (error == 1);

	return col;
}


/**
 * @brief Trasforma una lettera minuscola in una lettera maiuscola. Se letter è una lettera
 * maiuscola, allora viene restituita senza modificarla, se invece letter è minuscola
 * viene trasformata in una lettera maiuscola.
 * 
 * @param letter Lettera da trasformare.
 * @return Lettera trasformata. 
 */
char toUpperCase(char letter)
{
	if (letter >= 'a' && letter <= 'z')
	{
		letter -= LOWER_TO_UPPER;
	}

	return letter;
} 


/**
 * @brief Restituisce, sottoforma di stringa, il valore della riga inserito dall'utente. 
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
 * @brief Converte un numero naturale in una stringa, conservando il valore convertito
 * nel parametro buffer.
 * 
 * @param number Numero da convertire.
 * @param buffer Array che contiene il valore di number convertito in una stringa.
 */
void numberToString(int number, char buffer[])
{
	int i = 0;
	int last = 1;
	int digit = 0;

	if (number > 9)
	{
		i = 1;
		last = 2;
	}

	while (number > 0)
	{
		buffer[i] = (number % 10) + MIN_DIGIT; // Converto l'ultima cifra del numero in un carattere
		number = (int) number / 10; // Prendo le cifre successive
		i--;
	}
	
	buffer[last] = '\0';

	return;
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
 * @brief Converte una stringa in un numero naturale, andando ad escludere quei caratteri che non fanno parte
 * del range ASCII delle cifre decimali. Se li viene passata una stringa non valida, viene restituito il 
 * valore 0, altrimenti viene restituito il valore convertito.
 * 
 * @param str Stringa da convertire in un numero naturale.
 * @param len Lunghezza della stringa da convertire.
 * @return Numero convertito.
 */
int stringToNumber(char str[], int len)
{
	int number = 0;
	int i = 0;

	while (i < len)
	{
		if (str[i] >= MIN_DIGIT && str[i] <= MAX_DIGIT)
		{
			number = (str[i] - MIN_DIGIT) + number * 10;
		}

		i++;
	}

	return number;
}	


/**
 * @brief Ricava la lunghezza di una stringa.
 * 
 * @param str Stringa da calcolare la lunghezza.
 * @return Lunghezza di una stringa.
 */
int getLength(char str[])
{
	int i = 0;
	
	while (str[i] != '\0')
	{
		i++;
	}
	
	return i;
}


/**
 * @brief Costrutisce e restituisce la successiva coordinata, prendendo in considerazione
 * la coordinata di partenza, le dimensioni della nave e la sua direzione.
 * La coordinata costruita verrà salvata all'interno di nextCoord.
 * 
 * @param direction Direzione della nave e può avere un valore pari a 'V' o a 'O'.
 * @param startingCoord Coordinate di partenza della nave.
 * @param shipSize Dimensioni della nave.
 * @param nextCoord Coordianta successiva calcolata.
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
 * @brief Contatena e restituisce il valore di first e second, all'interno 
 * dell'array dest. Il contenuto delle due coordinate viene suddiviso 
 * dal simbolo "_".
 * 
 * Esempio: "A-1_A-5".
 * 
 * @param first Coordinata che contiene la cella di partenza della nave.
 * @param second Coordinata che contiene la cella di arrivo della nave.
 * @param dest Contiene il contenuto di first e second.
 */
void concatCoordinates(char first[], char second[], char dest[])
{
	int i = 0;
	int j = 0;

	while (first[i] != '\0') 
	{
		dest[i] = first[i];
		i++;
	}


	dest[i] = COORD_SEPARETOR;

	j = i + 1;
	i = 0;

	while (second[i] != '\0') 
	{
		dest[j] = second[i];
		i++;
		j++;
	}

	dest[j] = '\0';

	return;
}


