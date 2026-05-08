#include "func.h"


int main(int argc, char **arcgv){
	int con = 1;
	do{
		Matrix *matrix, *inversa, *aux;
		matrix = populate_matrix_keyboard(2,2);
		inversa = inverse(matrix);
		print_matrix(inversa);	
		aux = matrix_multiplication(matrix, inversa);
		printf("\n\n");
		print_matrix(aux);






		






		
		
		printf("\nDesea continuar: ");
		scanf("%d", &con);
	}while (con == 1);
	
	return 0;
	
}
