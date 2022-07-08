#include <stdio.h>
#include <stdlib.h>

#include "./playGame.h"

/**
 * Funzione playGame
 * DESCRIZIONE: La funzione gestisce lo svolgimento della partita
 * 
 * INPUT
 * round - Round della partita - Round - /
 * numFile - Numero di file di salvataggio della partita - Intero - numFile >= 1 AND numFile <= 7
 *
 * OUTPUT
 * file - file di salvataggio della partita - file binario - /
 *
 * LAVORO
 * turn - Turno di gioco - Intero - turn > 0
 * whoPlay - Indica il player che attacca - Intero - 1 = Attacca il player 1; 2 = Attacca il player 2
 * pause - Indica lo stato di pausa della partita - Intero - 1 = Uscire dalla partita; 0 = Continuare a giocare
 * player1 - Player che attacca - Player - /
 * player2 - Player che subisce l'attacco - Player - /
 * end - Indica se la partita e' terminata o meno - Intero - 1 = partita terminata; 2 = partita in corso
 * availableShipsControl - Numero di navi rimaste al giocatore che subisce l'attacco - Intero - availableShipsControl >= 0 AND availableShipsControl <= MAX_SHIP_AMOUNT
 * idWinner - Id del player vincitore - Intero - 1 = Player 1; 2 = Player 2
 * swap	- Player temporaneo necessario per il salvataggio - Player - /
 */
void playGame(Round round, int numFile) {
	int turn;
	int whoPlay;
	int pause;
	Player player1;
	Player player2;
	int AvailableShipsControl;
	int idWinner;
	int end;
	Player swap;
	system("cls"); // Funzione cleanScreen
	player1 = getActivePlayer(round);
	player2 = getPassivePlayer(round);
	turn = getGameRound(round);
	whoPlay = getWhoPlay(round);
	pause = getPause(round);
	end = 0;

	while ((pause == 0) && (end == 0)) {
		if (whoPlay == 1) {
			printf("ORA GIOCA IL GIOCATORE 1\n");
			round = setActivePlayer(round, player1);
			round = setPassivePlayer(round, player2);
			round = newTurn(round);
			pause = getPause(round);

			if (pause == 0) {
				player1 = getActivePlayer(round);
				player2 = getPassivePlayer(round);
				whoPlay = 2;
				round = setWhoPlay(round, whoPlay);
			}
		}

		else {
			printf("ORA GIOCA IL GIOCATORE 2\n");
			round = setActivePlayer(round, player2);
			round = setPassivePlayer(round, player1);
			round = newTurn(round);
			pause = getPause(round);

			if (pause == 0) {
				player2 = getActivePlayer(round);
				player1 = getPassivePlayer(round);
				whoPlay = 1;
				round = setWhoPlay(round, whoPlay);
			}
		}

		if (pause == 0) {
			AvailableShipsControl = getAvailableShips(getPassivePlayer(round));
			if (AvailableShipsControl == 0) {
				idWinner = getId(getActivePlayer(round));
				printf("\nPartita finita: ha vinto il giocatore %d\n", idWinner);
				end = 1;
				system("pause"); // Funzione clickToContinue
			}
			else {
				turn++;
				round = setGameRound(round, turn);
			}

			/* Dato che saveGame salva la partita con i ruoli impostati
			 * con l'ultimo giocatore che ha effettuato il proprio turno
			 * e' necessario scambiare i due ruoli dopo il turno del
			 * giocatore 1 affinche' le variabili player1 e player2 ricevano
			 * rispettivamente player1 e player2 dalla round per poter poi
			 * essere gestite dai turni
			*/
			if (whoPlay == 1) {
				swap = getActivePlayer(round);
				round = setActivePlayer(round, getPassivePlayer(round));
				round = setPassivePlayer(round, swap);
			}
			saveGame(round, numFile);

		}
		system("cls"); // Funzione cleanScreen
	}
	return;
}

