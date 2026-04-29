#include <stdio.h>
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
Matrix *populate_matrix(int row, int col);
void free_matrix(Matrix *matrix);
Matrix *add_matrix(Matrix *matrix1, Matrix *matrix2);
Matrix *scalar_multiplication(float val, Matrix *matrix);
Matrix *transpose(Matrix *matrix);
Matrix *matrix_multiplication(const Matrix *matrix1, const Matrix *matrix2);
int determinant(Matrix *matrix);
Matrix *gaussian_elimination(const Matrix *matrix);
void interchange_row(Matrix *matrix, int row1, int row2);

int main(int argc, char *argv[]) {
  Matrix *matrix;
  Matrix *matrix2;
  // Matrix *matrix3;
  // Matrix *matrix4;
  matrix = populate_matrix(3, 3);
  print_matrix(matrix);
  // matrix2 = populate_matrix(3, 2);
  // print_matrix(matrix2);
  // matrix3 = add_matrix(matrix, matrix2);
  // // print_matrix(matrix3);
  // // print_matrix(scalar_multiplication(4, matrix));
  // matrix4 = matrix_multiplication(matrix, matrix2);
  // print_matrix(matrix3);
  // print_matrix(matrix4);
  matrix2 = gaussian_elimination(matrix);
  print_matrix(matrix2);
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
  if (matrix == NULL) {
    printf("sos un wachin no se puede imprimir\n");
  } else {
    for (int i = 0; i < matrix->row; i++) {
      for (int j = 0; j < matrix->col; j++)
        printf("%4.0f ", matrix->data[i][j]);
      printf("\n");
    }
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
    return matrix3;
  } else {
    printf("sos un wachin como vas a sumar matrices de diferente dimension. "
           "kabum\n");
    return NULL;
  }
}

Matrix *scalar_multiplication(float val, Matrix *matrix1) {
  Matrix *matrix2 = init_matrix(matrix1->row, matrix1->col);
  for (int i = 0; i < matrix1->row; i++) {
    for (int j = 0; j < matrix1->col; j++) {
      matrix2->data[i][j] = (matrix1->data[i][j]) * val;
    }
  }
  return matrix2;
}

Matrix *transpose(Matrix *matrix) {
  Matrix *transposed;
  transposed = init_matrix(matrix->col, matrix->row);
  for (int i = 0; i < matrix->row; i++) {
    for (int j = 0; j < matrix->col; j++)
      transposed->data[j][i] = matrix->data[i][j];
  }
  return transposed;
}

Matrix *matrix_multiplication(const Matrix *matrix1, const Matrix *matrix2) {
  Matrix *result = init_matrix(matrix1->row, matrix2->col);
  if (matrix1->row != matrix2->col) {
    printf("fijate las dimensiones de las matrices wachin\n");
    return NULL;
  } else {
    for (int i = 0; i < matrix1->row; i++) {
      for (int j = 0; j < matrix2->col; j++) {
        for (int k = 0; k < matrix1->col; k++) {
          result->data[i][j] += matrix1->data[i][k] * matrix2->data[k][j];
        }
      }
    }
    return result;
  }
}

// ARREGLAR
Matrix *gaussian_elimination(const Matrix *matrix) {
  Matrix *result = copy_matrix(matrix);
  int pivot_pos[2] = {0, 0};
  float pivot = result->data[pivot_pos[0]][pivot_pos[1]];
  float aux;
  while (pivot_pos[0] < matrix->row) {
    pivot = result->data[pivot_pos[0]][pivot_pos[0]];
    if (pivot != 0) {
      for (int i = pivot_pos[0] + 1; i < result->col; i++) {
        aux = result->data[i][pivot_pos[0]];
        for (int j = 0; j < matrix->col; j++) {
          result->data[i][j] -= (result->data[pivot_pos[0]][j] * (aux / pivot));
        }
      }
    }
  }
  return result;
}

void interchange_row(Matrix *matrix, int row1, int row2) {
  float *aux = matrix->data[row1];
  memcpy(matrix->data[row1], matrix->data[row2], sizeof(float));
  memcpy(matrix->data[row2], aux, sizeof(float));
  free(aux);
}
// void lu_decomposition(const Matrix *matrix){
//   Matrix *l = init_matrix(matrix->row, matrix->col);
//   Matrix *u = copy_matrix(matrix);
// }
