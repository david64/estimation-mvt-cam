

#include "simul_mvt.h"
#include <stdio.h>

void main(int argc, char* argv[]) {

	if(argc<8) {
		printf("Pas assez d'arguments \n");
		return;
	}

	params P;

	sscanf(argv[3], "%le", &P.gamma);
	sscanf(argv[4], "%le", &P.alpha);
	sscanf(argv[5], "%le", &P.beta);
	sscanf(argv[6], "%le", &P.A);
	sscanf(argv[7], "%le", &P.B);
	sscanf(argv[8], "%le", &P.C);

	printf("%le - %le - %le - %le - %le - %le\n", P.gamma, P.alpha, P.beta, P.A, P.B, P.C);

    simul_mvt(argv[1], argv[2], P);

	return;
}