/**
 * Funzione newTurn
 * DESCRIZIONE: La funzione permette al giocatore attivo di giocare un nuovo turno
 * 
 * INPUT
 * round - Round della partita da giocare - Round - /
 * AIRSTRIKE_TURN - Turno dal quale si puo' iniziare ad utilizzare l'Airstrike - Numero intero - 10
 * 
 * OUTPUT
 * round - Round della partita giocato - Round - /
 * 
 * LAVORO
 * activePlayer	- Player che attacca - Player - /
 * activePlayerPlayground - Playground del player che attacca - Array bidimensionale di caratteri - Dimensione 16x16;
 * Caratteri consentiti:
 * Da 'a' a 'o' per le navi
 * '~' per il mare
 * 'x' nave colpita
 * '*' nave affondata
 * activePlayerHeatMap - HeatMap del player che attacca - Array bidimensionale di caratteri - Dimensione 16x16;
 * Caratteri consentiti:
 * '~' per il mare
 * '?' per ignoto
 * '!' per nave colpita
 * '*' nave colpita e affondata
 * '#' nave scansionata
 * Turn - Turno di gioco - Intero - turn > 0
 * Pause - Indica lo stato di pausa del gioco - Intero - 1 = Uscire dalla partita; 0 = Continuare a giocare
 * Choice - Scelta della prossima mossa - Carattere - Choice >='1' AND choice <= '5'
 * row - Riga scelta - Intero - row >= TABLE_MIN AND row <= TABLE_MAX
 * column - Colonna scelta - Intero - column >= TABLE_MIN AND column <= TABLE_MAX
 * axis - Asse scelto - Carattere - R = Riga; C = Colonna
 * activePlayerLongShot - Numero di longShot di activePlayer ancora disponibili - Intero - activePlayerLongShot >= 0 AND activePlayerLongShot <= MAX_LONG_SHOT
 * activePlayerAirStrike - Numero di airStrike di activePlayer ancora disponibili - Intero - activePlayerAirStrike >= 0 AND activePlayerAirStrike <= MAX_AIR_STRIKE
 * activePlayerRadar - Numero di radar di activePlayer ancora disponibili - Intero - activePlayerRadar >= 0 AND activePlayerRadar <= MAX_RADAR
 * error - Indica una scelta non valida - Intero - 1 = scelta non valida; 0 = scelta valida
 */
Round newTurn(Round round) {

	Player activePlayer;
	char activePlayerPlayground[TABLE_MAX][TABLE_MAX];
	char activePlayerHeatMap[TABLE_MAX][TABLE_MAX];
	int turn;
	int pause;
	char choice;
	int row;
	int column;
	char axis;
	int activePlayerLongShot;
	int activePlayerAirStrike;
	int activePlayerRadar;
	int error;

	activePlayer = getActivePlayer(round);
	getPlayground(activePlayer, activePlayerPlayground);
	getHeatMap(activePlayer, activePlayerHeatMap);

	printf("ECCO LA TUA ATTUALE MAPPA DI GIOCO\n");
	showMap(activePlayerPlayground);

	printf("\nECCO LA TUA ATTUALE CONOSCENZA DEL CAMPO AVVERSARIO\n");
	showMap(activePlayerHeatMap);

	activePlayerLongShot = getLongShots(activePlayer);
	activePlayerAirStrike = getAirstrike(activePlayer);
	activePlayerRadar = getRadar(activePlayer);
	turn = getGameRound(round);

	do {
		error = 0;
		choice = nextMoveChoice();

		if (choice == '1') {
			column = columnChoice() - 1; // decremento di 1 perche' l'indice della colonna parte da 0
			row = rowChoice() - 1; // decremento di 1 perche' l'indice della riga parte da 0
			round = hit(row, column, round);
			system("pause"); // Funzione clickToContinue
		}

		else if (choice == '2') {
			if (activePlayerLongShot > 0) {
				column = columnChoice(); // non decremento di 1 perche' viene effettuato nella longShot
				row = rowChoice(); // non decremento di 1 perche' viene effettuato nella longShot
				round = longShot(row, column, round);
				activePlayer = getActivePlayer(round);
				activePlayer = setLongshots(activePlayer, (activePlayerLongShot - 1));
				round = setActivePlayer(round, activePlayer);
				system("pause"); // Funzione clickToContinue
			}

			else {
				error = 1;
				printf("\nErrore: non hai colpi a largo raggio a disposizione\n");
			}
		}

		else if (choice == '3') {
			if (turn > AIRSTRIKE_TURN) {
				if (activePlayerAirStrike > 0) {
					axis = axisChoice();
					if (axis == 'R') {
						row = rowChoice();
						round = airStrikeRow(round, row);
						activePlayer = getActivePlayer(round);
						activePlayer = setAirstrike(activePlayer, (activePlayerAirStrike - 1));
						round = setActivePlayer(round, activePlayer);
						system("pause"); // Funzione clickToContinue
					}

					else {
						column = columnChoice();
						round = airStrikeColumn(round, column);
						activePlayer = getActivePlayer(round);
						activePlayer = setAirstrike(activePlayer, (activePlayerAirStrike - 1));
						round = setActivePlayer(round, activePlayer);
						system("pause"); // Funzione clickToContinue
					}
				}

				else {
					error = 1;
					printf("\nErrore: non hai il bombardamento aereo a disposizione\n");
				}
			}

			else {
				error = 1;
				printf("\n Errore: bombardamento aereo non attivo\n");
			}
		}

		else if (choice == '4') {
			if (activePlayerRadar > 0) {
				column = columnChoice();
				row = rowChoice();
				round = radar(round, row, column);
				activePlayer = getActivePlayer(round);
				activePlayer = setRadar(activePlayer, (activePlayerRadar - 1));
				round = setActivePlayer(round, activePlayer);
				system("pause"); // Funzione clickToContinue
			}

			else {
				error = 1;
				printf("\nErrore: non hai il radar a disposizione\n");
			}
		}

		else if (choice == '5') {
			pause = 1;
			round = setPause(round, pause);
		}

	} while (error == 1);
	return round;
}

