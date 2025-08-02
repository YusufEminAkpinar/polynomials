
all: polynomial

polynomial: polynomials.c
	cc polynomials.c -ggdb -Wall -Wextra -pedantic -o ./out/poly
