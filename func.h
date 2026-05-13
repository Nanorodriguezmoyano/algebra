#include <stdio.h>
//#include <unitstd.h>
#include <stdlib.h>
#include <string.h>

// matrix[row][col]
typedef struct Matrix {
  int col;
  int row;
  double **data;
} Matrix;


Matrix *copy_matrix(const Matrix *matrix1);
void set_elem(int row, int col, double value, Matrix *matrix);
Matrix *init_matrix(int row, int col);
void print_matrix(const Matrix *matrix);
Matrix *populate_matrix(int row, int col,const double *data);
void free_matrix(Matrix *matrix);
Matrix *add_matrix(Matrix *matrix1, Matrix *matrix2);
Matrix *scalar_multiplication(double val, Matrix *matrix);
Matrix *transpose(Matrix *matrix);
Matrix *matrix_multiplication(const Matrix *matrix1, const Matrix *matrix2);
Matrix *gaussian_elimination(const Matrix *matrix);
void interchange_row(Matrix *matrix, int row1, int row2);
double determinant(const Matrix *matrix);
Matrix *concatenate_matrix(const Matrix *matrix1, const Matrix *matrix2);
Matrix *populate_matrix_keyboard(int row, int col);
void mitosis_matrix(const Matrix *matrix, Matrix **result1, Matrix **result2, int i);
double cofactor(int row, int col, Matrix *matrix);
Matrix *identity_matrix(int dim);
Matrix *inverse(const Matrix *matrix);
Matrix *gauss_jordan_elimination(const Matrix *matrix);
Matrix *cofactor_matrix(Matrix *matrix);
Matrix *adjoint_matrix(Matrix *matrix);
Matrix *fast_inverse(Matrix *inverse);
int range(const Matrix *matrix);