/**
 * Funzione nextMoveChoice
 * DESCRIZIONE: la funzione permette al giocatore di selezionare il tipo di mossa che vuole effettuare
 * 
 * INPUT
 * choice - Scelta della prossima mossa - Carattere - choice >= '1' AND choice <= '5'
 * 
 * OUTPUT
 * choice - Scelta della prossima mossa - Carattere - choice >= '1' AND choice <= '5'
 * 
 * LAVORO
 * error - Indica se la scelta effettuata e' valida - Intero - 1 = Scelta non valida; 0 = scelta valida
 *  
 */
char nextMoveChoice() {
	char choice;
	choice = ' ';

	int error;

	do {
		error = 0;
		printf("Mosse: \n 1: colpo normale \n 2: colpo a largo raggio \n 3: bombardamento aereo \n 4: radar \n 5: esci\n Seleziona la tua mossa: ");
		choice = getchar();

		if (choice < '1' || choice > '5') {
			error = 1;
			printf("\n Errore: inserire una scelta valida \n");
		}

		fflush(stdin);
	} while (error == 1);

	return choice;
}

/**
 * Funzione rowChoice
 * DESCRIZIONE: la funzione permette all'utente di scegliere la riga da colpire
 * 
 * INPUT
 * row - Scelta della riga da colpire - Intero - row >= TABLE_MIN AND row <= TABLE_MAX
 * TABLE_MIN - Riga/Colonna minima - Numero intero - 1
 * TABLE_MAX - Riga/Colonna massima	- Numero intero - 16
 * 
 * OUTPUT
 * row - Scelta della riga da colpire - Intero - row >= TABLE_MIN AND row <= TABLE_MAX
 * 
 * LAVORO
 * error - Indica una scelta non valida - Intero - 1 = scelta non valida; 0 = scelta valida
 */
int rowChoice() {
	int row;
	int error;

	row = 0;

	do {
		error = 0;
		printf("Inserire la riga da colpire: ");
		scanf("%d", &row);

		if (row < TABLE_MIN || row > TABLE_MAX) {
			error = 1;
			printf("\n\nErrore: inserire un valore di riga valido\n\n");
		}

		fflush(stdin);
	} while (error == 1);

	return row;
}

/**
 * Funzione columnChoice
 * DESCRIZIONE: la funzione permette all'utente di selezionare la colonna da colpire
 * 
 * INPUT
 * column - Scelta della colonna da colpire, da convertire in un intero - Carattere	- column >= 'A' AND column <= 'P'
 * 
 * OUTPUT
 * intColumn - Scelta della colonna da colpire, convertita in un intero - Intero - column >= TABLE_MIN AND column <= TABLE_MAX
 * 
 * LAVORO
 * error - Indica una scelta non valida - Intero - 1 = scelta non valida; 0 = scelta valida
 */
int columnChoice() {
	char column;
	int error;
	int intColumn;

	column = ' ';

	do {
		error = 0;
		printf("Inserire la colonna da colpire: ");

		column = getchar();
		column = toUpperCase(column);
		fflush(stdin);

		if (column < 'A' || column > 'P') {
			error = 1;
			printf("\n\nErrore: inserire un valore di colonna valido\n\n");
		}

		fflush(stdin);
	} while (error == 1);

	intColumn = getIntegerColumn(column);

	return intColumn;
}

