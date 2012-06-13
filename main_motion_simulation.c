
#include <stdio.h>
#include "motion_params.h"

void motion_simulation(char* file, char* out, params p, double fc); 

int main(int argc, char* argv[]) {

	if(argc<9) {
		printf("Not enough arguments \n");
		return 1;
	}

	params P;

	sscanf(argv[3], "%le", &P.gamma);
	sscanf(argv[4], "%le", &P.alpha);
	sscanf(argv[5], "%le", &P.beta);
	sscanf(argv[6], "%le", &P.A);
	sscanf(argv[7], "%le", &P.B);
	sscanf(argv[8], "%le", &P.C);

    double fc = 1.0;
    sscanf(argv[9], "%lf", &fc);

    motion_simulation(argv[1], argv[2], P, fc);

	return EXIT_SUCCESS;
}

