
#include <stdlib.h>
#include <stdio.h>
#include "motion_params.h"


void main(int argc, char* argv[]) {

    int fc = 1;
    sscanf(argv[3], "%i", &fc);
	
    params P = motion_params(argv[1], argv[2], fc);	
	printf("%le %le %le %le %le %le", P.gamma, P.alpha, P.beta, P.A, P.B, P.C);
	return;
}

