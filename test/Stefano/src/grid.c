#include <stdio.h>
#include <stdlib.h>

#define ROWS 16
#define COLS 16

typedef struct {
	char values[ROWS][COLS];
	int rows;
	int cols;
} grid;

int readRows(grid grid);
int readCols(grid grid);
char readValue(grid grid, int row, int col);
grid writeRows(grid grid, int rows);
grid writeCols(grid grid, int cols);
grid writeValue(grid grid, int row, int col, char value);
void printGrid(grid grid);
grid createPlayground();
grid createHeatMap();

int readRows(grid grid) {
	int rows;
	rows = grid.rows;
	return rows;
}

int readCols(grid grid) {
	int cols;
	cols = grid.cols;
	return cols;
}

char readValue(grid grid, int row, int col) {
	char value;
	value = grid.values[row - 1][col - 1];
	return value;
}

grid writeRows(grid grid, int rows) {
	grid.rows = rows;
	return grid;
}

grid writeCols(grid grid, int cols) {
	grid.cols = cols;
	return grid;
}

grid writeValue(grid grid, int row, int col, char value) {
	grid.values[row - 1][col - 1] = value;
	return grid;
}

grid createPlayground() {
	grid grid;
	int i;
	int j;
	i = 1;
	while (i <= ROWS) {
		j = 1;
		while (j <= COLS) {
			grid = writeValue(grid, i, j, '~');
			j++;
		}
		i++;
	}
	return grid;
}

void printGrid(grid grid) {
	int i;
	int j;
	int k;
	char c;
	c = 'A';
	k = 1;
	printf("   ");
	while (k <= ROWS) {
		printf(" %c ", c);
		c++;
		k++;
	}
	printf("\n");
	i = 1;
	while (i <= ROWS) {
		if (i <= 9) {
			printf(" ");
		}
		j = 1;
		printf(" %d ", i);
		while (j <= COLS) {
			printf(" %c ", readValue(grid, i, j));
			j++;
		}
		printf("\n");
		i++;
	}
	return;
}

grid createHeatMap() {
	grid grid;
	int i;
	int j;
	i = 1;
	while (i <= ROWS) {
		j = 1;
		while (j <= COLS) {
			grid = writeValue(grid, i, j, '?');
			j++;
		}
		i++;
	}
	return grid;
}

