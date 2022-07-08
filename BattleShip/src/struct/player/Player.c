#include <stdio.h>
#include <stdlib.h>

#include "./Player.h"

/**
 * Funzione createPlayer
 * 
 * DESCRIZIONE: Crea e restituisce un giocatore con un identificotore pari a id
 * 
 * INPUT
 * player - Player da creare - player - /
 * id - Identificatore da assegnare a player - numero intero - 1 = Player 1,  2 = Player 2
 * MAX_LONG_SHOT - Numero massimo di longShot a disposizione di un player - Numero intero - 3
 * MAX_RADAR - Numero massimo di radar a disposizione di un player - Numero intero - 3
 * MAX_AIR_STRIKE - Numero massimo di airStrike a disposizione di un player - Numero intero - 1
 * MAX_SHIP_AMOUNT - Numero massimo di navi a in un playground - Numero intero - 15
 * 
 * OUTPUT
 * player - Giocatore inizializzato - player - /
 * 
 * LAVORO
 * playground - PLayground del giocatore - Array di caratteri a due dimensioni - 16x16
 * Simboli disponibili:
 * - Da 'a' a 'o' per le navi
 * - '~' mare
 * - 'x' nave colpita
 * - '*' Nave colpita e affondata
 
 * heatMap - Heatmap del giocatore - Array di caratteri a due dimensioni - 16x16
 * Simboli disponibili:
 * - Da 'a' a 'o' per le navi
 * - '~' mare
 * - '?' per ignoto
 * - '!' per nave colpita
 * - '#' nave scansionata
 * - '*' Nave colpita e affondata
 */
Player createPlayer(Player player, int id)
{
	char playground[TABLE_MAX][TABLE_MAX];
	char heatMap[TABLE_MAX][TABLE_MAX];

	createPlayground(playground);
	createHeatMap(heatMap);
	player = setId(player, id);
	player = setPlayground(player, playground);
	player = setHeatMap(player, heatMap);
	player = setLongshots(player, MAX_LONG_SHOT);
	player = setRadar(player, MAX_RADAR);
	player = setAirstrike(player, MAX_AIR_STRIKE);
	player = setAvailableShips(player, MAX_SHIP_AMOUNT);
	return player;
}


/**
 * Funzione getID
 * 
 * DESCRIZIONE: Restituisce l'ID di un giocatore
 * 
 * INPUT
 * Player - Giocatore di cui leggere l'id - player - /
 * 
 * OUTPUT
 * id - Identificatore del player - Numero intero - id = 1 -> Player numero 1, id = 2 -> Player numero 2
 * 
 * LAVORO
 * 
 */
int getId(Player player)
{
	int id;
	id = player.id;
	
	return id;
}

/**
 * Funzione getLongShot
 * DESCRIZIONE: Restituisce il numero di colpi a lungo raggio di un giocatore
 * 
 * INPUT
 * player - Giocatore di cui leggere i colpi a lungo raggio disponibili - player - /
 * 
 * OUTPUT
 * longShot - Colpi a lungo raggio disponibili - Numero intero - longShot >= 0 AND longShot <= MAX_LONG_SHOT
 * 
 * LAVORO
 * 
 */
int getLongShots(Player player)
{
	int longShots;
	longShots = player.longShots;

	return longShots;
}


/**
 * Funzione getRadar
 * DESCRIZIONE: Restituisce il numero di utilizzi per il radar di un giocatore
 * 
 * INPUT
 * player - Giocatore di cui leggere i radar disponibili - player - /
 * 
 * OUTPUT
 * radar - Radar del player ancora disponibili - Numero intero - radar >= 0 AND radar <= MAX_RADAR
 * 
 * LAVORO
 * 
 */
int getRadar(Player player)
{
	int radar;
	radar = player.radar;

	return radar;
}


/**
 * Funzione getAirstrike
 * DESCRIZIONE: Restituisce il numero di utilizzi per il bombardamento aereo di un giocatore
 * 
 * INPUT
 * player - Giocatore di cui leggere il numero di utilizzi per il bombardamento aereo disponibili - player - /
 * 
 * OUTPUT
 * airStrike - Bombardamenti aerei ancora disponibili - Numero intero - airStrike >= 0 AND airStrike <= MAX_AIR_STRIKE
 * 
 * LAVORO
 * 
 */
int getAirstrike(Player player)
{
	int airstrike;
	airstrike = player.airstrike;

	return airstrike;
}


