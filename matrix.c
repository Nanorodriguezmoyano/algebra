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

int main(int argc, char *argv[]) {
  int co, elem, fil;
  Matrix *matrix;
  Matrix *matrix2;
  Matrix *matrix3;
  matrix = populate_matrix(atoi(argv[1]), atoi(argv[2]));
  print_matrix(matrix);
  matrix2 = populate_matrix(atoi(argv[1]), 3);
  print_matrix(matrix2);
  matrix3 = add_matrix(matrix, matrix2);
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
  for (int i = 0; i < matrix->row; i++) {
    for (int j = 0; j < matrix->col; j++)
      printf("%.0f ", matrix->data[i][j]);
    printf("\n");
  }
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
