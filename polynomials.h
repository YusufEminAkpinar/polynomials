#ifndef POLYNOMIAL_H
	#define POLYNOMIAL_H
#endif
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define VARS "xyztwpqr"


struct Monomial{
	int dim;
	int *powers;
	float coefficient;
	struct Monomial *next;
	struct Monomial *prev;
};
typedef struct Monomial monom;

monom* createMonomial(int dim, int *pow, float coef);
monom *concatMonom(monom *m1, monom *m2);
monom* constructPolynom(int len, monom *m1, ...);
monom *product(monom *m1, monom* m2);

void freeMonomial(monom *m);
void printPolynom(monom *p);
void tideUp(monom *m);