/**
 * Funzione getAvailableShips
 * DESCRIZIONE: Restituisce il numero di navi disponibili per un giocatore
 * 
 * INPUT
 * player - Giocatore di cui leggere il numero di navi disponibili - player - /
 * 
 * OUTPUT
 * availableShips - Numero di navi del plater ancora disponibili - Numero intero - availableShips >= 0 AND availableShips <= MAX_SHIP_AMOUNT
 * 
 * LAVORO
 * 
 */
int getAvailableShips(Player player)
{
	int availableShips;
	availableShips = player.availableShips;

	return availableShips;
}


/**
 * Funzione getPlayGround
 *
 * DESCRIZIONE: Restituisce il playground di un giocatore
 * 
 * INPUT
 * Player - Giocatore di cui leggere il playground - player - /
 * TABLE_MAX - Riga/Colonna massima - Numero intero - 16
 * 
 * OUTPUT
 * playground - Playground del player - Array bidimensionale di caratteri - Dimensioni 16x16
 * Caratteri consentiti:
 * - Da 'a' a 'o' per le navi
 * - '~' mare
 * - 'x' nave colpita
 * - '*' Nave colpita e affondata
 * LAVORO
 * i - Contatore della prima dimensione (righe) del playground - Numero intero - i > 0
 * j - Contatore della seconda dimensione (colonne) del playground - Numero intero - j > 0
 */
void getPlayground(Player player, char playground[TABLE_MAX][TABLE_MAX]) 
{
	int i;
	int j;

	i = 0;
	
	while (i < TABLE_MAX)
	{
		j = 0;
		while (j < TABLE_MAX)
		{
			playground[i][j] = player.playground[i][j];
			j++;
		}
		
		i++;
	}

	return;
}


/**
 * Funzione getHeatMap
 *
 * DESCRIZIONE: Restituisce la heatmap di un giocatore
 * 
 * INPUT
 * Player - Giocatore di cui leggere la heatmap - player - /
 * TABLE_MAX - Riga/Colonna massima - Numero intero - 16
 * 
 * OUTPUT
 * heatmap - Heatmap del player - Array bidimensionale di caratteri - Dimensioni 16x16
 * Caratteri consentiti:
 * - Da 'a' a 'o' per le navi
 * - '~' mare
 * - '?' per ignoto
 * - '!' per nave colpita
 * - '#' nave scansionata
 * - '*' Nave colpita e affondata
 * 
 * LAVORO
 * i - Contantore della prima dimensione (righe) del playground - Numero intero - i > 0
 * j - Contantore della seconda dimensione (colonne) del playground - Numero intero - j > 0
 */
void getHeatMap(Player player, char heatMap[TABLE_MAX][TABLE_MAX]) 
{
	int i;
	int j;
	
	i = 0;
	
	while (i < TABLE_MAX)
	{
		j = 0;
		while (j < TABLE_MAX)
		{
			heatMap[i][j] = player.heatMap[i][j];
			j++;
		}
		i++;
	}
	
	return;
}


/**
 * Funzione getShip
 *
 * DESCRIZIONE: Restituisce una nave in una certa posizione
 *
 * INPUT
 * player - Giocatore a cui leggere la nave in posizione index - player - /
 * index - Posizione che indica quale nave leggere - numero intero - index >= 1 AND index <= MAX_SHIP_AMOUNT
 *
 * OUTPUT
 * ship - Nave in posizione index del player - ship - /
 *
 * LAVORO
 * 
 */
Ship getShip(Player player, int index)
{
	Ship ship;
	ship = player.ships[index - 1];
	// la variabile index va da 1 a 16
	// le posizioni del vettore invece vanno da 0 a 15, quindi sottraggo 1

	return ship;
}


/**
 * Funzione setID
 *
 * DESCRIZIONE: Imposta l'id ad un giocatore
 *
 * INPUT
 * player - Giocatore a cui aggiornare l'id - player - /
 * id - Nuovo identificatrore del player - numero intero - id = 1 -> Player numero 1, id = 2 -> PLayer numero 2
 *
 * OUTPUT
 * Player - Giocatore con id aggiornato - player - /
 *
 * LAVORO
 * 
 */
Player setId(Player player, int id)
{
	player.id = id;
	return player;
}


