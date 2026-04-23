#include <stdio.h>
#include <stdlib.h>


typedef struct Matrix{
	int col;
	int row;
	float **data;
}Matrix;

Matrix *copy_matrix(const Matrix *matrix1, Matrix *matrix2);
Matrix *init_matrix(int row, int col);
void print_matrix(const Matrix* matrix);
Matrix *set_elem(int row, int col, float value, Matrix*);

int main(int argc, char *argv[])
{
	Matrix * matrix;
	matrix = init_matrix(atoi(argv[1]),atoi(argv[2]));
	print_matrix(matrix);
}
Matrix *init_matrix(int row, int col)
{
	Matrix *matrix;
	matrix= calloc(1, sizeof(Matrix));
	matrix->col = col;
	matrix->row = row;
	matrix->data = calloc(matrix->row, sizeof(float *));
	for (int i = 0; i < row; i++)
	{
		matrix->data[i] = calloc(col, sizeof(float));
	}
	return matrix; 
}

void print_matrix(const Matrix* matrix)
{
	for(int i = 0; i<matrix->row; i++ )
	{
		for(int j=0; j<matrix->col; j++) printf("%.0f ", matrix->data[i][j]);
		printf("\n");
	}
}
/*
Matrix *set_elem(int row, int col, float value, Matrix*)
{
	
}*/
Matrix *copy_matrix(const Matrix *matrix1)
{
	Matrix *matrix2;
	matrix2 = init_matrix(matrix1->row, matrix2->col);
	for (int i = 0; i < matrix->row, i++){
		for (int j=0; j<matrix->col; j**) matrix2->data[i][j] = matrix1->data[i][j];
	}
	return matrix2;
}
