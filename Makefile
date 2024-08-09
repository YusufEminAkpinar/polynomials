
all: polynomial

polynomial: polynomials.c
	cc polynomials.c -Wall -Wextra -pedantic -o ./out/poly