/**
 * Funzione hit
 * DESCRIZIONE: Permette al giocatore attivo di colpire una cella
 * della mappa dell'avversario, restituendo il match di gioco
 * modificato.
 * 
 * INPUT
 * row - Riga del colpo - intero - row >= TABLE_MIN AND row <= TABLE_MAX
 * column - Colonna del colpo - intero - column >= TABLE_MIN AND column <= TABLE_MAX
 * match - Match di gioco da modificare - Round - \
 * WATER - Carattere che indica la presenza di acqua nel playground e nell'heatMap - Carattere - '~'
 * PLAYGROUND_HIT - Carattere che indica una nave colpita nel playground - Carattere - 'X'
 * START_LOWERCASE_ASCII - Prima lettera dell'alfabeto minuscola in ASCII - Numero intero - 97
 * SUNK - Carattere che indica la presenza di una nave affondata nel playground e nell'heatMap - Carattere - '*'   
 * HEAT_MAP_HIT - Carattere che indica una nave colpita nell'heatMap - Carattere - '!'
 * START_UPPERCASE_ASCII - Prima lettera dell'alfabeto maiuscola in ASCII - Numero intero - 65
 * 
 * OUTPUT
 * match - Match di gioco modificato - Round - \
 * 
 * LAVORO
 * passivePlayground - Campo da gioco del giocatore player che subisce l'attacco - Array di caratteri a due dimensioni - Dimensione 16x16;
 * Caratteri consentiti:
 * da 'a' a 'o' per le navi
 * '~' per il mare
 * 'X' per nave colpita
 * '*' per nave affondata
 * activeHeatMap - heatMap del giocatore player che attacca - Array di caratteri a due dimensioni - Dimensione 16x16
 * Caratteri consentiti:
 * '~' per il mare
 * '!' per nave colpita
 * '*' per nave affondata
 * '#' per nave scansionata
 * cell - Contenuto della cella del passivePlayground - Carattere - Caratteri consentiti:
 * da 'a' a 'o' per le navi
 * '~' per il mare
 * 'X' per nave colpita
 * '*' per nave affondata
 * passivePlayer - Giocatore che subisce l'attacco - Player - \
 * activePlayer - Giocatore che attacca - Player - \
 * Ship - Nave del giocatore che subisce l'attacco - Ship - \
 * lifePoints - lifePoints della nave che ha subito l'attacco - Intero - lifePoints >= 0 AND lifePoints <= MAX_SHIP_SIZE
 * passivePlayerShips - Numero di navi rimaste al giocatore che ha subito l'attacco	- Intero - passivePlayerShips >= 0 AND passivePlayerShips <= MAX_SHIP_AMOUNT
 * direction - Direzione della nave - Carattere - V = Verticale; O = Orizzontale
 */
Round hit(int row, int column, Round match) {
	char passivePlayground[TABLE_MAX][TABLE_MAX];
	char activeHeatMap[TABLE_MAX][TABLE_MAX];
	char cell;
	Player passivePlayer;
	Player activePlayer;
	Ship ship;
	int lifePoints;
	int passivePlayerShips;
	char passivePlayerCoords[MAX_COORDS_RANGE];
	char direction;

	passivePlayer = getPassivePlayer(match);
	activePlayer = getActivePlayer(match);
	getPlayground(passivePlayer, passivePlayground);
	getHeatMap(activePlayer, activeHeatMap);
	cell = passivePlayground[row][column];

	if (passivePlayground[row][column] == WATER || passivePlayground[row][column] == PLAYGROUND_HIT || passivePlayground[row][column] == SUNK) {
		if (activeHeatMap[row][column] == UNKNOWN) {
			activeHeatMap[row][column] = WATER;
		}
		printf("\n%c-%d: ACQUA!\n", (column + START_UPPERCASE_ASCII),
				(row + 1));
	}

	else {
		ship = getShip(passivePlayer, (cell - START_LOWERCASE_ASCII + 1));
		lifePoints = getLifePoints(ship);
		if (lifePoints == 1) {
			printf("\n%c-%d: COLPITO E AFFONDATO!\n", (column + START_UPPERCASE_ASCII), (row + 1));
			passivePlayerShips = getAvailableShips(passivePlayer);
			passivePlayerShips--;
			passivePlayer = setAvailableShips(passivePlayer, passivePlayerShips);
			getCoords(ship, passivePlayerCoords);
			direction = getDirection(ship);
			row = pullRow(ship) - 1;
			column = pullColumn(ship) - 1;
			if (direction == 'V') {
				while (passivePlayground[row][column] != WATER && row < TABLE_MAX) {
					passivePlayground[row][column] = SUNK;
					activeHeatMap[row][column] = SUNK;
					row++;
				}
			}
			else {
				while (passivePlayground[row][column] != WATER && column < TABLE_MAX) {
					passivePlayground[row][column] = SUNK;
					activeHeatMap[row][column] = SUNK;
					column++;
				}
			}
		}

		else {
			passivePlayground[row][column] = PLAYGROUND_HIT;
			activeHeatMap[row][column] = HEAT_MAP_HIT;
			printf("\n%c-%d: COLPITO!\n", (column + START_UPPERCASE_ASCII),
					(row + 1));
		}
		ship = setLifePoints(ship, (lifePoints - 1));
		passivePlayer = setShip(passivePlayer, (cell - START_LOWERCASE_ASCII + 1), ship);
	}
	passivePlayer = setPlayground(passivePlayer, passivePlayground);
	activePlayer = setHeatMap(activePlayer, activeHeatMap);
	match = setActivePlayer(match, activePlayer);
	match = setPassivePlayer(match, passivePlayer);
	return match;
}

