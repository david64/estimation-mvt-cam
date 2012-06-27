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
#include "least_squares.h"
#include "flow_input.h"
#include "motion_params.h"

int main(int argc, char* argv[]) {

    if (argc<4) {
        printf("Not enough parameters");
        return 1;
    }

   size s = flow_size(argv[1]);

   double **u1, **u2;
   
   int i;

   u1 = malloc(sizeof(double*)*s.h);
   u2 = malloc(sizeof(double*)*s.h);

   for(i=0;i<s.h;i++){
           u1[i] = malloc(sizeof(double)*s.w);
           u2[i] = malloc(sizeof(double)*s.w);
   }

   read_flow(u1, s, argv[1]);
   read_flow(u2, s, argv[2]);

   double fc = 1.0;
   sscanf(argv[3], "%lf", &fc);
   
   vect vp = least_squares_params(s, u1, u2);
   params P = params_conversion(vp, fc);

   printf("%le %le %le %le %le %le", P.gamma, P.alpha, P.beta, P.A, P.B, P.C);

   for(i=0;i<s.h;i++){
           free(u1[i]);
           free(u2[i]); 
   }
    
   free(u1);
   free(u2);

   return EXIT_SUCCESS;
}

