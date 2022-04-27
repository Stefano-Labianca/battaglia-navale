#include <stdio.h>
#include <stdlib.h>

#include "./Player.h"

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
	player = setAvailableShips(player, SHIP_NUMB);
	
	getPlayground(player, playground);
	
	return player;
}


/**
 * @brief Restituisce l'indetificatore del giocatore.
 * 
 * @param player Giocatore da cui ricavare l'identificatore
 * @return Identificatore del giocatore 
 */
int getId(Player player)
{
	int id;
	id = player.id;
	
	return id;
}


/**
 * @brief Restituisce il numero di colpi a lungo raggio 
 * disponibili al giocatore.
 * 
 * @param player Giocatore da cui ricavare il numero di colpi disponibili
 * @return Numero di colpi a lungo raggio disponibili
 */
int getLongShots(Player player)
{
	int longShots;
	longShots = player.longShots;

	return longShots;
}


/**
 * @brief Restituisce il numero di volte in cui può usare
 * usare il radar
 * 
 * @param player Giocatore da cui ricavare la disponibilità di uso del radar
 * @return Numero di volte in cui può usare il radar
 */
int getRadar(Player player)
{
	int radar;
	radar = player.radar;

	return radar;
}


/**
 * @brief Restituisce il numero di volte in cui è possibile avviare 
 * il bombardamento aereo.
 * 
 * @param player Giocatore da cui ricavare il numero di bombardamenti aerei
 * @return Numero di bombardamenti aerei disponibili.
 */
int getAirstrike(Player player)
{
	int airstrike;
	airstrike = player.aistrike;

	return airstrike;
}


/**
 * @brief Restituisce il numero attive di un giocatore 
 * 
 * @param player Giocatore da cui ricavare il numero di navi attive.
 * @return Numero di navi attive.
 */
int getAvailableShips(Player player)
{
	int availableShips;
	availableShips = player.availableShips;

	return availableShips;
}


/**
 * @brief Restituisce il valore contenuto nel campo playground, del dato strutturato Player, e
 * lo salva all'intero del parametro playground.
 * 
 * @param player Giocatore da cui estrarre il contenuto della sua mappa di gioco
 * @param playground Mappa di gioco di un giocatore specifico.
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
 * @brief Restituisce il valore contenuto nel campo heatMap, del dato strutturato Player, e
 * lo salva all'intero del parametro heatMap.
 * 
 * @param player Giocatore da cui estrarre il contenuto della sua mappa di gioco
 * @param heatMap heat map di un giocatore specifico.
 */
void getHeatMap(Player player, char heatMap[TABLE_MAX][TABLE_MAX]) 
{
	int i;
	int j;
	
	i = 0;
	
	while (i < TABLE_MAX)
	{
		j=0;
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
 * @brief Restistuisce una nave del giocatore.
 * 
 * @param player Giocatore da cui prendere una nave
 * @param index Indice della nave.
 * @return Nave scelta.
 */
Ship getShip(Player player, int index)
{
	Ship ship;
	ship = player.ships[index - 1];

	return ship;
}


/**
 * @brief Imposta l'indentificatore di un giocatore, restituendo 
 * il dato aggiornato.
 * 
 * @param player Giocatore a cui aggiornare l'identificatore.
 * @param id Identificatore del giocatore.
 * @return Giocatore aggiornato. 
 */
Player setId(Player player, int id)
{
	player.id = id;
	return player;
}


/**
 * @brief Imposta il numero di colpi a lungo raggio di 
 * un giocatore, restituendo il dato aggiornato
 * 
 * @param player Giocatore a cui aggiornare il numero di colpi a lungoo raggio
 * @param longShotsAmount Numero di colpi a lungo raggio da impostare.
 * @return Giocatore aggiornato
 */
Player setLongshots(Player player, int longShotsAmount)
{
	player.longShots = longShotsAmount;
	return player;
}


/**
 * @brief Imposta il numero di volte in cui è possibile utilizzare il radar
 * da un giocatore, restituendo il dato aggiornato.
 * 
 * @param player Giocatore a cui aggiurnare il numero di utilizzi del radar.
 * @param radarAmount Numero di utilizzi del radar.
 * @return Giocatore aggiornato.
 */
Player setRadar(Player player, int radarAmount)
{
	player.radar = radarAmount;
	return player;
}


/**
 * @brief Imposta il numero di bombardamenti disponibili ad un 
 * giocatore, restituendo il dato aggiornato.
 * 
 * @param player Giocatore a cui aggiornare il numero di bombardamenti disponibili.
 * @param airstrikeAmount Numero di bombardamenti disponibili.
 * @return Giocatore aggiornato 
 */
Player setAirstrike(Player player, int airstrikeAmount)
{
	player.aistrike = airstrikeAmount;
	return player;
}


/**
 * @brief Imposta il numero di navi attive di un giocatore, restituendo
 * il dato aggiornato.
 * 
 * @param player Giocatore a cui aggiornare il numero di navi attive.
 * @param availableShips Numero di navi attive.
 * @return Giocatore aggiornato. 
 */
Player setAvailableShips(Player player, int availableShips)
{
	player.availableShips = availableShips;
	return player;
}


/**
 * @brief Imposta ad una nave, un suo indice, all'interno di un array di navi
 * attive del giocatore, restituendo il dato aggiornato.
 * 
 * @param player Giocatore a cui aggiungere una nave, in un indice 
 * specifico della sua lista.
 * @param index Indice della nave.
 * @param ship Nave da aggiungere.
 * @return Giocatore aggiornato.
 */
Player setShip(Player player, int index, Ship ship)
{
	player.ships[index - 1] = ship;
	return player;
}


/**
 * @brief Aggiorna il valore del campo playground, del dato strutturato player, con il contenuto
 * dell'array playground, restituendo il dato strutturato aggiornato.
 * 
 * @param player Giocatore da aggiornare.
 * @param playground Contenuto aggiornato del playground
 * @return Giocatore aggiornato. 
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
 * @brief Aggiorna il valore del campo heatmap, del dato strutturato player, con il contenuto
 * dell'array heatMap, restituendo il dato strutturato aggiornato.
 * 
 * @param player Giocatore da aggiornare.
 * @param heatMap Contenuto aggiornato della heat map.
 * @return Giocatore aggiornato. 
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
