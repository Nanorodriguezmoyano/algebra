#include "func.h"


int main(int argc, char **arcgv){
	int con = 1;
	do{
		Matrix *matrix, *cofactor, *aux;
		matrix = populate_matrix_keyboard(8, 8);
		cofactor = fast_inverse(matrix);
		aux = inverse(matrix);
		print_matrix(cofactor);
		printf("\n");
		print_matrix(aux);





		






		
		
		printf("\nDesea continuar: ");
		scanf("%d", &con);
	}while (con == 1);
	
	return 0;
	
}