/**
 * Funzione longShot
 * DESCRIZIONE: la funzione effettua il colpo longShot quando richiamata
 * 
 * INPUT 
 * round - Contiene le informazioni relative al turno corrente (player che attacca, player che subisce l'attacco, numero del turno) - Round - /
 * row - riga del colpo - numero intero - row >= TABLE_MIN AND row <= TABLE_MAX
 * column - colonna del colpo - numero intero - column >= TABLE_MIN AND column <= TABLE_MAX
 * TABLE_MIN - Riga/Colonna minima - Numero intero - 1
 * TABLE_MAX - Riga/Colonna massima - Numero intero	- 16
 * 
 * OUTPUT
 * round - Contiene le informazioni aggiornate relative al colpo effettuato (player che ha attaccato, player che ha subito l'attacco, numero del turno) - Round - /
 * 
 * LAVORO
 * passivePlayground - Campo da gioco del giocatore player che subisce l'attacco - Array di caratteri a due dimensioni - Dimensione 16x16; 
 * Caratteri consentiti:
 * da 'a' a 'o' per le navi
 * '~' per il mare
 * 'x' per nave colpita
 * '*' per nave affondata
 * activeHeatMap - heatMap del giocatore player che attacca - Array di caratteri a due dimensioni - Dimensione 16x16;
 * Caratteri consentiti:
 * '~' per il mare
 * '!' per nave colpita
 * '*' per nave affondata
 * '#' per nave scansionata
 * pivotRow	- Riga di inizio del controllo - Numero intero - pivotRow >= TABLE_MIN AND pivotRow <= TABLE_MAX
 * pivotColumn - Colonna di inizio del controllo - Numero intero - pivotColumn >= TABLE_MIN AND pivotColumn <= TABLE_MAX
 * endRow - Riga di fine del controllo - Numero intero - endRow >= TABLE_MIN AND endRow <= TABLE_MAX
 * endColumn - Colonna di fine del controllo - Numero intero - endColumn >= TABLE_MIN AND endColumn <= TABLE_MAX
 * i - Contatore della colonna in passivePlayground	- Numero intero - i > 0
 * passivePlayer - Giocatore che subisce l'attacco - Player - \
 * activePlayer	- Giocatore che attacca - Player - \
 *
 */
Round longShot(int row, int column, Round match) {
	char passivePlayground[TABLE_MAX][TABLE_MAX];
	char activeHeatMap[TABLE_MAX][TABLE_MAX];
	Player passivePlayer;
	Player activePlayer;
	int i;
	int pivotRow;
	int pivotColumn;
	int endColumn;
	int endRow;

	passivePlayer = getPassivePlayer(match);
	activePlayer = getActivePlayer(match);
	getPlayground(passivePlayer, passivePlayground);
	getHeatMap(activePlayer, activeHeatMap);

	row--; // Dato che iteriamo da 0, diminuiamo di 1 la riga ricevuta dall'utente
	column--; // Dato che iteriamo da 0, diminuiamo di 1 la colonna ricevuta dall'utente

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

	pivotColumn = column - 1;
	pivotRow = row - 1;

	// controllo se il pivot esce dal limite minimo della mappa
	if (pivotColumn < TABLE_MIN - 1) {
		pivotColumn = TABLE_MIN - 1;
	}

	if (pivotRow < TABLE_MIN - 1) {
		pivotRow = TABLE_MIN - 1;
	}

	/**
	* Prendiamo la cella finale della nave
	*/
	endRow = row + 1; // Incremento di 1 perche' all'inizio della funzione avevo decrementato
	endColumn = column + 1; // Incremento di 1 perche' all'inizio della funzione avevo decrementato

	if (endRow > TABLE_MAX - 1) {
		endRow = TABLE_MAX - 1;
	}

	if (endColumn > TABLE_MAX - 1) {
		endColumn = TABLE_MAX - 1;
	}

	// Per ogni riga dalla pivotRow alla endRow colpisco le colonne da pivotColumn a endColumn
	while (pivotRow <= endRow && getAvailableShips(getPassivePlayer(match)) > 0) {
		i = pivotColumn;
		while (i <= endColumn && getAvailableShips(getPassivePlayer(match)) > 0) {
			match = hit(pivotRow, i, match);
			i++;
		}
		pivotRow++;
	}
	return match;
}

