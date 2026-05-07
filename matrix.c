
#include "func.h"
#define PRUEBA printf("a\n");
// matrix[row][col]

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
		printf("ERROR print_matrix: sos un wachin no se puede imprimir\n");
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

//Para hacer la funcion mas versatil, la funcion ya recibe el array de numeros, y es trabajo de otra funcion como consigue el array.
//Se asume que se recibe la cantidad adecuada de valores. Si se recibe mas, los ulimos los desechará, y si recibe menos, completará con cero.
Matrix *populate_matrix(int row, int col, const float *data) {
	float elem;
	Matrix *matrix1;
	matrix1 = init_matrix(row, col);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			elem = *(data ++);	
			matrix1->data[i][j] = elem;
		}
	}
	return matrix1;
}

//para directamente llenar una desde el teclado.
Matrix *populate_matrix_keyboard(int row, int col){
	Matrix *matrix; 
	float *data;
	float *aux;
	data = calloc(col*row, sizeof(float));
	aux = data;
	printf("Mete los valores wachin\n");
	for (int i = 0; i< row; i++){
		for (int j=0; j<col; j++){
			printf("Posicion %d %d: ", i + 1, j + 1);
			scanf("%f", aux++);
		}		
	}
	matrix = populate_matrix(row, col, data);
	free((void*)data);
	return matrix;

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
		printf("ERROR add_matrix: sos un wachin como vas a sumar matrices de diferente dimension. "
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
		printf("ERROR matrix_multiplication: fijate las dimensiones de las matrices wachin\n");
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
	int pivot_pos[2] = {0,0}; 
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
		printf("ERROR determinant: Estas queriedo hacer un determinante de una cuadrada wachin\n"); //Ayuda para debuggear nomas
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
Matrix *concatenate_matrix(const Matrix *matrix1, const Matrix *matrix2){
	if (matrix1->row - matrix2->row) {
		printf("ERROR CONCATENATE: No coinciden las filas\n");
	}
	Matrix *result = init_matrix(matrix1->row, 2*matrix1->col);
	for (int i = 0; i < matrix1->row; i++) {
		for (int j = 0; j < matrix1->col; j++){
			result->data[i][j] = matrix1->data[i][j];
			if (j < matrix2->col){
			       	result->data[i][j+matrix1->col] = matrix2->data[i][j];
			}
		}	
		if (matrix1->col < matrix2->col) {
				for (int j = (matrix1->col) *2; j < matrix1->col + matrix2->col; j++) result->data[i][j] = matrix2->data[i][j - matrix1->col]; 
			}
	}
			
	return result;
	
       	
}
//recibe punteros a la funciones 
//recibe las dos matrices donde va a guardar las matrices separadas, y la cantidad de columnas de la primera.
void mitosis_matrix(const Matrix *matrix, Matrix **result1, Matrix **result2, int col1)
{
	if (col1 >= matrix->col) {
		printf("ERROR MITOSIS: columnas de la segunda matriz, menor o igual a 0\n");
		return;
	}
	int col2 = matrix->col - col1; 
	float *data1,  *data2, *aux1, *aux2;
	
	data1 = calloc(matrix->row * col1, sizeof(float));
	data2 = calloc(matrix->row * col2, sizeof(float));
	aux1 = data1;
	aux2 = data2;

	//llene los vecctores de data
	for(int i = 0; i < matrix->row; i++){
		for (int j = 0; j < col1; j++){
			*(aux1++) = matrix->data[i][j]; 
		}
		for (int j = col1; j < matrix->col; j++){
			*(aux2++) = matrix->data[i][j];
		}
	}
	*result1 = populate_matrix(matrix->row, col1, data1);
	*result2 = populate_matrix(matrix->row, col2, data2);
	return;
}

Matrix *identity_matrix(int dim){
	Matrix *matrix;
	float *data;
	data = calloc(dim * dim, sizeof(float));
	
	for (int i = 0; i < dim; i ++){
		data[i * (dim + 1)] = 1;
	}	
	
	matrix = populate_matrix(dim, dim, data);
	free((void *) data);
	return matrix;
}
Matrix *inverse(const Matrix *matrix){
	if (!determinant(matrix)){
		printf("ERROR Inverse: matriz no tiene inversa\n");
		return NULL;
	}
	if (matrix->col - matrix->row){
		printf("Error Inverse: quiere calcular inversa de una no cuadrada\n");
		return NULL;
	}

	int dim = matrix->row;
	float pivot;
	Matrix *identity, *concatenate,*aux, *aux_right,*inverse, *concatenate_aux;

	identity = identity_matrix(dim);
	concatenate = concatenate_matrix(matrix, identity);

	concatenate_aux = gaussian_elimination(concatenate);

	free_matrix(concatenate);
	free_matrix(identity);

	mitosis_matrix(concatenate_aux, &aux, &identity, dim);

	free_matrix(concatenate_aux);
	aux_right =  transpose(aux);
	inverse = transpose(identity);

	free_matrix(aux);
	free_matrix(identity);

	concatenate = concatenate_matrix(aux_right, inverse);
	concatenate_aux = gaussian_elimination(concatenate);

	free_matrix(concatenate);
	free_matrix(aux_right);
	free_matrix(inverse);
	
	mitosis_matrix(concatenate_aux, &aux_right, &inverse, dim);
	//print_matrix(aux_right);
	//print_matrix(inverse);
	for (int i = 0; i< dim; i++){
		pivot = aux_right->data[i][i];
		for (int j = 0; j < dim; j++){
			inverse->data[i][j] *= (1/pivot);
		}
	}
	free_matrix(aux_right);
	free_matrix(concatenate_aux);

	return inverse;
}

float cofactor(int row, int col, Matrix *matrix){
  float *data = calloc((matrix->row -1)*(matrix->row -1), sizeof(float));
  float cofactor;
  int k = 0;

  for (int i = 0; i < matrix->row; i++){
    for (int j = 0; j < matrix->col; j++){
      if (i != row && j != col){
        data[k++] = matrix->data[i][j];
      }
    }
  }

  cofactor = determinant(populate_matrix((matrix->row)-1, (matrix->col)-1, data));
  if (cofactor != 0 && (row + col + 2) % 2 != 0){
   cofactor = cofactor * (-1); 
  }

  return cofactor;
}
