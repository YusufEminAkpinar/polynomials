#include "./polynomials.h"

/*
 * PROBLEMS:
 * every monomial should be used once, since we pass by ref, links (next and
 * prev) will be broken. Try to maybe use copies inside constructPolynom or concatMonom.
 *
 */

// struct Monomial{
// 	int dim;
// 	int *powers;
// 	float coefficient;
// 	struct Monomial *next;
// 	struct Monomial *prev;
// };
//
// typedef struct Monomial monom;


monom *createMonomial(int dim, int *pow, float coef) {

	if (dim < 0 || pow == NULL) return NULL;
	monom *monomial = (monom *)malloc(sizeof(monom));

	if (!monomial) return NULL;
	monomial->dim = dim;

    monomial->powers = (int *)malloc(sizeof(int) * dim);
    if (!monomial->powers) {
        free(monomial);
        return NULL;
    }
    
    for (int i = 0; i < dim; i++) {
        monomial->powers[i] = pow[i];
    }

	monomial->coefficient = coef;
	monomial->next = NULL;
	monomial->prev = NULL;
	return monomial;
}


void freeMonomial(monom *m) {
	while (m) {
		monom *tmp = m;
		m = m->next;
		if (tmp) {
			free(tmp->powers);
			free(tmp);
		}
	}
}


monom *concatMonom(monom *m1, monom *m2) {
	if (!m1) return m2;
	if (!m2) return m1;
	monom *curr = m1;
	// Last monom (since it is not DLL)
	while (curr->next) {
		curr = curr->next;
	}
	curr->next = m2;
	m2->prev = curr;

	return m1;
}


monom* constructPolynom(int len, monom *m1, ...) {
	va_list ap;
	va_start(ap, m1);
	monom *nextMon = NULL;
	monom *res = m1;
	for(int i=0; i<len-1; i++){
		nextMon = va_arg(ap, monom*);
		if (!res) {
			printf("Res is NULL\n");
			exit(1);
			res = nextMon;
			continue;
		}
		if (!nextMon) {
			printf("NextMon is NULL\n");
			exit(1);
			continue;
		}
		res = concatMonom(res, nextMon);
	}
	return res;
}


void printPolynom(monom *p) {
	if (!p) return;

	if (p->dim > 8){
		printf("Dim is too large, quitting\n");
		exit(1);
	}

	monom *tmp = p;

    if (tmp->coefficient == 0) tmp=tmp->next;
	if (tmp != NULL) {
		printf("%.1f", tmp->coefficient);
		for(int i=0; i<p->dim; i++){
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
		for(int i=0; i<p->dim; i++){
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
void tideUp(monom *m) {
	if (!m) return;

    monom *curr = m;

	bool isEqual = true;
    while(curr) {
        monom *tmp = curr->next;
        while(tmp) {
			monom *nx = tmp->next;
			isEqual = true;
            for (int i = 0; i < m->dim; i++)
                if (curr->powers[i] != tmp->powers[i]) {
					isEqual = false;
					break;
				}
			if (isEqual) {
				curr->coefficient += tmp->coefficient;
				monom *pr = tmp->prev;
				if (pr) pr->next = nx;
				// Do not deref NULL pointer
				if (nx) nx->prev = pr;

				free(tmp->powers);
				free(tmp);
			}
            
            tmp = nx;
        }
        curr = curr->next;
    }

}


monom *product(monom *m1, monom* m2) {
	if (!m1 || !m2) return NULL;

	monom *prod = NULL;
    int dim = m1->dim;

	// Loop through monomials of m1 and m2
    for(monom *tmp1 = m1; tmp1 != NULL; tmp1 = tmp1->next) {
        for (monom *tmp2 = m2; tmp2 != NULL; tmp2 = tmp2->next) {
			int *prodPowers = malloc(sizeof(int) * dim);
			if (!prodPowers) {
				freeMonomial(prod);
				printf("Powers array can not be allocated.\n");
				return NULL;

			}

			for (int i=0; i<dim; i++) prodPowers[i] = tmp1->powers[i] + tmp2->powers[i];
			float prodCoeff = tmp1->coefficient * tmp2->coefficient;
			
			monom *prodMonom = createMonomial(dim, prodPowers, prodCoeff);
			free(prodPowers);
			
			prod = concatMonom(prod, prodMonom);
		}
	}

	return prod;
}


int main(int argc, char **argv) {
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
	pow4[0] = 0; pow4[1] = 3;
	int coef1 = 2;
	int coef2 = 5;
	int coef3 = 1;
	int coef4 = 3;
	monom* m1 = createMonomial(dim, pow1, coef1);
	monom* m2 = createMonomial(dim, pow2, coef2);
	monom* m3 = createMonomial(dim, pow3, coef3);
	monom* m4 = createMonomial(dim, pow4, coef4);

	m1 = constructPolynom(2, m1, m2);
	m3 = constructPolynom(2, m3, m4);
    printf("first one is: ");
	printPolynom(m1);
    
    printf("second one is: ");
    printPolynom(m3);

    printf("Product is: ");
    monom *prod = product(m1, m3);
    printPolynom(prod);

	tideUp(prod);
	printf("After tiding up: ");
	printPolynom(prod);

	freeMonomial(m1);
	freeMonomial(m3);
	freeMonomial(prod);

	free(pow1);
	free(pow2);
	free(pow3);
	free(pow4);

	return 0;
}
