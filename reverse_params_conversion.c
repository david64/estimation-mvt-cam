

#include <math.h>
#include "motion_simulation.h"


vect reverse_params_conversion(params p) {
	
	// Convert (theta, etc) into (a1, etc)
	vect theta;
	theta.v[0] = -p.C;
	theta.v[1] = p.beta;
	theta.v[2] = fc*(p.A - (p.alpha)*sin(p.gamma));
	theta.v[3] = fc*(p.B + (p.alpha)*cos(p.gamma));
	theta.v[4] = -(p.alpha)*sin(p.gamma)/fc;
	theta.v[5] = (p.alpha)*cos(p.gamma)/fc;
	return theta;
}

