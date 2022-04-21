#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 16
#define COLS 16
#define DIM_RANGE 7
#define DIM_COORDS 6
#define SHIP_NUMB 15

typedef struct
{
	char values[ROWS][COLS];
	int rows;
	int cols;
} grid;

typedef struct
{
	char label;
	int sunk;
	int size;
	char range[DIM_RANGE];
	char coords[DIM_COORDS];
} ship;

typedef struct
{
	int id;
	grid playground;
	grid heatMap;
	int longShots;
	int radar;
	int aistrike;
	int availableShips;
	ship ships[SHIP_NUMB];
} player;

int readRows(grid grid)
{
	int rows;
	rows = grid.rows;
	return rows;
}

int readCols(grid grid)
{
	int cols;
	cols = grid.cols;
	return cols;
}

char readValues(grid grid, int row, int col)
{
	char value;
	value = grid.values[row - 1][col - 1];
	return value;
}

grid writeRows(grid grid, int row)
{
	grid.rows = row;
	return grid;
}

grid writeCols(grid grid, int col)
{
	grid.cols = col;
	return grid;
}

grid writeValues(grid grid, int row, int col, char value)
{
	grid.values[row - 1][col - 1] = value;
	return grid;
}

char readLabel(ship ship)
{
	char label;
	label = ship.label;
	return label;
}

int readSunk(ship ship)
{
	int sunk;
	sunk = ship.sunk;
	return sunk;
}

int readSize(ship ship)
{
	int size;
	size = ship.size;
	return size;
}
void readRange(ship ship, char range[])
{
	strcpy(range, ship.range);
	return;
}

void readCords(ship ship, char coords[])
{
	coords = ship.coords;
	return;
}

ship writeLabel(ship ship, char label)
{
	ship.label = label;
	return ship;
}

ship writeSunk(ship ship, int sunk)
{
	ship.sunk = sunk;
	return ship;
}

ship writeSize(ship ship, int size)
{
	ship.size = size;
	return ship;
}
ship writeRange(ship ship, char range[])
{
	strcpy(ship.range, range); // METTERE LA NOSTRA STRCPY???????
	return ship;
}

ship writeCords(ship ship, char coords[])
{
	strcpy(ship.coords, coords);
	return ship;
}

int readId(player player)
{
	int id;
	id = player.id;
	return id;
}

grid readPlayground(player player)
{
	grid playground;
	playground = player.playground;
	return playground;
}

grid readHeatMap(player player)
{
	grid heatMap;
	heatMap = player.heatMap;
	return heatMap;
}

int readLongshots(player player)
{
	int longShots;
	longShots = player.longShots;
	return longShots;
}

int readRadar(player player)
{
	int radar;
	radar = player.radar;
	return radar;
}

int readAirstrike(player player)
{
	int airstrike;
	airstrike = player.aistrike;
	return airstrike;
}

int readAvailableShips(player player)
{
	int availableShips;
	availableShips = player.availableShips;
	return availableShips;
}

ship readShip(player player, int index)
{
	ship ship;
	ship = player.ships[index - 1];
	return ship;
}

player writeId(player player, int id)
{
	player.id = id;
	return player;
}

player writePlayground(player player, grid playground)
{
	player.playground = playground;
	return player;
}

player writeHeatMap(player player, grid heatMap)
{
	player.heatMap = heatMap;
	return player;
}

player writeLongshots(player player, int longShots)
{
	player.longShots = longShots;
	return player;
}

player writeRadar(player player, int radar)
{
	player.radar = radar;
	return player;
}

player writeAirstrike(player player, int airstrike)
{
	player.aistrike = airstrike;
	return player;
}

player writeAvailableShips(player player, int availableShips)
{
	player.availableShips = availableShips;
	return player;
}

player writeShip(player player, int index, ship ship)
{
	player.ships[index - 1] = ship;
	return player;
}

grid createPlayground()
{
	grid grid;
	int i;
	int j;
	i = 1;
	while (i <= ROWS)
	{
		j = 1;
		while (j <= COLS)
		{
			grid = writeValues(grid, i, j, '~');
			j++;
		}
		i++;
	}
	return grid;
}

void printGrid(grid grid)
{
	int i;
	int j;
	int k;
	char a = 'A';
	k = 1;
	printf("   ");
	while (k <= ROWS)
	{
		printf(" %c ", a);
		a++;
		k++;
	}
	printf("\n");
	i = 1;
	while (i <= ROWS)
	{
		j = 1;
		printf(" %d ", i);
		while (j <= COLS)
		{
			printf(" %c ", readValues(grid, i, j));
			j++;
		}
		printf("\n");
		i++;
	}
	return;
}

