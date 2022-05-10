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

	/*
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