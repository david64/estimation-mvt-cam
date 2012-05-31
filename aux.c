

/* aux.c */
/* Contains all auxiliary functions */


#include "motion_params.h"
#include <math.h>

#ifndef M_PI
	#define M_PI 3.14
#endif

// Compute DF_theta, write the result into DF
void comp_DFtheta (double** DF, double** u1, double** u2, int** f, int** g, double xi, size s){

	int x,y;

	for(x=MARGIN; x<s.h-MARGIN; x++) {
		for(y=MARGIN; y<s.w-MARGIN; y++){

            double x_ = x + u1[x][y];
			double y_ = y + u2[x][y];
			
			if(-1<x_ && x_<s.h-1 && -1<y_ && y_<s.w-1)
				DF[x][y] = int_px_interp(g, x_, y_) - f[x][y] + xi;
		}	
	}
}

// Compute the discrete gradient of g. Write the result in dgdx and dgdy.
void comp_grad(double** dgdx, double** dgdy, int** g, size s) {

	int x,y;
	for (x = 1 ; x < s.h-1 ; x++) {
	
		for (y = 1 ; y < s.w-1 ; y++) {
	
			dgdx[x][y] = (g[x+1][y] - g[x-1][y])/2;
			dgdy[x][y] = (g[x][y+1] - g[x][y-1])/2;
		}
	}
}


// Compute u_theta given motion parameters theta. Write the result in u1 and u2
void comp_utheta(double** u1, double** u2, vect theta, taille t) {

	int x,y;
	for (x = MARGIN ; x < s.h-MARGIN ; x++) {
	
		for (y = MARGIN ; y < s.w-MARGIN ; y++){ 
		
			u1[x][y] = theta.v[2] + theta.v[0]*(x-s.h/2) + theta.v[1]*(y-s.w/2) + theta.v[4]*(x-s.h/2)*(x-s.h/2) + theta.v[5]*(x-s.h/2)*(y-s.w/2);
			u2[x][y] = theta.v[3] - theta.v[1]*(x-s.h/2) + theta.v[0]*(y-s.w/2) + theta.v[4]*(x-s.h/2)*(y-s.w/2) + theta.v[5]*(y-s.w/2)*(y-s.w/2);
		}
	}
}

// Convert motion parameters (a1, a2, c1, c2, q1, q2, xi) into (gamma, beta, alpha, A, B, C)
params params_conversion(vect theta, int fc) {

	// Recall : theta = (a_1, a_2, c_1, c_2, q_1, q_2, xi)
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

// Interpolate the value of t[x_][y_], where x_ and y_ are not integers
double px_interp(double** t, double x_, double y_){

	int x = x_;
	int y = y_;
	
	return  (x_- x)*(y_-y)*t[x+1][y+1] + (x_-x)*(1-y_+y)*t[x+1][y] + (1-x_+x)*(y_-y)*t[x][y+1] + (1-x_+x)*(1-y_+y)*t[x][y];

}

// Same function with integers values in t
int int_px_interp(int** t, double x_, double y_){

	int x = x_;
	int y = y_;
	
	return  (x_- x)*(y_-y)*t[x+1][y+1] + (x_-x)*(1-y_+y)*t[x+1][y] + (1-x_+x)*(y_-y)*t[x][y+1] + (1-x_+x)*(1-y_+y)*t[x][y];

}

// Stopping criterion, found empirically
int stop_criterion(vect deltas[N], int i) {

   if(i<10) 
        return 0;

    double s = 0;
    int j;

    for(j=i-10;j<=i;j++)
        s += (deltas[j]).v[2];

    return (fabs(s) <= fabs((deltas[i]).v[2] - (deltas[i-1]).v[2])/2);

}

