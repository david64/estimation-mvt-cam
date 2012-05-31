

#include <math.h>
#include "simul_mvt.h"


vect conversion_params_inverse(params p) {

	// Ce programme renvoie (a1,â€¦ , q2) Ã  partir de (theta, alpha,â€¦ ,C)
	// C'est la fonction inverse de conversion_params
	vect theta;
	theta.v[0] = -p.C;
	theta.v[1] = p.beta;
	theta.v[2] = fc*(p.A - (p.alpha)*sin(p.gamma));
	theta.v[3] = fc*(p.B + (p.alpha)*cos(p.gamma));
	theta.v[4] = -(p.alpha)*sin(p.gamma)/fc;
	theta.v[5] = (p.alpha)*cos(p.gamma)/fc;
	return theta;
}

