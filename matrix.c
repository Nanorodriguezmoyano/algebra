#include <stdio.h>
#include <stdlib.h>

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
Matrix *populate_matrix(int row, int col);
void free_matrix(Matrix *matrix);
Matrix *add_matrix(Matrix *matrix1, Matrix *matrix2);
Matrix *scalar_multiplication(float val, Matrix *matrix);
Matrix *transpose(Matrix *matrix);
Matrix *matrix_multiplication(Matrix *matrix1, Matrix *matrix2);

int main(int argc, char *argv[]) {
  Matrix *matrix;
  Matrix *matrix2;
  Matrix *matrix3;
  // Matrix *matrix4;
  matrix = populate_matrix(atoi(argv[1]), atoi(argv[2]));
  print_matrix(matrix);
  matrix2 = populate_matrix(atoi(argv[2]), atoi(argv[1]));
  print_matrix(matrix2);
  // matrix3 = add_matrix(matrix, matrix2);
  // print_matrix(matrix3);
  // print_matrix(scalar_multiplication(4, matrix));
  matrix3 = matrix_multiplication(matrix, matrix2);
  print_matrix(matrix3);
}

Matrix *init_matrix(int row, int col) {
  Matrix *matrix;
  matrix = calloc(1, sizeof(Matrix));
  matrix->col = col;
  matrix->row = row;
  matrix->data = calloc(matrix->row, sizeof(float *));
  for (int i = 0; i < row; i++) {
    matrix->data[i] = calloc(col, sizeof(float));
  }
  return matrix;
}

void print_matrix(const Matrix *matrix) {
  for (int i = 0; i < matrix->col; i++) printf("----");
  printf("\n");
  for (int i = 0; i < matrix->row; i++) {
    printf("|");
    for (int j = 0; j < matrix->col; j++)
      printf("%4.0f ", matrix->data[i][j]);
    printf("|");
    printf("\n");
    for (int i = 0; i < matrix->col; i++) printf("----");
    printf("\n");
  }
  for (int i = 0; i < (matrix->col + 2); i++) printf("-");
}

void set_elem(int row, int col, float value, Matrix *matrix) {
  matrix->data[row - 1][col - 1] = value;
  return;
}

Matrix *copy_matrix(const Matrix *matrix1) {
  Matrix *matrix2;
  matrix2 = init_matrix(matrix1->row, matrix1->col);
  for (int i = 0; i < matrix1->row; i++) {
    for (int j = 0; j < matrix1->col; j++)
      matrix2->data[i][j] = matrix1->data[i][j];
  }
  return matrix2;
}

Matrix *populate_matrix(int row, int col) {
  float elem;
  Matrix *matrix1;
  matrix1 = init_matrix(row, col);
  printf("mete los valores wachin\n");
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      scanf("%f", &elem);
      matrix1->data[i][j] = elem;
    }
  }
  return matrix1;
}

void free_matrix(Matrix *matrix) {
  if (matrix != NULL) {
    if (matrix->data != NULL) {
      for (int i = 0; i < matrix->row; i++) {
        if (matrix->data[i])
          free((void *)matrix->data[i]);
      }
      free((void *)matrix->data);
    }
    free((void *)matrix);
  }
}

Matrix *add_matrix(Matrix *matrix1, Matrix *matrix2) {
  Matrix *matrix3;
  matrix3 = init_matrix(matrix1->row, matrix1->col);
  if (matrix1->row == matrix2->col && matrix1->col == matrix2->col) {
    for (int i = 0; i < matrix1->row; i++) {
      for (int j = 0; j < matrix1->col; j++) {
        matrix3->data[i][j] = matrix1->data[i][j] + matrix2->data[i][j];
      }
    }
  } else {
    printf("sos un wachin como vas a sumar matrices de diferente dimension. "
           "kabum\n");
  }
  return matrix3;
}

Matrix *scalar_multiplication(float val, Matrix *matrix1){
  Matrix *matrix2 = init_matrix(matrix1->row, matrix1->col);
  for (int i = 0; i < matrix1->row; i++) {
    for (int j = 0; j < matrix1->col; j++){
      matrix2->data[i][j] = (matrix1->data[i][j]) * val;
    }
  }
  return matrix2;
}

Matrix *transpose(Matrix *matrix){
  Matrix *transposed;
  transposed = init_matrix(matrix->col, matrix->row);
  for (int i = 0; i < matrix->row; i++) {
    for (int j = 0; j < matrix->col; j++)
      transposed->data[j][i] = matrix->data[i][j];
  }
  return transposed;
}

Matrix *matrix_multiplication(Matrix *matrix1, Matrix *matrix2){
  Matrix *result = init_matrix(matrix1->row, matrix2->col);
  if (matrix1->row != matrix2->col){
    printf("fijate las dimensiones de las matrices wachin\n");
  } else {
    for (int i = 0; i < matrix1->row; i++){
      for (int j = 0; j < matrix2->col; j++){
        for (int k = 0; k < matrix1->col; k++){
          result->data[i][j] += matrix1->data[i][k] * matrix2->data[k][j];
        }
      }
    }
  }
  return result;
}

// void lu_decomposition(const Matrix *matrix){
//   Matrix *l = init_matrix(matrix->row, matrix->col);
//   Matrix *u = copy_matrix(matrix);
//
//
// }
