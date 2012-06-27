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

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "motion_params.h"

int main(int argc, char* argv[]) {

    if(argc<9){
	    printf("Not enough arguments !");
            return 0;
    }

    params P;

	sscanf(argv[1], "%le", &P.gamma);
	sscanf(argv[2], "%le", &P.alpha);
	sscanf(argv[3], "%le", &P.beta);
	sscanf(argv[4], "%le", &P.A);
	sscanf(argv[5], "%le", &P.B);
	sscanf(argv[6], "%le", &P.C);
		   
	double fc = 1.0;
	sscanf(argv[7], "%lf", &fc);

	vect theta = reverse_params_conversion(P, fc);
	size s = image_size(argv[8]);
			        
	printf("P2\n%i %i\n65000\n", s.w, s.h);

	int x,y;
	 for (x = 0 ; x<s.h ; x++)
	    for (y = 0 ; y<s.w ; y++)
		    printf("%le \n", theta.v[2] + theta.v[0]*(x-s.h/2) + theta.v[1]*(y-s.w/2) + theta.v[4]*(x-s.h/2)*(x-s.h/2) + theta.v[5]*(x-s.h/2)*(y-s.w/2));
				        
	return EXIT_SUCCESS;
}

