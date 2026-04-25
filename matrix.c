#include <stdio.h>
#include <stdlib.h>

//matrix[row][col]
typedef struct Matrix{
	int col;
	int row;
	float **data;
}Matrix;

Matrix *copy_matrix(const Matrix *matrix1);
Matrix *init_matrix(int row, int col);
void print_matrix(const Matrix* matrix);
Matrix *set_elem(int row, int col, float value,const Matrix* matrix);

int main(int argc, char *argv[])
{
	int co, elem, fil;
	Matrix * matrix;
	Matrix * matrix2;
	matrix = init_matrix(atoi(argv[1]),atoi(argv[2]));
	print_matrix(matrix);
	matrix2 = copy_matrix(matrix);
	printf("Set row, and col to modify: ");
	scanf("%d%d%d", &fil, &co, &elem);
	matrix = set_elem(fil, co, elem, matrix);
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
	for(int i = 0; i < matrix->row; i++ )
	{
		for(int j=0; j<matrix->col; j++) printf("%.0f ", matrix->data[i][j]);
		printf("\n");
	}
}

Matrix *set_elem(int row, int col, float value, const Matrix* matrix)
{
	Matrix * matrix2;
	matrix2 = copy_matrix(matrix);
	matrix2->data[row-1][col-1] = value;
	return matrix2;
}
Matrix *copy_matrix(const Matrix *matrix1)
{
	Matrix *matrix2;
	matrix2 = init_matrix(matrix1->row, matrix1->col);
	for (int i = 0; i < matrix1->row; i++){
		for (int j=0; j<matrix1->col; j++) matrix2->data[i][j] = matrix1->data[i][j];
	}
	return matrix2;
}
