

#include <stdlib.h>
#include <stdio.h>
#include "motion_params.h"


int main(int argc, char* argv[]) {

    if(argc<4){
	    printf("Not enough arguments !");
            return 0;
    }

    double fc = 1.0;
    sscanf(argv[3], "%lf", &fc);
	
    params P = motion_params(argv[1], argv[2], fc);	
	printf("%le %le %le %le %le %le", P.gamma, P.alpha, P.beta, P.A, P.B, P.C);
	return EXIT_SUCCESS;
}

