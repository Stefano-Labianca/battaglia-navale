#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "./Grid.c"
// #include "./Ship.c"
// #include "./Player.c"


//TODO: Migliorare le funzioni
//TODO: Suddividere le funzioni in file appositi in base al loro scopo -> Consulta file "divisore.txt"



#define LOWER_TO_UPPER 32
#define SEPARATOR '-'
#define MAX_COORD_LEN 7


enum ROWS_RANGE{ROW_MIN = 1, ROW_MAX = 16};

char getColumn();
char toUpperCase(char letter);
int isValidRow(int row);

void getRow(char row[]);
void numerToString(int number, char buffer[]);
void buildShipCoordinate(char column, char row[], char coord[]);


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

	numerToString(numericRow, row);

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
	
	if (row < ROW_MIN || row > ROW_MAX) 
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
void numerToString(int number, char buffer[])
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
		buffer[i] = (number % 10) + '0'; // Converto l'ultima cifra del numero in un carattere
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


//FIXME: Eliminare la gestione della direzione delle coordinate
//TODO: Aggiungere delle funzio che ricavino l'orientamento della nave


// Grid setVertical(Grid playground, Ship ship) {
// 	char cell[6];
// 	readCoords(ship, cell);
// 	int size;
// 	int row;
// 	int col;
// 	int i;
	
// 	char label;
// 	size = readSize(ship);
// 	row = cell[2] - 48;
// 	col = cell[0] - 64;
// 	i = 0;
// 	label = readLabel(ship);
// 	if (cell[3] >= '0' && cell[3] <= '9') {
// 		row *= 10;
// 		row += cell[3] - 48;
// 	}
// 	while (i < size) {
// 		playground = writeValue(playground, row, col, label);
// 		row++;
// 		i++;
// 	}
// 	// CONCATENA L ULTIMA CELLA A coordS
// 	return playground;
// }

// Grid setOrizzontal(Grid playground, Ship ship) {
// 	char cell[6];
// 	readCoords(ship, cell);
// 	int size;
// 	int row;
// 	int col;
// 	int i;
// 	;
// 	char label;
// 	size = readSize(ship);
// 	row = cell[2] - 48;
// 	col = cell[0] - 64;
// 	if (cell[3] >= '0' && cell[3] <= '9') {
// 		row *= 10;
// 		row += cell[3] - 48;
// 	}
// 	while (i < size) {
// 		playground = writeValue(playground, row, col, label);
// 		col++;
// 		i++;
// 	}
// 	// CONCATENA L ULTIMA CELLA A coordS
// 	return playground;
// }

// Ship createShip(Ship ship, int size, int number) {
// 	char cell[5];
// 	char direction;
// 	ship = writeSize(ship, size);
// 	ship = writeLifePoints(ship, size);
// 	ship = writeLabel(ship, (number + 96));
// 	ship = writeSunk(ship, 0);
// 	getCell(cell);
// 	direction = getDirection();
// 	ship = writeDirection(ship, direction);
// 	ship = writeCoords(ship, cell);
// 	return ship;
// }

// Grid fillPlayground(Grid playground, Player p) {
// 	int index;
// 	int size; //dimensione della nave
// 	Ship ship;
// 	index = 1;
// 	size = 5;
// 	//CREAZIONE DI UNA NAVE
// 	printf("NAVE %d DI DIMENSIONE %d \n", index, size);
// 	ship = createShip(ship, size, index);
// 	p = writeShip(p, index, ship);
// 	index++;
// 	size--;
// 	while (index <= 3) {
// 		printf("NAVE %d DI DIMENSIONE %d \n", index, size);
// 		fflush(stdin);
// 		ship = createShip(ship, size, index);
// 		p = writeShip(p, index, ship);
// 		index++;
// 	}
// 	size--;
// 	while (index <= 6) {
// 		printf("NAVE %d DI DIMENSIONE %d \n", index, size);
// 		ship = createShip(ship, size, index);
// 		p = writeShip(p, index, ship);
// 		index++;
// 	}
// 	size--;
// 	while (index <= 10) {
// 		printf("NAVE %d DI DIMENSIONE %d \n", index, size);
// 		ship = createShip(ship, size, index);
// 		p = writeShip(p, index, ship);
// 		index++;
// 	}
// 	size--;
// 	while (index <= 15) {
// 		printf("NAVE %d DI DIMENSIONE %d \n", index, size);
// 		ship = createShip(ship, size, index);
// 		p = writeShip(p, index, ship);
// 		index++;
// 	}

// 	index = 1;
// 	while (index <= 15) {
// 		ship = readShip(p, index);

// 		if (readDirection(ship) == 'V') {
// 			playground = setVertical(playground, ship);
// 		} else {
// 			playground = setOrizzontal(playground, ship);
// 		}
// 		index++;
// 	}	
// 	printf("\nMAPPA FIN ORA\n");
// 	printGrid(playground);
// 	return playground;
// }

