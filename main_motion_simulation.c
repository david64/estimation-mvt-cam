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

