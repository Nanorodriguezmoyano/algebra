#include "function.h"
#define ESPACIO printf("\n\n");


int main(int argc, char **arcgv){
	Matrix *matrix1;
	Vector *vector1, *vector2, *vector3;	
	double dot_product, data1[] = {1,0,0}, data2[] = {0,1,0};

	vector1 = populate_vector(3, data1);
	vector2 = populate_vector(3, data2);
	vector3 = cross_product_3_dim_vector(vector1, vector2);

	print_vector(vector3);
	return 0;
}
