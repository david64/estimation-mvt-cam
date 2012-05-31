

/* au1.c */
/* Regroupe les fonctions : calc_r, calc_DFtheta, */


#include "params_mvt.h"
#include <math.h>

#ifndef M_PI
	#define M_PI 3.14
#endif

// Calcule DF_theta. Ecrit le resultat dans DF
void calc_DFtheta (double** DF, double** u1, double** u2, int** f, int** g, double xi, taille t){

	int x,y;

	for(x=MARGE; x<t.h-MARGE; x++) {
		for(y=MARGE; y<t.l-MARGE; y++){

            double x_ = x + u1[x][y];
			double y_ = y + u2[x][y];
			
			if(-1<x_ && x_<t.h-1 && -1<y_ && y_<t.l-1)
				DF[x][y] = interp_pixeli(g, x_, y_) - f[x][y] + xi;
		}	
	}
}

// Calcule le gradient discret de g. Ecrit le resultat dans dgdx et dgdy 
void calc_grad(double** dgdx, double** dgdy, int** g, taille t) {

	int x,y;
	for (x = 1 ; x < t.h-1 ; x++) {
	
		for (y = 1 ; y < t.l-1 ; y++) {
	
			dgdx[x][y] = (g[x+1][y] - g[x-1][y])/2;
			dgdy[x][y] = (g[x][y+1] - g[x][y-1])/2;
		}
	}
}


// Calcule u_theta a partir des parametres du mouvement theta
void calc_utheta(double** u1, double** u2, vect theta, taille t) {

	int x,y;
	for (x = MARGE ; x < t.h-MARGE ; x++) {
	
		for (y = MARGE ; y < t.l-MARGE ; y++){ 
		
			u1[x][y] = theta.v[2] + theta.v[0]*(x-t.h/2) + theta.v[1]*(y-t.l/2) + theta.v[4]*(x-t.h/2)*(x-t.h/2) + theta.v[5]*(x-t.h/2)*(y-t.l/2);
			u2[x][y] = theta.v[3] - theta.v[1]*(x-t.h/2) + theta.v[0]*(y-t.l/2) + theta.v[4]*(x-t.h/2)*(y-t.l/2) + theta.v[5]*(y-t.l/2)*(y-t.l/2);
		}
	}
}

// Convertit les parametres du mouvement (a1, a2, c1, c2, q1, q2, xi) en
// (gamma, beta, alpha, A, B, C)
params conversion_params(vect theta, int fc) {

	// Rappel : theta = (a_1, a_2, c_1, c_2, q_1, q_2, xi)
	params p;
	p.alpha = fc*sqrt(theta.v[4]*theta.v[4] + theta.v[5]*theta.v[5]);
	p.beta = theta.v[1];

	if (theta.v[5] > 0.0)
		p.gamma = -atan(theta.v[4]/theta.v[5]);
	else if (theta.v[5] < 0.0)
		p.gamma = -atan(theta.v[4]/theta.v[5]) + M_PI;
	else if (theta.v[4] > 0.0)
		p.gamma = M_PI/2;
	else if (theta.v[4] < 0.0)
		p.gamma = -M_PI/2;

	p.A = theta.v[2]/fc + (p.alpha)*sin(p.gamma);
	p.B = theta.v[3]/fc - (p.alpha)*cos(p.gamma);
	p.C = -theta.v[0];
	return p;
}

double interp_pixel(double** t, double x_, double y_){

	int x = x_;
	int y = y_;
	
	return  (x_- x)*(y_-y)*t[x+1][y+1] + (x_-x)*(1-y_+y)*t[x+1][y] + (1-x_+x)*(y_-y)*t[x][y+1] + (1-x_+x)*(1-y_+y)*t[x][y];

}

int interp_pixeli(int** t, double x_, double y_){

	int x = x_;
	int y = y_;
	
	return  (x_- x)*(y_-y)*t[x+1][y+1] + (x_-x)*(1-y_+y)*t[x+1][y] + (1-x_+x)*(y_-y)*t[x][y+1] + (1-x_+x)*(1-y_+y)*t[x][y];

}

/*
double max_derniers_ecarts_moy(double norme[N1], int k) {

	double moy, max;
	int i;
	
	for(i=k;i>=k-NB_ECART;i--){
		moy += norme[i];
	}

	moy = moy/NB_ECART;

	max = fabs(norme[k] - moy);

	for(i=k-1;i>=k-NB_ECART;i--){
		if(fabs(norme[i]-moy) > max)
			max = fabs(norme[i] - moy);
	}

	return max;
}

*/

int critere_arret(vect deltas[N], int i) {

   if(i<10) 
        return 0;

    double s = 0;
    int j;

    for(j=i-10;j<=i;j++)
        s += (deltas[j]).v[2];

    return (fabs(s) <= fabs((deltas[i]).v[2] - (deltas[i-1]).v[2])/2);

}

