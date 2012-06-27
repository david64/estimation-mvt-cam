/* Camera motion estimation, by Léo Girardin and David Lafontaine
    Copyright (C) 2012 Léo Girardin and David Lafontaine

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


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

