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
Grid writeColumns(Grid grid, int cols);
Grid writeValue(Grid grid, int row, int col, char value);
Grid createPlayground();
Grid createHeatMap();

int readRows(Grid grid);
int readColumns(Grid grid);
char readValue(Grid grid, int row, int col);
void printGrid(Grid grid);


int readRows(Grid grid)
{
	int rows;
	rows = grid.rows;

	return rows;
}


int readColumns(Grid grid)
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


Grid writeColumns(Grid grid, int cols)
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
	Grid playground;
	int i;
	int j;

	i = 1;
	j = 1;
	
	while (i <= ROWS)
	{
		j = 1;
		while (j <= COLS)
		{
			playground = writeValue(playground, i, j, '~');
			j++;
		}

		i++;
	}

	return playground;
}


void printGrid(Grid grid)
{
	int i;
	int j;
	int k;
	char c = 'A';
	
	i = 1;
	j = 1;
	k = 1;

	printf("    ");
	while (k <= ROWS)
	{
		printf(" %c ", c);
		c++;
		k++;
	}
	printf("\n");
	
	while (i <= ROWS)
	{
		j = 1;

		if (i <= 9)
		{
			printf(" ");
		}

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
	Grid heatMap;
	int i;
	int j;
	
	i = 1;
	j = 1;

	while (i <= ROWS)
	{
		j = 1;
		while (j <= COLS)
		{
			heatMap = writeValue(heatMap, i, j, '?');
			j++;
		}
		i++;
	}
	
	return heatMap;
}
