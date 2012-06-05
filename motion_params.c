

/* motion_params.c */


#include <stdlib.h>
#include "motion_params.h"
#include "matrix.h"
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

params motion_params(char* file_f, char* file_g, int fc) {

	double **DF, **dgdx, **dgdy, **u1, **u2;
	int **f, **g;

	int i, k, x, y;

	size s = image_size(file_f);
	
	// allocation
	DF   = malloc(s.h * sizeof(double*));
	dgdy = malloc(s.h * sizeof(double*));
	dgdx = malloc(s.h * sizeof(double*));
	u1   = malloc(s.h * sizeof(double*));
	u2   = malloc(s.h * sizeof(double*));
   	f    = malloc(s.h * sizeof(int*));
	g    = malloc(s.h * sizeof(int*));
	
	for(i = 0; i<s.h; i++) {
		DF[i]   = malloc(s.w * sizeof(double));
		dgdy[i] = malloc(s.w * sizeof(double));
		dgdx[i] = malloc(s.w * sizeof(double));
		u1[i]   = malloc(s.w * sizeof(double));
		u2[i]   = malloc(s.w * sizeof(double));
		f[i] 	= malloc(s.w * sizeof(int));
		g[i] 	= malloc(s.w * sizeof(int));
	}

	// Image loading	
	load_image(f, file_f);
	load_image(g, file_g);

	// g gradient
	comp_grad(dgdx, dgdy, g, s);

	// We use a vector instead of an array to store theta to be able to make computation
	vect theta;
	theta.size = 7;
	
	// Initializations	
	for(i=0; i<7; i++)
		theta.v[i] = 0;

	for(x=0;x<s.h;x++) {
		for(y=0;y<s.w;y++){
			DF[x][y]  = 0.0;
			u1[x][y]  = 0.0;
			u2[x][y]  = 0.0;
		}			
	}

    vect deltas[N];
    int stop = 0;

	// Incremental scheme to compute theta
	for(k=0; k<N && (!stop); k++){
		
		comp_utheta(u1, u2, theta, s);
		comp_DFtheta(DF, u1, u2, f, g, theta.v[6], s);
		vect deltatheta = comp_deltatheta(DF, dgdx, dgdy, u1, u2, s);

		
		for(i=0; i<7; i++) {
			theta.v[i] += (deltatheta.v[i]);
		}

        deltas[k] = deltatheta;

        stop = stop_criterion(deltas, k);
	}

#ifndef STAT_STUDY

//    printf("Iteration number : %i \n", k);

#endif

#ifdef STAT_STUDY

    // For statistical study on octave
    
    char stats[N*1000] = "A = [";

    int j;
    for(j=0; j<k; j++) {

        for(i=0; i<7; i++){

            char q[30] = "";
            sprintf(q, "%f", (deltas[j]).v[i]);
            strcat(stats, q);
            strcat(stats, " ");
        }

        if(j<k-1)
            strcat(stats, " ; ");
    }

    strcat(stats, "];");
    printf(stats);
    

#endif

	// deallocation
	for(i = 0; i<s.h; i++) {
		free(DF[i]);
		free(dgdy[i]);
		free(dgdx[i]);
		free(u1[i]);
		free(u2[i]);
		free(f[i]);
		free(g[i]);
	}

	free(DF);
	free(dgdy);
	free(dgdx);
	free(u1);
	free(u2);
	free(f);
	free(g);
	
	// Result (after conversion of a1,a2,c1,c2,q1,q2,xi into interpretable parameters)
	return params_conversion(theta, fc);
}

