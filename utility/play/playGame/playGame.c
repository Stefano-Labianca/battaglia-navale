#include <stdlib.h>
#include <stdio.h>

#include "./playGame.h"

void playGame(Round round, int numFile) {
	int turn;
	int whoPlay;
	int pause;
	Player player1;
	Player player2;
	int AvailableShipsControl;
	int idWinner;
	int end;

	system("cls");
	player1 = getActivePlayer(round);
	player2 = getPassivePlayer(round);
	turn = getGameRound(round);
	whoPlay = getWhoPlay(round);
	pause = getPause(round);
	end = 0;

	while ((pause == 0) && (end == 0)) {
		if (whoPlay == 1) {
			printf("\n\n\nORA GIOCA IL GIOCATORE 1");
			round = setActivePlayer(round, player1);
			round = setPassivePlayer(round, player2);
			round = newTurn(round);
			pause = getPause(round);
			printf("%d", pause);
			if (pause == 0) {
				player1 = getActivePlayer(round);
				player2 = getPassivePlayer(round);
				whoPlay = 2;
				round = setWhoPlay(round, whoPlay);
			}
		}

		else {
			printf("\n\n\nORA GIOCA IL GIOCATORE 2");
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
			saveGame(round, numFile);
			AvailableShipsControl = getAvailableShips(player2);
			if (AvailableShipsControl == 0) {
				idWinner = getId(player1);
				printf("\n Partita finita: ha vinto il giocatore %d\n",
						idWinner);
				end = 1;
			}

			else {
				turn++;
				round = setGameRound(round, turn);
			}
		}
		system("cls");
	}
	return;
}

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

	printf("ECCO LA TUA ATTUALE CONOSCENZA DEL CAMPO AVVERSARIO\n");
	showMap(activePlayerHeatMap);

	activePlayerLongShot = getLongShots(activePlayer);
	activePlayerAirStrike = getAirstrike(activePlayer);
	activePlayerRadar = getRadar(activePlayer);
	turn = getGameRound(round);

	do {
		error = 0;
		choice = nextMoveChoice();

		if (choice == '1') {
			column = columnChoice() - 1;
			row = rowChoice() - 1;
			round = hit(row, column, round);
			clickToContinue();
		}

		else if (choice == '2') {
			if (activePlayerLongShot > 0) {
				column = columnChoice();
				row = rowChoice();
				round = longShot(row, column, round);
				activePlayer = getActivePlayer(round);
				activePlayer = setLongshots(activePlayer,
						(activePlayerLongShot - 1));
				round = setActivePlayer(round, activePlayer);
				clickToContinue();
			}

			else {
				error = 1;
				printf(
						"\nErrore: non hai colpi a largo raggio a disposizione\n");
			}
		}

		else if (choice == '3') {
			if (turn > 10) {
				if (activePlayerAirStrike > 0) {
					axis = axisChoice();
					if (axis == 'R') {
						row = rowChoice();
						round = airStrikeRow(round, row);
						activePlayer = getActivePlayer(round);
						activePlayer = setAirstrike(activePlayer,
								(activePlayerAirStrike - 1));
						round = setActivePlayer(round, activePlayer);
						clickToContinue();
					}

					else {
						column = columnChoice();
						round = airStrikeColumn(round, column);
						activePlayer = getActivePlayer(round);
						activePlayer = setAirstrike(activePlayer,
								(activePlayerAirStrike - 1));
						round = setActivePlayer(round, activePlayer);
						clickToContinue();
					}
				}

				else {
					error = 1;
					printf(
							"\nErrore: non hai il bombardamento aereo a disposizione\n");
				}
			}

			else {
				error = 1;
				printf(
						"\n Errore: Sara' possibile utilizzare il bombardamento aereo tra %d turni\n",
						11 - turn);
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
				clickToContinue();
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

char nextMoveChoice() {
	char choice;
	choice = ' ';

	int error;

	do {
		error = 0;
		printf(
				"Mosse: \n 1: colpo normale \n 2: colpo a largo raggio \n 3: bombardamento aereo \n 4: radar \n 5: esci\n Seleziona la tua mossa: ");
		choice = getchar();

		if (choice < '1' || choice > '5') {
			error = 1;
			printf("\n Errore \n");
		}

		fflush(stdin);
	} while (error == 1);

	return choice;
}

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
 * @brief Permette al giocatore attivo di colpire una cella
 * della mappa dell'avversario, restituendo il match di gioco
 * modificato.
 *
 * @param row Riga del colpo.
 * @param column Colonna del colpo.
 * @param match Match di gioco da modificare.
 * @return Match di gioco modificato.
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

	if (passivePlayground[row][column] == WATER
			|| passivePlayground[row][column] == PLAYGROUND_HIT) {
		activeHeatMap[row][column] = WATER;
		printf("\n%c-%d: ACQUA!\n", (column + START_UPPERCASE_ASCII),
				(row + 1));
	}

	else {
		ship = getShip(passivePlayer, (cell - START_LOWERCASE_ASCII + 1));
		lifePoints = getLifePoints(ship);

		if (lifePoints == 1) {
			printf("\n%c-%d: COLPITO E AFFONDATO!\n",
					(column + START_UPPERCASE_ASCII), (row + 1));
			passivePlayerShips = getAvailableShips(passivePlayer);
			passivePlayerShips--;
			passivePlayer = setAvailableShips(passivePlayer,
					passivePlayerShips);
			getCoords(ship, passivePlayerCoords);
			direction = getDirection(ship);

			row = pullRow(ship) - 1;
			column = pullColumn(ship) - 1;

			if (direction == 'V') {
				while (passivePlayground[row][column] != WATER) {
					passivePlayground[row][column] = SUNK;
					activeHeatMap[row][column] = SUNK;
					row++;
				}
			}

			else {
				while (passivePlayground[row][column] != WATER) {
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
		passivePlayer = setShip(passivePlayer,
				(cell - START_LOWERCASE_ASCII + 1), ship);
	}

	passivePlayer = setPlayground(passivePlayer, passivePlayground);
	activePlayer = setHeatMap(activePlayer, activeHeatMap);

	match = setActivePlayer(match, activePlayer);
	match = setPassivePlayer(match, passivePlayer);

	return match;
}

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

	row--;
	column--;
	pivotColumn = column - 1;
	pivotRow = row - 1;

	if (pivotColumn < TABLE_MIN - 1) {
		pivotColumn = TABLE_MIN - 1;
	}

	if (pivotRow < TABLE_MIN - 1) {
		pivotRow = TABLE_MIN - 1;
	}

	endRow = row + 1;
	endColumn = column + 1;

	if (endRow > TABLE_MAX - 1) {
		endRow = TABLE_MAX - 1;
	}
	if (endColumn > TABLE_MAX - 1) {
		endColumn = TABLE_MAX - 1;
	}

	while (pivotRow <= endRow) {
		i = pivotColumn;
		while (i <= endColumn) {
			match = hit(pivotRow, i, match);
			i++;
		}
		pivotRow++;
	}

	return match;
}

char axisChoice() {
	char axis;
	int error;

	axis = ' ';
	error = 0;

	do {
		error = 0;
		printf(
				"Inserire R se si vuole colpire la riga, oppure C se si vuole colpire la colonna: ");

		axis = getchar();

		if (axis != 'C' && axis != 'R') {
			error = 1;
			printf("\n\nErrore\n\n"); // TODO: Da gestire meglio la stampa dell'errore
		}

		fflush(stdin);
	} while (error == 1);

	return axis;
}

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

	row--;
	i = 0;

	while (i < TABLE_MAX) {
		match = hit(row, i, match);
		i++;
	}

	return match;
}

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

	column--;
	i = 0;

	while (i < TABLE_MAX) {
		match = hit(i, column, match);
		i++;
	}

	return match;
}

Round scan(int row, int column, Round match) {
	char passivePlayground[TABLE_MAX][TABLE_MAX];
	char activeHeatMap[TABLE_MAX][TABLE_MAX];

	Player passivePlayer;
	Player activePlayer;

	passivePlayer = getPassivePlayer(match);
	activePlayer = getActivePlayer(match);

	getPlayground(passivePlayer, passivePlayground);
	getHeatMap(activePlayer, activeHeatMap);

	if (passivePlayground[row][column] == WATER
			|| passivePlayground[row][column] == PLAYGROUND_HIT) {
		activeHeatMap[row][column] = WATER;
		printf("\n%c-%d: VUOTO!\n", (column + START_UPPERCASE_ASCII),
				(row + 1));
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
	row--;
	column--;
	pivotColumn = column - 1;
	pivotRow = row - 1;
	if (pivotColumn < TABLE_MIN - 1) {
		pivotColumn = TABLE_MIN - 1;
	}
	if (pivotRow < TABLE_MIN - 1) {
		pivotRow = TABLE_MIN - 1;
	}
	endRow = row + 1;
	endColumn = column + 1;
	if (endRow > TABLE_MAX - 1) {
		endRow = TABLE_MAX - 1;
	}
	if (endColumn > TABLE_MAX - 1) {
		endColumn = TABLE_MAX - 1;
	}

	printf(
			"Row=%d\tColumn=%d\nPivotRow=%d\tPivotColumn=%d\tEndRow=%d\tEndColumn=%d\n",
			row, column, pivotRow, pivotColumn, endRow, endColumn);
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

void clickToContinue() {

	printf("\n\nPremi INVIO per continuare: ");
	getchar();
	fflush(stdin);
	return;
}

