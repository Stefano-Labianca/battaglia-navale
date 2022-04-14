#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./grid.c"
#include "./ship.c"
#include "./player.c"

char getCol() {
	int errore;
	char col;
	do {
		errore = 0;
		printf("Inserisci la colonna di partenza della nave ->");
		fflush(stdin);
		col = getchar();
		if (col >= 'a' && col <= 'p') {
			col -= 32;
		}
		if (col < 'A' || col > 'P') {
			errore = 1;
		}
	} while (errore == 1);
	return col;
}

int isValidRow(char row[]) {
	int n;
	int i;
	int isValid;
	n = 0;
	i = 0;
	isValid = 1;
	while (row[i] != '\0' && isValid == 1) {
		if (row[i] < '0' || row[i] > '9') {
			isValid = 0;
		} else {
			n *= 10;
			n = n + row[i] - 48;
			i++;
		}
	}
	if (n < 1 || n > 16) {
		isValid = 0;
	}
	return isValid;
}

void getRow(char row[]) {
	do {
		printf("Inserisci la riga di partenza della nave ->");
		fflush(stdin);
		gets(row);
	} while (isValidRow(row) == 0);
	return;
}

void getCell(char cell[]) {
	char col;
	char row[3];
	int i;
	int j;
	col = getCol();
	getRow(row);
	i = 0;
	cell[i] = col;
	i++;
	cell[i] = '-';
	i++;
	j = 0;
	while (row[j] != '\0') {
		cell[i] = row[j];
		i++;
		j++;
	}
	cell[i] = '\0';
	return;
}

char getDirection() {
	int errore;
	char direction;
	do {
		errore = 0;
		printf(
				"Inserire v (oppure V) per inserire la nave in verticale, o (oppure O) per inserire la nave in orizzontale ");
		fflush(stdin);
		direction = getchar();
		if (direction == 'o' || direction == 'v') {
			direction -= 32;
		}

		if (direction != 'V' && direction != 'O') {
			errore = 1;
		}
	} while (errore == 1);
	return direction;
}

grid setVertical(grid playground, ship ship) {
	char cell[6];
	readCoords(ship, cell);
	int size;
	int row;
	int col;
	int i;
	;
	char label;
	size = readSize(ship);
	row = cell[2] - 48;
	col = cell[0] - 64;
	i = 0;
	label = readLabel(ship);
	if (cell[3] >= '0' && cell[3] <= '9') {
		row *= 10;
		row += cell[3] - 48;
	}
	while (i < size) {
		playground = writeValue(playground, row, col, label);
		row++;
		i++;
	}
	// CONCATENA L ULTIMA CELLA A coordS
	return playground;
}

grid setOrizzontal(grid playground, ship ship) {
	char cell[6];
	readCoords(ship, cell);
	int size;
	int row;
	int col;
	int i;
	;
	char label;
	size = readSize(ship);
	row = cell[2] - 48;
	col = cell[0] - 64;
	if (cell[3] >= '0' && cell[3] <= '9') {
		row *= 10;
		row += cell[3] - 48;
	}
	while (i < size) {
		playground = writeValue(playground, row, col, label);
		col++;
		i++;
	}
	// CONCATENA L ULTIMA CELLA A coordS
	return playground;
}

ship createShip(ship ship, int size, int number) {
	char cell[5];
	char direction;
	ship = writeSize(ship, size);
	ship = writeLifePoints(ship, size);
	ship = writeLabel(ship, (number + 96));
	ship = writeSunk(ship, 0);
	getCell(cell);
	direction = getDirection();
	ship = writeDirection(ship, direction);
	ship = writeCoords(ship, cell);
	return ship;
}

grid fillPlayground(grid playground, player p) {
	int index;
	int size; //dimensione della nave
	ship ship;
	index = 1;
	size = 5;
	//CREAZIONE DI UNA NAVE
	printf("NAVE %d DI DIMENSIONE %d \n", index, size);
	ship = createShip(ship, size, index);
	p = writeShip(p, index, ship);
	index++;
	size--;
	while (index <= 3) {
		printf("NAVE %d DI DIMENSIONE %d \n", index, size);
		fflush(stdin);
		ship = createShip(ship, size, index);
		p = writeShip(p, index, ship);
		index++;
	}
	size--;
	while (index <= 6) {
		printf("NAVE %d DI DIMENSIONE %d \n", index, size);
		ship = createShip(ship, size, index);
		p = writeShip(p, index, ship);
		index++;
	}
	size--;
	while (index <= 10) {
		printf("NAVE %d DI DIMENSIONE %d \n", index, size);
		ship = createShip(ship, size, index);
		p = writeShip(p, index, ship);
		index++;
	}
	size--;
	while (index <= 15) {
		printf("NAVE %d DI DIMENSIONE %d \n", index, size);
		ship = createShip(ship, size, index);
		p = writeShip(p, index, ship);
		index++;
	}

	index = 1;
	while (index <= 15) {
		ship = readShip(p, index);

		if (readDirection(ship) == 'V') {
			playground = setVertical(playground, ship);
		} else {
			playground = setOrizzontal(playground, ship);
		}
		index++;
	}
	printf("\nMAPPA FIN ORA\n");
	printGrid(playground);
	return playground;
}

