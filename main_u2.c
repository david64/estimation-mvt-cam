
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "motion_params.h"

int main(int argc, char* argv[]) {

	    params P;

        sscanf(argv[1], "%le", &P.gamma);
		sscanf(argv[2], "%le", &P.alpha);
		sscanf(argv[3], "%le", &P.beta);
		sscanf(argv[4], "%le", &P.A);
		sscanf(argv[5], "%le", &P.B);
		sscanf(argv[6], "%le", &P.C);
		   
	    double fc;
	    sscanf(argv[7], "%le", &fc);

	    vect theta = reverse_params_conversion(P, fc);

	    size s = image_size(argv[8]);

	    printf("P2\n%i %i\n65000\n", s.w, s.h);

	    int x,y;
	    for (x = 0; x <s.h ; x++)
			for (y = 0 ; y<s.w ; y++)
				printf("%le \n", theta.v[3] - theta.v[1]*(x-s.h/2) + theta.v[0]*(y-s.w/2) + theta.v[4]*(x-s.h/2)*(y-s.w/2) + theta.v[5]*(y-s.w/2)*(y-s.w/2));
				    
	    return EXIT_SUCCESS;
}


