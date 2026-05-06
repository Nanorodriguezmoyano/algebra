#include <stdio.h>
//#include <unitstd.h>
#include <stdlib.h>
#include <string.h>

// matrix[row][col]
typedef struct Matrix {
  int col;
  int row;
  float **data;
} Matrix;


Matrix *copy_matrix(const Matrix *matrix1);
void set_elem(int row, int col, float value, Matrix *matrix);
Matrix *init_matrix(int row, int col);
void print_matrix(const Matrix *matrix);
Matrix *populate_matrix(int row, int col,const float *data);
void free_matrix(Matrix *matrix);
Matrix *add_matrix(Matrix *matrix1, Matrix *matrix2);
Matrix *scalar_multiplication(float val, Matrix *matrix);
Matrix *transpose(Matrix *matrix);
Matrix *matrix_multiplication(const Matrix *matrix1, const Matrix *matrix2);
Matrix *gaussian_elimination(const Matrix *matrix);
void interchange_row(Matrix *matrix, int row1, int row2);
float determinant(const Matrix *matrix);
Matrix *concatenate_matrix(const Matrix *matrix1, const Matrix *matrix2);
Matrix *populate_matrix_keyboard(int row, int col);
void mitosis_matrix(const Matrix *matrix, Matrix **result1, Matrix **result2, int i);
float cofactor(int row, int col, Matrix *matrix);
Matrix *identity(int dim);
