#include "./MapsController.h"
#include "../converter/converter.c"

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

	passivePlayer = getPassivePlayer(match);
	activePlayer = getActivePlayer(match);

	row--;
	column--;

	getPlayground(passivePlayer, passivePlayground); 
	getHeatMap(activePlayer, activeHeatMap);
	cell = passivePlayground[row][column];

	if (cell >= 'a' && cell <= 'p')
	{
		passivePlayground[row][column] = PLAYGROUND_HIT;
		activeHeatMap[row][column] = HEAT_MAP_HIT;
	}

	else
	{
		passivePlayground[row][column] = MISS;
		activeHeatMap[row][column] = MISS;
	}

	passivePlayer = setPlayground(passivePlayer, passivePlayground);
	activePlayer = setHeatMap(activePlayer, activeHeatMap);

	match = setPassivePlayer(match, passivePlayer);
	match = setActivePlayer(match, activePlayer);

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

	if (checkBoundaries(row, column, size) == 0)
	{
		if (checkCollisions(playground, direction, coords, size) == 1)
		{
			printf("Coordinate non valide: sei in contatto con un altra nave\n");
			error = 1;
		}
	}

	else
	{
		printf("Coordinate non valide: stai violando i confini della mappa\n");
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
 * @return Valore numerico pari a 1 o 0, che rappresenta l'esito del controllo. 
 */
int checkBoundaries(int row, int column, int size)
{
	int error;
	error = 0;

	if ((row + size - 1 > TABLE_MAX) || (column + size - 1 > TABLE_MAX))
	{
		error = 1;
	}

	return error;
}


//FIXME: Risolvere i problemi delle collisioni sulle navi

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
int checkCollisions(char playground[TABLE_MAX][TABLE_MAX], char direction, char coords[], int shipSize)
{
	int error;
	error = 0;

	//FIXME: Fare un calcolo migliore della scelta della cella di scansione nel caso
	// di posizionamento dell nave ai bordi della mappa.

	if (direction == 'V')
	{
		if(checkVerticalCollisions(playground, coords, shipSize) == 1)
		{
			printf("Coordinate non valide: sei in contatto con un altra nave\n");
			error = 1;
		}
	}

	else if (direction == 'O')
	{
		if(checkHorizontalCollisions(playground, coords, shipSize) == 1)
		{
			printf("Coordinate non valide: sei in contatto con un altra nave\n");
			error = 1;
		}
	}

	return error;
}


int checkVerticalCollisions(char playground[TABLE_MAX][TABLE_MAX], char coords[], int shipSize)
{
	int error;
	int startingColumn;
	char firstCell[MAX_COORD_LEN];
	char secondCell[MAX_COORD_LEN];
	int firstRow;
	int secondRow;
	int i;
	int j;
	int k;

	error = 0;
	getFirstCell(coords, firstCell);
	getLastCell(coords, secondCell);
	startingColumn = getIntegerColumn(firstCell[0]) - 1;
	firstRow = stringToNumber(firstCell, getLength(firstCell));
	secondRow = stringToNumber(secondCell, getLength(secondCell));
	
	k = 0;
	i = firstRow - 1;
	j = startingColumn - 1;

	while (k < SEARCH_RADIUS)
	{
		j = startingColumn - 1;

		while (j < startingColumn + shipSize + 1)
		{
			if (playground[j][i] != WATER)
			{
				k = SEARCH_RADIUS;
				j = startingColumn + shipSize;
				error = 1;
			}

			j++;
		}

		i++;
		k++;
	}


	return error;
}



int checkHorizontalCollisions(char playground[TABLE_MAX][TABLE_MAX], char coords[], int shipSize)
{
	int error;
	int startingRow;
	char firstCell[MAX_COORD_LEN];
	char secondCell[MAX_COORD_LEN];
	int firstColumn;
	int secondColumn;
	int i;
	int j;
	int k;

	error = 0;
	getFirstCell(coords, firstCell);
	getLastCell(coords, secondCell);

	startingRow = stringToNumber(firstCell, getLength(firstCell)) - 1;
	firstColumn = getIntegerColumn(firstCell[0]);
	secondColumn = getIntegerColumn(secondCell[0]);

	k = SEARCH_RADIUS;
	i = firstColumn - 1; 
	j = startingRow;

	while (k > 0)
	{
		j = startingRow;

		while (j <= startingRow + shipSize + 1)
		{
			if (playground[i][j] != WATER)
			{
				k = -1;
				j = startingRow + shipSize + 1;
				error = 1;
			}

			j++;
		}

		k--;
		i--;
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

	while (coords[i] != COORD_SEPARETOR)
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

	while (coords[i] != COORD_SEPARETOR)
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