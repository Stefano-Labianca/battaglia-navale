#include "./MapsController.h"


/**
 * @brief Inizializza e restituisce il playgroud dei giocatori.
 * 
 * @param playground Playground da inizializzare.
 */
void createPlayground(char playground[TABLE_MAX][TABLE_MAX])
{
    int i;
	int j;

	i = 0;
	
	while (i < TABLE_MAX) 
	{
		j = 0;
		while (j < TABLE_MAX) 
		{
			playground[i][j] = WATER; //FIXME: Richiamare la funzione di accesso di Player.c
			j++;
		}
		
		i++;
	}

	return;
}


/**
 * @brief Inizializza e restituisce, all'interno del paramentro heatMap, l'heat map 
 * dei giocatori.
 * 
 * @param heatMap Heat map da inizializzare. 
 */
void createHeatMap(char heatMap[TABLE_MAX][TABLE_MAX])
{
	int i;
	int j;

	i = 0;
	
	while (i < TABLE_MAX) 
	{
		j = 0;
		while (j < TABLE_MAX) 
		{
			heatMap[i][j] = UNKNOWN; //FIXME: Richiamare la funzione di accesso di Player.c
			j++;
		}
		i++;
	}

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
	
    printf("   ");
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
		if (i < 10) 
        {
			printf(" ");
		}

		j = 0;
		printf(" %d ", i);

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
