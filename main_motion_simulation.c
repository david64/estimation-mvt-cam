

#include "motion_simulation.h"
#include <stdio.h>

int main(int argc, char* argv[]) {

	if(argc<8) {
		printf("Not enough arguments \n");
		return;
	}

	params P;

	sscanf(argv[3], "%le", &P.gamma);
	sscanf(argv[4], "%le", &P.alpha);
	sscanf(argv[5], "%le", &P.beta);
	sscanf(argv[6], "%le", &P.A);
	sscanf(argv[7], "%le", &P.B);
	sscanf(argv[8], "%le", &P.C);

//	printf("%le - %le - %le - %le - %le - %le\n", P.gamma, P.alpha, P.beta, P.A, P.B, P.C);

    motion_simulation(argv[1], argv[2], P);

	return EXIT_SUCCESS;
}