/**
 * Funzione setLongshots
 *
 * DESCRIZIONE: Imposta il numero di colpi a lungo raggio di un giocatore
 *
 * INPUT
 * player - Giocatore a cui aggiornare i longShot disponibili - player - /
 * longShotsAmount - Nuovo numero di longshot disponibili del player - numero intero - longShoot >= 0 AND longShots <= MAX_LONG_SHOT
 *
 * OUTPUT
 * Player - giocatore con longShots ancora disponibili aggiornati - player - /
 *
 * LAVORO
 * 
 */
Player setLongshots(Player player, int longShots)
{
	player.longShots = longShots;
	return player;
}


/**
 * Funzione setRadar
 *
 * DESCRIZIONE: Imposta il numero di radar di un giocatore
 *
 * INPUT
 * player - Giocatore a cui aggiornare i radar disponibili - player - /
 * radarAmount - Nuovo numero di radar ancora disponibili - numero intero - radar >= 0 AND radar <= MAX_RADAR
 *
 * OUTPUT
 * Player - giocatore con radar ancora disponibili aggiornati - player - /
 *
 * LAVORO
 * 
 */
Player setRadar(Player player, int radar)
{
	player.radar = radar;
	return player;
}


/**
 * Funzione setAirstrike
 *
 * DESCRIZIONE: Imposta il numero di airstrike di un giocatore
 *
 * INPUT
 * player - Giocatore a cui aggiornare gli airstrike ancora disponibili - player - /
 * airstrikeAmount - Nuovo numero di airstrike del player ancora disponibili - numero intero - airstrikeAmount >= 0 AND airstrikeAmount <= MAX_AIR_STRIKE
 *
 * OUTPUT
 * Player - giocatore con gli airstrike ancora disponibili aggiornati - player - /
 *
 * LAVORO
 * 
 */
Player setAirstrike(Player player, int airstrike)
{
	player.airstrike = airstrike;
	return player;
}


/**
 * Funzione setAvailableShips
 *
 * DESCRIZIONE: Imposta il numero di navi disponibili per un giocatore
 *
 * INPUT
 * player - Giocatore a cui aggiornare il numero di navi ancora disponibili - player - /
 * availableShips - Nuovo numero di navi ancora disponibili - numero intero - availableShips >= 0 AND availableShips <= MAX_SHIP_AMOUNT
 *
 * OUTPUT
 * Player - giocatore con il numero di navi ancora disponibili aggiornati - player - /
 *
 * LAVORO
 * 
 */
Player setAvailableShips(Player player, int availableShips)
{
	player.availableShips = availableShips;
	return player;
}


/**
 * Funzione setShip
 *
 * DESCRIZIONE: Imposta il numero di navi disponibili per un giocatore
 *
 * INPUT
 * player - Giocatore a cui aggiornare la nave in posizione index - player - /
 * index - Posizione che indica quale nave leggere  - numero intero - index >= 1 AND index <= MAX_SHIP_AMOUNT
 * ship - Nave in posizione index del player - ship - /
 *
 * OUTPUT
 * Player - giocatore con la nave in posizione index aggiornata - player - /
 *
 * LAVORO
 * 
 */
Player setShip(Player player, int index, Ship ship)
{
	player.ships[index - 1] = ship;
	// la variabile index va da 1 a 16
	// le posizioni del vettore invece vanno da 0 a 15, quindi sottraggo 1

	return player;
}


/**
 * Funzione setPlayGround
 *
 * DESCRIZIONE: Inizializza il playground del giocatore
 * 
 * INPUT
 * Player - Giocatore di cui aggiornare il playground - player - /
 * playground - Nuovo playground del player - Array bidimensionale di caratteri - Dimensione 16x16 
 * Caratteri consentiti: 
 * - Da 'a' a 'o' per le navi 
 * - '~' per il mare
 * - 'x' nave colpita
 * - '*' nave affondata
 * TABLE_MAX - Riga/Colonna massima - Numero intero - 16
 * 
 * OUTPUT
 * Player - Giocatore con playground aggiornato - player - /
 * 
 * LAVORO
 * i - Contatore della prima dimensione (righe) del playground - Numero intero - i > 0
 * j - Contatore della seconda dimensione (colonne) del playground - Numero intero - j > 0
 */
Player setPlayground(Player player, char playground[TABLE_MAX][TABLE_MAX])
{
	int i;
	int j;
	
	i = 0;
	while (i < TABLE_MAX)
	{
		j = 0;
		while (j < TABLE_MAX)
		{
			player.playground[i][j] = playground[i][j];
			j++;
		}
		i++;
	}

	return player;
}


