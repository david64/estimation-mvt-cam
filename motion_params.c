

/* params_mvt.c */


#include <stdlib.h>
#include "params_mvt.h"
#include "matrices.h"
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

params param_mvt(char* file_f, char* file_g, int fc) {

	double **DF, **dgdx, **dgdy, **u1, **u2;
	int **f, **g;

	int i, k, x, y;

	taille t = taille_image(file_f);
	
	// allocation
	DF   = malloc(t.h * sizeof(double*));
	dgdy = malloc(t.h * sizeof(double*));
	dgdx = malloc(t.h * sizeof(double*));
	u1   = malloc(t.h * sizeof(double*));
	u2   = malloc(t.h * sizeof(double*));
    f    = malloc(t.h * sizeof(int*));
	g    = malloc(t.h * sizeof(int*));
	
	for(i = 0; i<t.h; i++) {
		DF[i]   = malloc(t.l * sizeof(double));
		dgdy[i] = malloc(t.l * sizeof(double));
		dgdx[i] = malloc(t.l * sizeof(double));
		u1[i]   = malloc(t.l * sizeof(double));
		u2[i]   = malloc(t.l * sizeof(double));
		f[i] 	= malloc(t.l * sizeof(int));
		g[i] 	= malloc(t.l * sizeof(int));
	}

	// Chargement des images	
	charger_image(f, file_f);
	charger_image(g, file_g);

	// calcul du gradient de g
	calc_grad(dgdx, dgdy, g, t);

	// On utilise un vecteur plutot qu'un tableau pour stocker
	// theta car on va faire du calcul matriciel
	vect theta;
	theta.taille = 7;
	
	// Initialisations	
	for(i=0; i<7; i++)
		theta.v[i] = 0;

	for(x=0;x<t.h;x++) {
		for(y=0;y<t.l;y++){
			DF[x][y]  = 0.0;
			u1[x][y]  = 0.0;
			u2[x][y]  = 0.0;
		}			
	}

    vect deltas[N];
    int arret = 0;

	// schema incremental pour calculer theta
	for(k=0; k<N && (!arret); k++){
		
		calc_utheta(u1, u2, theta, t);
		calc_DFtheta(DF, u1, u2, f, g, theta.v[6], t);
		vect deltatheta = calc_deltatheta(DF, dgdx, dgdy, u1, u2, t);

		
		for(i=0; i<7; i++) {
			theta.v[i] += (deltatheta.v[i]);
		}

        deltas[k] = deltatheta;

        arret = critere_arret(deltas, k);
	}

#ifndef ETUDE_STAT

//    printf("Nombre d'iterations : %i \n", k);

#endif

#ifdef ETUDE_STAT

    // Pour l'etude statistique sur Matlab
    
    char stats[N*1000] = "A = [";

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

	// desallocation
	for(i = 0; i<t.h; i++) {
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
	
	// resultat (on renvoie la conversion de (a1,a2,c1,c2,q1,q2,xi)
	// en parametres de camera interpretables
	return conversion_params(theta, fc);
}

