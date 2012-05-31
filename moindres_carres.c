
/* moindres_carres.c */

#include "moindres_carres.h"
#include <stdio.h>
#include <math.h>

/* Calcule la matrice de la forme quadratique associée 
au problème aux moindres carrés que l'on souhaite résoudre */
mat mat_forme_quadratique(int taille_x, int taille_y) {

	mat Q;
	Q.lignes = 6;
	Q.colonnes = 6;
	
	int x,y,i,j;
	
	for(i=0;i<6;i++){
		for(j=0;j<6;j++)
			Q.m[i][j] = 0.0;
	}	

	for(x=0;x<taille_x;x++) {
		for(y=0;y<taille_y;y++) {

			Q.m[0][0] += (x*x + y*y);
			Q.m[0][2] += (x);
			Q.m[0][3] += (y);
			Q.m[0][4] += (x*x*x + x*y*y);
			Q.m[0][5] += (y*y*y + y*x*x);				
			
			Q.m[1][1] += (x*x + y*y);
			Q.m[1][2] += (y);
			Q.m[1][3] += (-x);

			Q.m[2][0] += (x);
			Q.m[2][1] += (y);
			Q.m[2][2] += (1.0);
			Q.m[2][4] += (x*x);
			Q.m[2][5] += (x*y);

			Q.m[3][0] += (y);
			Q.m[3][1] += (-x);
			Q.m[3][3] += (1.0);
			Q.m[3][4] += (x*y);
			Q.m[3][5] += (y*y);

			Q.m[4][0] += (x*x*x + x*y*y);
			Q.m[4][2] += (x*x);
			Q.m[4][3] += (x*y);
			Q.m[4][4] += (x*x*x*x + x*x * y*y);
			Q.m[4][5] += (x*x*x*y + y*y*y*x);
			 
			Q.m[5][0] += (x*x*y + y*y*y);
			Q.m[5][2] += (x*y);
			Q.m[5][3] += (y*y);
			Q.m[5][4] += (x*x*x*y+y*y*y*x);
			Q.m[5][5] += (y*y*y*y + x*x*y*y);
		}
	}
	
	return Q;
}

/* Calcule le vecteur de la forme linéaire associée au problème aux moindres carrés que
l'on souhaite résoudre */
vect vect_forme_lineaire(int taille_x, int taille_y, double** flot_x, double** flot_y) {

	vect l;
	l.taille = 6;

	int x,y,i;

	for(i=0;i<6;i++)
		l.v[i] = 0.0;

	for(x=0;x<taille_x;x++){
		for(y=0;y<taille_y; y++) {

			double a = flot_x[x][y];
			double b = flot_y[x][y];

		  	l.v[0] +=  (a*x + b*y);
			l.v[1] +=  (a*y - b*x);
			l.v[2] +=  (a);
			l.v[3] +=  (b);
			l.v[4] +=  (a*x*x + b*x*y);
			l.v[5] +=  (b*y*y + a*x*y); 
		}
	}
	
	for(i=0;i<6;i++)
		l.v[i] *= (-2.0);
	
	return l;
}

/* Donne une approximation des paramètres du mouvement de la caméra à partir du flot optique,
par moindre carrés par rapport aux paramètres */
params params_moindres_carres(int taille_x, int taille_y, double** flot_x, double** flot_y){

	mat U = mat_forme_quadratique(taille_x, taille_y);
	vect B = vect_forme_lineaire(taille_x, taille_y, flot_x, flot_y);
        
	mat L = cholesky(U);
 	
	int i;
	for(i=0;i<6;i++)
		B.v[i] *= (-0.5);

	vect C = res_tri_sup(L, res_tri_inf(transpose(L), B));
	params p = {C.v[0], C.v[1], C.v[2], C.v[3], C.v[4], C.v[5]};     	
	
	return p;
}

