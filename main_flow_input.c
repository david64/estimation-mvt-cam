
#include <stdlib.h>
#include <stdio.h>
#include "least_squares.h"
#include "flow_input.h"
#include "motion_params.h"

int main(int argc, char* argv[]) {

    if (argc<4) {
        printf("Not enough parameters");
        return;
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

   int fc = 1;
   sscanf(argv[3], "%i", &fc);
   
   vect vp = least_squares_params(s.w, s.h, u1, u2);
   params P = params_conversion(vp, fc);

   printf("%le %le %le %le %le %le", P.gamma, P.alpha, P.beta, P.A, P.B, P.C);

   for(i=0;i<s.w;i++){
           free(u1[i]);
           free(u2[i]); 
   }
    
   free(u1);
   free(u2);

   return 1;
}

