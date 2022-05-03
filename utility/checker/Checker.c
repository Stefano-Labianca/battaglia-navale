#include <stdio.h>
#include <stdlib.h>

#include "./Checker.h"



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
