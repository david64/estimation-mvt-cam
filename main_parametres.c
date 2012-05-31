
#include <stdlib.h>
#include <stdio.h>
#include "params_mvt.h"


void main(int argc, char* argv[]) {

    int fc = 1;
    sscanf(argv[3], "%i", &fc);
	
    params P = param_mvt(argv[1], argv[2], fc);	
	printf("%le %le %le %le %le %le", P.gamma, P.alpha, P.beta, P.A, P.B, P.C);
	return;
}

