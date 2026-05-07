#include "func.h"


int main(int argc, char **arcgv){
	int con = 1;
	do{
		Matrix *matrix, *inversa;
		matrix = populate_matrix_keyboard(2,2);
		inversa = inverse(matrix);
		print_matrix(inversa);
		printf("\nDesea continuar: ");
		scanf("%d", &con);
	}while (con == 1);
	
	return 0;
}
