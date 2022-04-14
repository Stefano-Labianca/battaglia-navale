#include <stdio.h>
#include <stdlib.h>

#define ROWS 16
#define COLS 16

typedef struct Grid
{
	char values[ROWS][COLS];
	int rows;
	int cols;
} Grid;

Grid writeRows(Grid grid, int rows);
Grid writeCols(Grid grid, int cols);
Grid writeValue(Grid grid, int row, int col, char value);
Grid createPlayground();
Grid createHeatMap();

int readRows(Grid grid);
int readCols(Grid grid);
char readValue(Grid grid, int row, int col);
void printGrid(Grid grid);

int readRows(Grid grid)
{
	int rows;
	rows = grid.rows;
	return rows;
}

int readCols(Grid grid)
{
	int cols;
	cols = grid.cols;

	return cols;
}

char readValue(Grid grid, int row, int col)
{
	char value;
	value = grid.values[row - 1][col - 1];

	return value;
}

Grid writeRows(Grid grid, int rows)
{
	grid.rows = rows;
	return grid;
}

Grid writeCols(Grid grid, int cols)
{
	grid.cols = cols;
	return grid;
}

Grid writeValue(Grid grid, int row, int col, char value)
{
	grid.values[row - 1][col - 1] = value;
	return grid;
}

Grid createPlayground()
{
	Grid grid;
	int i;
	int j;
	i = 1;
	while (i <= ROWS)
	{
		j = 1;
		while (j <= COLS)
		{
			grid = writeValue(grid, i, j, '~');
			j++;
		}
		i++;
	}
	return grid;
}

void printGrid(Grid grid)
{
	int i;
	int j;
	int k;
	char c;
	c = 'A';
	k = 1;
	printf("   ");
	while (k <= ROWS)
	{
		printf(" %c ", c);
		c++;
		k++;
	}
	printf("\n");
	i = 1;
	while (i <= ROWS)
	{
		if (i <= 9)
		{
			printf(" ");
		}
		j = 1;
		printf(" %d ", i);
		while (j <= COLS)
		{
			printf(" %c ", readValue(grid, i, j));
			j++;
		}
		printf("\n");
		i++;
	}
	return;
}

Grid createHeatMap()
{
	Grid grid;
	int i;
	int j;
	i = 1;
	while (i <= ROWS)
	{
		j = 1;
		while (j <= COLS)
		{
			grid = writeValue(grid, i, j, '?');
			j++;
		}
		i++;
	}
	return grid;
}