/**
 * Funzione axisChoice
 * DESCRIZIONE: la funzione permette all'utente di scegliere un asse
 * 
 * INPUT
 * axis - Scelta dell'asse da colpire - Carattere - C = colonna; R = riga
 * 
 * OUTPUT
 * axis - Scelta dell'asse da colpire - Carattere - C = colonna; R = riga
 * 
 * LAVORO
 * error - indica una scelta non valida - Intero - 1 = scelta non valida; 0 = scelta valida
 */
char axisChoice() {
	char axis;
	int error;
	axis = ' ';

	do {
		error = 0;
		printf("Inserire R se si vuole colpire la riga, oppure C se si vuole colpire la colonna: ");

		axis = getchar();
		axis = toUpperCase(axis);
		fflush(stdin);

		if (axis != 'C' && axis != 'R') {
			error = 1;
			printf("\nErrore: effettuare una scelta corretta\n");
		}

		fflush(stdin);
	} while (error == 1);

	return axis;
}


/**
 * Funzione airStrikeRow
 * DESCRIZIONE: la funzione effettua il colpo airStrike sulla riga scelta dall'utente, quando richiamata
 * 
 * INPUT
 * round - Contiene le informazioni relative al turno corrente (player che attacca, player che subisce l'attacco, numero del turno) - Round - /
 * row - Riga del colpo - numero intero - row >= TABLE_MIN AND row <= TABLE_MAX
 * TABLE_MAX - Riga/Colonna massima - Numero intero - 16
 * 
 * OUTPUT
 * round - Contiene le informazioni aggiornate relative al colpo effettuato (player che ha attaccato, player che ha subito l'attacco, numero del turno) - Round - /
 * 
 * LAVORO
 * passivePlayground - Campo da gioco del giocatore player che subisce l'attacco - Array di caratteri a due dimensioni - Dimensione 16x16;
 * Caratteri consentiti:
 * da 'a' a 'o' per le navi
 * '~' per il mare
 * 'x' per nave colpita
 * '*' per nave affondata
 * activeHeatMap - heatMap del giocatore player che attacca - Array di caratteri a due dimensioni - Dimensione 16x16;
 * Caratteri consentiti:
 * '~' per il mare
 * '!' per nave colpita
 * '*' per nave affondata
 * '#' per nave scansionata
 * i - Contatore della colonna in passivePlayground - Numero intero - i > 0
 * passivePlayer - Giocatore che subisce l'attacco - Player - \
 * activePlayer - Giocatore che attacca	- Player - \
 *  
 */
Round airStrikeRow(Round match, int row) {
	char passivePlayground[TABLE_MAX][TABLE_MAX];
	char activeHeatMap[TABLE_MAX][TABLE_MAX];
	Player passivePlayer;
	Player activePlayer;
	int i;

	passivePlayer = getPassivePlayer(match);
	activePlayer = getActivePlayer(match);
	getPlayground(passivePlayer, passivePlayground);
	getHeatMap(activePlayer, activeHeatMap);

	row--;  // Dato che iteriamo da 0, diminuiamo di 1 la riga ricevuta dall'utente

	i = 0;

	while (i < TABLE_MAX && getAvailableShips(getPassivePlayer(match)) > 0) {
		match = hit(row, i, match);
		i++;
	}

	return match;
}

