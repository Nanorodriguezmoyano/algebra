#include "func.h"


int main(int argc, char **arcgv){
	int con = 1;
	do{
		double data[900];
		for (int i = 0; i < 900; i++){
			data[i] = 2*(i) % 7 + i + 31 * i % 11+ 47.5464845456 * i / 23;
		}

		Matrix *matrix, *cofactor, *aux;
		matrix = populate_matrix(30, 30, data);
		cofactor = fast_inverse(matrix);
		aux = matrix_multiplication(matrix, cofactor);
		print_matrix(cofactor);
		printf("\n");
		print_matrix(aux);





		






		
		
		printf("\nDesea continuar: ");
		scanf("%d", &con);
	}while (con == 1);
	
	return 0;
	
}
