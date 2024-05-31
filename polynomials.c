#include "./polynomials.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define VARS "xyztwpqr"


/*
 * struct Monomial{
 * 	int dim;
 * 	int *powers;
 * };
 * typedef struct Monomial mono;
 * 
 * struct Polynomial{
 * 	Monomial* monom;
 * 	float *coefs;
 * };
 * typedef struct Polynomial poly;
 *
*/ 

struct Polynomial{
	int monomialNumber; //Number of monomials 
	int dim; // Dimension (Number of variables)
	int **powers; // Array of powers 
	float *coefs; // Array of coefficients
};
typedef struct Polynomial poly;

void printPoly(poly *p){
	int dim = p->dim;
	if (dim > 8){
		printf("Dim is too large, quitting\n");
		exit(1);
	}
	for(int i=0; i<p->monomialNumber; i++){
		//if (p->coefs[i] != 1)
		printf("%d", (int)p->coefs[i]);
		for(int j=0; j<dim; j++){
			if (p->powers[i][j] == 1)
				printf("*%c", VARS[j]);
			else if (p->powers[i][j])
				printf("*%c^%d", VARS[j], p->powers[i][j]);
		}
		if(i != p->monomialNumber-1)
			printf(" + ");
		else
			printf("\n");
	}
}

// I malloc'd two times. It's a waste of space.
poly *createPolynom(int monomial, int dim, int **pow, float *coef){
	poly *polynom = (poly *)malloc(sizeof(poly));
	polynom->monomialNumber = monomial;
	polynom->dim = dim;
	polynom->powers = pow;
	polynom->coefs = coef;
	return polynom;
}

void freePolynom(poly *polynom){
	free(polynom->coefs);
	for(int i=0; i<polynom->monomialNumber; i++){
		free(polynom->powers[i]);
	}
	free(polynom->powers);
	free(polynom);
}

//poly *product(poly *p1, poly *p2){

//}

int main(int argc, char **argv){
	(void) argc;
	(void) argv;
	int dimension = 3;
	int monom = 3;
	int **pow = (int **)malloc(sizeof(int) * dimension * monom);
	for(int i=0;i<monom; i++){
		pow[i] = (int *)malloc(sizeof(int) * dimension);
	}
	float *coefs = (float *)malloc(sizeof(float) * monom);
	// xy^2 + 5x^2y + 3y
	// 3x^3y^2 + y^31z^2+12
	pow[0][0] = 3;
	pow[0][1] = 2;
	pow[0][2] = 0;
	pow[1][0] = 0;
	pow[1][1] = 31;
	pow[1][2] = 2;
	pow[2][0] = 0;
	pow[2][1] = 0;
	pow[2][2] = 0;
	coefs[0] = 3;
	coefs[1] = 1;
	coefs[2] = 12;
	poly *P = createPolynom(monom, dimension, pow, coefs);
	//poly P = {
	//	.monomialNumber = 3,
	//	.dim = 2,
	//	//.powers = {{1,2}, {2,1}, {0,1}},
	//	.powers = pow,
	//	.coefs = coefs
	//};
	printPoly(P);
	freePolynom(P);
	return 0;
}

// p1 => deg=3, dim=2, powers = [[1, 2], [1,4], [2,3]]
//poly *multiplication(poly p1, poly p2){
//	return NULL;
//}