grid createHeatMap()
{
	grid grid;
	int i;
	int j;
	i = 1;
	while (i <= ROWS)
	{
		j = 1;
		while (j <= COLS)
		{
			grid = writeValues(grid, i, j, '?');
			j++;
		}
		i++;
	}
	return grid;
}

char getCol()
{
	int errore;
	char col;
	do
	{
		errore = 0;
		printf("Inserisci la colonna di partenza della nave ->");
		fflush(stdin);
		col = getchar();
		if (col >= 'a' && col <= 'p')
		{
			col -= 32;
		}
		if (col < 'A' || col > 'P')
		{
			errore = 1;
		}
	} while (errore == 1);
	return col;
}

int isValidRow(char row[])
{
	int n = 0;
	int i = 0;
	int isValid = 1;
	while (row[i] != '\0' && isValid == 1)
	{
		if (row[i] < '0' || row[i] > '9')
		{
			isValid = 0;
		}
		else
		{
			n *= 10;
			n = n + row[i] - 48;
			i++;
		}
	}
	if (n < 1 || n > 16)
		isValid = 0;
	return isValid;
}

void getRow(char row[])
{
	do
	{
		printf("Inserisci la riga di partenza della nave ->");
		fflush(stdin);
		gets(row);
	} while (isValidRow(row) == 0);
	return;
}

void getCell(char cell[])
{
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
	while (row[j] != '\0')
	{
		cell[i] = row[j];
		i++;
		j++;
	}
	cell[i] = '\0';
	return;
}

char getDirection()
{
	int errore;
	char direction;
	do
	{
		errore = 0;
		printf("Inserire v (oppure V) per inserire la nave in verticale, o (oppure O) per inserire la nave in orizzontale ");
		fflush(stdin);
		direction = getchar();
		if (direction == 'o' || direction == 'v')
		{
			direction -= 32;
		}

		if (direction != 'V' && direction != 'O')
		{
			errore = 1;
		}
	} while (errore == 1);
	return direction;
}

grid setVertical(grid playground, ship ship)
{
	int size = readSize(ship);
	char range[DIM_RANGE];
	readRange(ship, range);
	int row = range[2] - 48;
	int col = range[0] - 64;
	char label = readLabel(ship);
	
	while (row <= size)
	{
		playground = writeValues(playground, row, col, label);
		row++;
	}
	return playground;
}

grid setOrizzontal(grid playground, ship ship)
{
	int size = readSize(ship);
	char range[DIM_RANGE];
	readRange(ship, range);
	int row = range[2] - 48;
	int col = range[0] - 64;
	char label = readLabel(ship);
	
	while (col <= size)
	{
		playground = writeValues(playground, row, col, label);
		col++;
	}
	return playground;
}

grid fillPlayground(grid playground, player p)
{
	ship ship;
	char range[7];
	char cell[5];
	char direction;
	int col;
	int row;
	int i = 1; // Numero di nave
	int j = 0;
	int size = 5; // dimensione della nave

	// CREAZIONE DI UNA NAVE
	printf("NAVE DI DIMENSIONE 5 \n");
	ship = writeSize(ship, size);
	ship = writeLabel(ship, i + 96);
	ship = writeSunk(ship, 0);
	getCell(cell);
	direction = getDirection();
	while (cell[j] != '\0')
	{
		range[j] = cell[j];
		j++;
	}
	range[j] = '_';
	j++;
	range[j] = direction;
	j++;
	range[j] = '_';
	j++;
	range[j] = size + 48;
	j++;
	range[j] = '\0';

	ship = writeRange(ship, range);

	printf("STAMPA DELLA COSA\n");

	// SALVATAGGIO NAVE SU MAPPA
	if (direction == 'V')
	{
		playground = setVertical(playground, ship);
	}
	else
	{
		playground = setOrizzontal(playground, ship);
	}
	printGrid(playground);
	return playground;
}

int main()
{
	grid playground = createPlayground();
	printf("\nSTAMPA DELLA TUA MAPPA\n");
	printGrid(playground);

	grid heatMap = createHeatMap();
	printf("\nSTAMPA DELLA TUA HEATMAP\n");
	printGrid(heatMap);

	player p;
	playground = fillPlayground(playground, p);
	
	system("pause");
	return 0;
}
