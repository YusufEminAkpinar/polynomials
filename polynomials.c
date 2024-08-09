#include "./polynomials.h"


/*
* struct Monomial{
* 	int dim;
* 	int *powers;
* 	float coefficient;
* 	struct Monomial *next;
* 	struct Monomial *prev;
* };
*
* typedef struct Monomial monom;
*/


monom *createMonomial(int dim, int *pow, float coef){
	monom *monomial = (monom *)malloc(sizeof(monom));
	monomial->dim = dim;
	monomial->powers = pow;
	monomial->coefficient = coef;
	monomial->next = NULL;
	monomial->prev = NULL;
	return monomial;
}


void constructPolynom(int len, monom *m1, ...){
	va_list ap;
	va_start(ap, m1);
	monom *nextMon;
	monom *tmp = m1;
	for(int i=0; i<len-1; i++){
		nextMon = va_arg(ap, monom*);
		tmp->next = nextMon;
		nextMon->prev = tmp;
		tmp = nextMon;
	}
}


void printPolynom(monom *p){
	int dim = p->dim;
	if (dim > 8){
		printf("Dim is too large, quitting\n");
		exit(1);
	}
	monom *tmp = p;

    if (tmp->coefficient == 0) tmp=tmp->next;
	if (tmp != NULL) {
		printf("%.1f", tmp->coefficient);
		for(int i=0; i<dim; i++){
			if (tmp->powers[i] == 1)
				printf("*%c", VARS[i]);
			else if (tmp->powers[i])
				printf("*%c^%d ", VARS[i], tmp->powers[i]);
		}
		tmp = tmp->next;
	}
	while (tmp != NULL){
        if (tmp->coefficient == 0) tmp=tmp->next;
		//Print monomial here
		printf("+ %.1f", tmp->coefficient);
		for(int i=0; i<dim; i++){
			if (tmp->powers[i] == 1)
				printf("*%c", VARS[i]);
			else if (tmp->powers[i])
				printf("*%c^%d ", VARS[i], tmp->powers[i]);
		}
		tmp = tmp->next;
	}
	printf("\n");
}


// Sum up the monomials with same exponent.
void tideUp(monom *m){
    monom *tmp = m;
    int isEqual;
    while(m->next != NULL){
        tmp = m->next;
        while(tmp != NULL){
            isEqual = 0;
            for (int i = 0; i < m->dim; i++)
                if (m->powers[i] == tmp->powers[i]) isEqual++;
            if(isEqual == m->dim){
                m->coefficient += tmp->coefficient;
                if (tmp->next != NULL){
                    tmp->prev->next = tmp->next;
                    tmp->next->prev = tmp->prev; //Do not deref NULL pointer
                }else {
                    tmp->prev->next = NULL;
                    free(tmp->powers);
                    free(tmp);
                    return;
                }
                free(tmp->powers);
                free(tmp);
            }
            tmp = tmp->next;
        }
        m = m->next;
    }
}


monom *product(monom *m1, monom* m2){
	monom *prod;
    int dim = m1->dim, *power = malloc(sizeof(int) * dim), k = 1;
    memset(power, 0, sizeof(int) * dim);
    prod = createMonomial(dim, power, 0);

    monom *tmp, *previous;
    for(monom *tmp1 = m1; tmp1 != NULL; tmp1=tmp1->next){
        for (monom *tmp2 = m2; tmp2 != NULL; tmp2=tmp2->next){
            for (int i=0; i<dim; i++) power[i] = tmp1->powers[i] + tmp2->powers[i];

            tmp = createMonomial(dim, power, tmp1->coefficient * tmp2->coefficient);
            memset(power, 0, sizeof(int) * dim);
            if (k){
                prod = tmp;
                previous = prod;
                k--;
            }
            printPolynom(tmp);

            previous->next = tmp;
            tmp->prev = previous;
            
            previous = tmp;
        }
    }
	
    return prod;
}


int main(int argc, char **argv){
	(void) argc;
	(void) argv;
	int dim = 2;
	int *pow1 = malloc(sizeof(int) * dim);
	pow1[0] = 1; pow1[1] = 2;
	int *pow2 = malloc(sizeof(int) * dim);
	pow2[0] = 1; pow2[1] = 3;
	int *pow3 = malloc(sizeof(int) * dim);
	pow3[0] = 0; pow3[1] = 3;
	int *pow4 = malloc(sizeof(int) * dim);
	pow4[0] = 2; pow4[1] = 3;
	int coef1 = 2;
	int coef2 = 5;
	int coef3 = 1;
	int coef4 = 3;
	monom* m1 = createMonomial(dim, pow1, coef1);
	monom* m2 = createMonomial(dim, pow2, coef2);
	monom* m3 = createMonomial(dim, pow3, coef3);
	monom* m4 = createMonomial(dim, pow4, coef4);
	constructPolynom(2, m1, m2);
	constructPolynom(2, m3, m4);
    printf("first one is: ");
	printPolynom(m1);
    
    printf("second one is: ");
    printPolynom(m3);

    printf("Product is: ");
    monom *prod = product(m1, m3);
    printPolynom(prod);

	return 0;
}

