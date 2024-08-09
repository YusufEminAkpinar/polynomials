#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#endif
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#define VARS "xyztwpqr"


struct Monomial{
	int dim;
	int *powers;
	float coefficient;
	struct Monomial *next;
	struct Monomial *prev;
};

typedef struct Monomial monom;

monom *createMonomial(int dim, int *pow, float coef);

void constructPolynom(int len, monom *m1, ...);

void printPolynom(monom *p);