/**
 * Funzione setHeatMap
 *
 * DESCRIZIONE: Inizializza la heatmap del giocatore
 * 
 * INPUT
 * Player - Giocatore di cui aggiornare la heatMap - player - /
 * heatMap - Nuova heatMap del player - Array bidimensionale di caratteri - Dimensione 16x16 
 * Caratteri consentiti: 
 * - '~' per il mare 
 * - '?' per ignoto
 * - '!' per nave colpita 
 * - '*' nave colpita e affondata
 * - '#' nave scansionata
 * TABLE_MAX - Riga/Colonna massima - Numero intero - 16
 * 
 * OUTPUT
 * Player - Giocatore con heatMap aggiornata - player - /
 * 
 * LAVORO
 * i - Contatore della prima dimensione (righe) del playground - Numero intero - i > 0
 * j - Contatore della seconda dimensione (colonne) del playground - Numero intero - j > 0
 */
Player setHeatMap(Player player, char heatMap[TABLE_MAX][TABLE_MAX]) {
	int i;
	int j;

	i = 0;
	
	while (i < TABLE_MAX)
	{
		j = 0;
		while (j < TABLE_MAX)
		{
			player.heatMap[i][j] = heatMap[i][j];
			j++;
		}
		i++;
	}
	
	return player;
}


/**
 * Funzione createPlayground
 * DESCRIZIONE: Inizializza il playground di un giocatore 
 *
 * INPUT
 * TABLE_MAX - Riga/Colonna massima - numero intero - 16
 * WATER - Carattere che indica la presenza di acqua nel playground e nella heatMap - Carattere - '~'
 *
 * OUTPUT
 * playground - playground del giocatore - Array di caratteri a due dimensioni - Dimensioni 16x16
 * Caratteri consentiti:
 * - Da 'a' a 'o' per le navi
 * - '~' mare
 * - 'x' nave colpita
 * - '*' Nave colpita e affondata
 *
 * LAVORO
 * i - Indice di scorrimento per le righe - Numero intero - i > 0
 * j - Indice di scorrimento per le colonne - Numero intero - j > 0
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
			playground[i][j] = WATER;
			j++;
		}
		
		i++;
	}

	return;
}


/**
 * Funzione createHeatMap
 * DESCRIZIONE: Inizializza la heatmap di un giocatore 
 *
 * INPUT
 * TABLE_MAX - Riga/Colonna massima - Numero intero - 16
 * WATER - Carattere che indica la presenza di acqua nel playground e nell'heatMap - Carattere - '~'
 *
 * OUTPUT
 * heatmap - heatmap del giocatore - Array di caratteri a due dimensioni - Dimensione 16x16
 * Simboli disponibili:
 *  - '~' per il mare 
 *  - '?' per ignoto
 *  - '!' per nave colpita 
 *  - '*' nave colpita e affondata
 *  - '#' nave scansionata
 *
 * LAVORO
 * i - Indice di scorrimento per le righe - Numero intero - i > 0
 * j - Indice di scorrimento per le colonne - Numero intero - j > 0
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
			heatMap[i][j] = UNKNOWN;
			j++;
		}
		i++;
	}

	return;
}



/**
 * Funzione showMap
 * DESCRIZIONE: Mostra il contenuto del playground o dell'heatmap di un giocatore
 *
 * INPUT
 * map - Mappa da stampare a schermo - Array di caratteri bidimensionale - /
 * TABLE_MAX - Riga/Colonna massima - Numero intero - 16
 * START_UPPERCASE_ASCII - Prima lettera dell'alfabeto maiuscola in ASCII - Numero intero - 65
 *
 * OUTPUT
 *
 * LAVORO
 * i - Indice di scorrimento per le righe - Numero intero - i > 0
 * j - Indice di scorrimento per le colonne - Numero intero - j > 0
 * startColumnSymbol - Simbolo della colonna - Carattere - Compreso tra 'A' a 'P'
 */
void showMap(char map[TABLE_MAX][TABLE_MAX])
{
	int i;
	int j;
	char startColumnSymbol;

	startColumnSymbol = START_UPPERCASE_ASCII;
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
			printf(" %c ", map[i][j]);
			j++;
		}

		printf("\n");
		i++;
	}

    return;
}