/**
 * Funzione airStrikeColumn
 * DESCRIZIONE: la funzione effettua il colpo airStrike sulla colonna scelta dall'utente, quando richiamata
 * 
 * INPUT
 * round - Contiene le informazioni relative al turno corrente (player che attacca, player che subisce l'attacco, numero del turno) - Round - /
 * column - colonna del colpo - numero intero - column >= TABLE_MIN AND column <= TABLE_MAX
 * TABLE_MAX - Riga/Colonna massima - Numero intero - 16
 * 
 * OUTPUT
 * round - Contiene le informazioni aggiornate relative al colpo effettuato (player che ha attaccato, player che ha subito l'attacco, numero del turno) - Round - /
 * 
 * LAVORO
 * passivePlayground - Campo da gioco del giocatore player che subisce l'attacco - Array di caratteri a due dimensioni - Dimensione 16x16;
 * Caratteri consentiti:
 * da 'a' a 'o' per le navi
 * '~' per il mare
 * 'x' per nave colpita
 * '*' per nave affondata
 * activeHeatMap - heatMap del giocatore player che attacca - Array di caratteri a due dimensioni - Dimensione 16x16;
 * Caratteri consentiti:
 * '~' per il mare
 * '!' per nave colpita
 * '*' per nave affondata
 * '#' per nave scansionata
 * i - Contatore della colonna in passivePlayground - Numero intero	- i > 0
 * passivePlayer - Giocatore che subisce l'attacco - Player - \
 * activePlayer - Giocatore che attacca - Player - \
 */
Round airStrikeColumn(Round match, int column) {
	char passivePlayground[TABLE_MAX][TABLE_MAX];
	char activeHeatMap[TABLE_MAX][TABLE_MAX];
	Player passivePlayer;
	Player activePlayer;
	int i;

	passivePlayer = getPassivePlayer(match);
	activePlayer = getActivePlayer(match);
	getPlayground(passivePlayer, passivePlayground);
	getHeatMap(activePlayer, activeHeatMap);

	column--; // Dato che iteriamo da 0, diminuiamo di 1 la colonna ricevuta dall'utente

	i = 0;
	while (i < TABLE_MAX && getAvailableShips(getPassivePlayer(match)) > 0) {
		match = hit(i, column, match);
		system("pause");
		i++;
	}

	return match;
}

/**
 * Funzione scan
 * DESCRIZIONE: la funzione effettua la scansione del campo da gioco avversario e ne restituisce gli esiti
 * 
 * INPUT
 * round - Contiene le informazioni relative al turno corrente (player che attacca, player che subisce l'attacco, numero del turno) - Round - /
 * row - riga del colpo - numero intero - row >= TABLE_MIN AND row <= TABLE_MAX
 * column - colonna del colpo - numero intero - column >= TABLE_MIN AND column <= TABLE_MAX
 * WATER - Carattere che indica la presenza di acqua nel playground e nell'heatMap - Carattere - '~'
 * PLAYGROUND_HIT - Carattere che indica una nave colpita nel playground - Carattere - 'X'
 * HEAT_MAP_SUCCESSFUL_SCAN - Carattere che indica la presenza di una nave nell'heatMap a seguito di una scansione - Carattere - '#'
 * START_UPPERCASE_ASCII - Prima lettera dell'alfabeto maiuscola in ASCII - Numero intero - 65
 * 
 * OUTPUT
 * round - Contiene le informazioni aggiornate relative al colpo effettuato (player che ha attaccato, player che ha subito l'attacco, numero del turno)	- Round	- /
 * 
 * LAVORO 
 * passivePlayground - Campo da gioco del giocatore player che subisce l'attacco - - Array di caratteri a due dimensioni - Dimensione 16x16;
 * Caratteri consentiti:
 * da 'a' a 'o' per le navi
 * '~' per il mare
 * 'x' per nave colpita
 * '*' per nave affondata
 * activeHeatMap - heatMap del giocatore player che attacca - Array di caratteri a due dimensioni - Dimensione 16x16;
 * Caratteri consentiti:
 * '~' per il mare
 * '!' per nave colpita
 * '*' per nave affondata
 * '#' per nave scansionata
 * passivePlayer - Giocatore che subisce l'attacco - Player - \
 * activePlayer - Player - Giocatore che attacca - \
 */
Round scan(int row, int column, Round match) {
	char passivePlayground[TABLE_MAX][TABLE_MAX];
	char activeHeatMap[TABLE_MAX][TABLE_MAX];
	Player passivePlayer;
	Player activePlayer;

	passivePlayer = getPassivePlayer(match);
	activePlayer = getActivePlayer(match);
	getPlayground(passivePlayer, passivePlayground);
	getHeatMap(activePlayer, activeHeatMap);
	if (passivePlayground[row][column] == WATER	|| passivePlayground[row][column] == PLAYGROUND_HIT || passivePlayground[row][column] == SUNK) {
		if (activeHeatMap[row][column] == UNKNOWN) {
			activeHeatMap[row][column] = WATER;
		}
		printf("\n%c-%d: VUOTO!\n", (column + START_UPPERCASE_ASCII), (row + 1));
	}
	else {
		activeHeatMap[row][column] = HEAT_MAP_SUCCESSFUL_SCAN;
		printf("\n%c-%d: NAVE!\n", (column + START_UPPERCASE_ASCII), (row + 1));
	}
	passivePlayer = setPlayground(passivePlayer, passivePlayground);
	activePlayer = setHeatMap(activePlayer, activeHeatMap);
	match = setActivePlayer(match, activePlayer);
	match = setPassivePlayer(match, passivePlayer);
	return match;
}

