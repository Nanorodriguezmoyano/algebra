#include "func.h"

// matrix[row][col]
typedef struct Matrix {
  int col;
  int row;
  float **data;
} Matrix;

int main(int argc, char *argv[]) {
	Matrix *matrix;
	Matrix *matrix2;
	// Matrix *matrix3;
	// Matrix *matrix4;
	matrix = populate_matrix(3, 3);
	print_matrix(matrix);
	printf("\n");
	// matrix2 = populate_matrix(3, 2);
	// print_matrix(matrix2);
	// matrix3 = add_matrix(matrix, matrix2);
	// // print_matrix(matrix3);
	// // print_matrix(scalar_multiplication(4, matrix));
	// matrix4 = matrix_multiplication(matrix, matrix2);
	// print_matrix(matrix3);
	// print_matrix(matrix4);
	matrix2 = gaussian_elimination(matrix);
	printf("\n\n\n");
	print_matrix(matrix2);
	printf("%.4f\n", determinant(matrix)); 
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
				printf("%4.6f ", matrix->data[i][j]);
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


Matrix *gaussian_elimination(const Matrix *matrix){
	/*
	 *La idea de esta funcion es la siguiente. 
	 Primero se selecciona un pivot y a partir de ahí tenemos 2 casos:
	 1. si el pivot no es cero simplemente se generan ceros debajo
	 2. Si no es empiezo a buscar un pivot que no sea cero.
	 Si encuentr: Intercambio las filas
	 Si no, muev el pivot a la derecha y repito.
	 */

	Matrix *result = copy_matrix(matrix);
	int pivot_pos[2] = {0,0}, pivto_pos_aux[2]; 	
	float pivot, aux, factor; 

	while((pivot_pos[0] < matrix->row && pivot_pos[1] < matrix->col))
	{
		pivot = result->data[pivot_pos[0]][pivot_pos[1]];
		if (pivot) { //entra solamente si el pivot no es cero
			for (int i = pivot_pos[0] + 1; i < matrix->row; i ++){

				aux = result->data[i][pivot_pos[1]];//valor a convertir en cero
				if (aux == 0) continue;
				factor = aux / pivot; 
				for (int j = pivot_pos[1]; j < matrix->col; j ++){
					result->data[i][j] -= (result->data[pivot_pos[0]][j] * factor);

				}
			}
			pivot_pos[0] ++;
			pivot_pos[1] ++;

		}
		else{
			aux = 0;
			for (int i = pivot_pos[0] + 1; i < matrix->row; i ++){
				aux = result->data[i][pivot_pos[1]];//posible nuevo pivot
				if(aux != 0){
					interchange_row(result, pivot_pos[0], i);
					break;	
				} 
			}
			if (aux == 0) pivot_pos[1] ++;
		}
	}
	return result;
}

void interchange_row(Matrix *matrix, int row1, int row2) {
	float *aux = calloc (matrix->col, sizeof(float));
	memcpy(aux,  matrix->data[row1], sizeof(float) * matrix->col);
	for(int i = 0; i < matrix->col; i++){
		if (aux[i]) aux[i]*=-1;
	}
	memcpy(matrix->data[row1], matrix->data[row2], sizeof(float)* matrix->col);
	memcpy(matrix->data[row2], aux, sizeof(float) *matrix->col);
	free(aux);
}
// void lu_decomposition(const Matrix *matrix){
//   Matrix *l = init_matrix(matrix->row, matrix->col);
//   Matrix *u = copy_matrix(matrix);
// }
float determinant(const Matrix *matrix) {
	if (matrix->row - matrix->col) {
		printf("Estas queriedo hacer un determinante de una cuadrada wachin\n"); //Ayuda para debuggear nomas
		return 0;
	}
	Matrix * triangular = gaussian_elimination(matrix);
	float result = 1, value;

	for (int i = 0; i < matrix->row; i++){
		value = triangular->data[i][i];
		if (!value) return 0;
		result *= value;
	}
	free_matrix(triangular);
	return result;
}
