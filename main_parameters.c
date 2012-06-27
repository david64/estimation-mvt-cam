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