/**
 * Funzione radar
 * DESCRIZIONE: la funzione realizza la scansione su righe e colonne richieste dall'utente
 * 
 * INPUT
 * round - Contiene le informazioni relative al turno corrente (player che attacca, player che subisce l'attacco, numero del turno) - Round - /
 * row - riga del colpo - numero intero - Row >= TABLE_MIN AND row <= TABLE_MAX
 * column - colonna del colpo - numero intero - Column >= TABLE_MIN AND column <= TABLE_MAX
 * TABLE_MIN - Riga/Colonna minima - Numero intero - 1
 * TABLE_MAX - Riga/Colonna massima - Numero intero - 16
 * 
 * OUTPUT
 * round - Contiene le informazioni aggiornate relative al colpo effettuato (player che ha attaccato, player che ha subito l'attacco, numero del turno) - Round - /
 * 
 * LAVORO 
 * passivePlayground - Campo da gioco del giocatore player che subisce l'attacco - Array di caratteri a due dimensioni - Dimensione 16x16;
 * Caratteri consentiti:
 * da 'a' a 'o' per le navi
 * '~' per il mare
 * 'x' per nave colpita
 * '#' per nave affondata
 * activeHeatMap - heatMap del giocatore player che attacca - Array di caratteri a due dimensioni - Dimensione 16x16;
 * Caratteri consentiti:
 * '~' per il mare
 * '!' per nave colpita
 * '*' per nave affondata
 * '#' per nave scansionata
 * i - Contatore della colonna in passivePlayground - Numero intero - i > 0
 * passivePlayer - Giocatore che subisce l'attacco - Player - \
 * activePlayer - Giocatore che attacca - Player - \
 * pivotRow - Riga di inizio del controllo - Numero intero - pivotRow >= TABLE_MIN AND pivotRow <= TABLE_MAX
 * pivotColumn - Colonna di inizio del controllo - Numero intero - pivotColumn >= TABLE_MIN AND pivotColumn <= TABLE_MAX
 * endRow - Riga di fine del controllo - Numero intero - endRow >= TABLE_MIN AND endRow <= TABLE_MAX
 * endColumn - Colonna di fine del controllo - Numero intero - endColumn >= TABLE_MIN AND endColumn <= TABLE_MAX
 *
 *  
 */
Round radar(Round match, int row, int column) {
	char passivePlayground[TABLE_MAX][TABLE_MAX];
	char activeHeatMap[TABLE_MAX][TABLE_MAX];
	Player passivePlayer;
	Player activePlayer;
	int i;
	int pivotRow;
	int pivotColumn;
	int endColumn;
	int endRow;

	passivePlayer = getPassivePlayer(match);
	activePlayer = getActivePlayer(match);
	getPlayground(passivePlayer, passivePlayground);
	getHeatMap(activePlayer, activeHeatMap);

	row--; // Dato che iteriamo da 0, diminuiamo di 1 la riga ricevuta dall'utente
	column--; // Dato che iteriamo da 0, diminuiamo di 1 la colonna ricevuta dall'utente

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
	pivotColumn = column - 1;
	pivotRow = row - 1;

	// controllo se il pivot esce dal limite minimo della mappa
	if (pivotColumn < TABLE_MIN - 1) {
		pivotColumn = TABLE_MIN - 1;
	}
	if (pivotRow < TABLE_MIN - 1) {
		pivotRow = TABLE_MIN - 1;
	}

	/**
	* Prendiamo la cella finale della nave
	*/
	endRow = row + 1; // Incremento di 1 perche' all'inizio della funzione avevo decrementato
	endColumn = column + 1; // Incremento di 1 perche' all'inizio della funzione avevo decrementato

	if (endRow > TABLE_MAX - 1) {
		endRow = TABLE_MAX - 1;
	}
	if (endColumn > TABLE_MAX - 1) {
		endColumn = TABLE_MAX - 1;
	}

	// Per ogni riga dalla pivotRow alla endRow scansiono le colonne da pivotColumn a endColumn
	while (pivotRow <= endRow) {
		i = pivotColumn;
		while (i <= endColumn) {
			match = scan(pivotRow, i, match);
			i++;
		}
		pivotRow++;
	}
	return match;
}



