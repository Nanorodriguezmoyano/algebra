#include <stdio.h>
#include <stdlib.h>


typedef struct Matrix{
	int column;
	int row;
	float **data;
}Matrix;
Matrix *init_matrix(int row, int column);
int main(int argv, char *arcgv[])
{
	float **matriz;
	int column = 3;
	int row = 2;
	for (int i = 0; i<row; i++)
	{
		*matriz = calloc(column, sizeof(float));
		*matriz ++;
	}
	for (int i = 0; i<row; i++)
	{
		for (int j = 0; j<column; j++) printf("%.2f", **(matriz++));
		printf("\n");
		*matriz ++;
	}

}
/*
Matrix *init_matrix(int row, int column)
{
	Matrix *matrix;
	matrix->column = column;
	matrix->row = row;
	for (int i = 0; i < row; i++)
	{
		*(matrix->data++) = calloc(column, sizeof(float));
	}
	for (int i = 0; i<column; i ++)
	{
		matrix->data[i] = calloc
	}
	return matrix; 
}
*/
