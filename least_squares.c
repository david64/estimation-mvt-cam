
/* least_squares.c */

#include "least_squares.h"
#include <stdio.h>
#include <math.h>

/* Compute the matrix of the quadratic form associated to the least squares problem that we have to solve */
mat least_squares_quad_form(int size_x, int size_y) {

	mat Q;
	Q.rows = 6;
	Q.columns = 6;
	
	int x,y,i,j;
	
	for(i=0;i<6;i++){
		for(j=0;j<6;j++)
			Q.m[i][j] = 0.0;
	}	

	for(x=0;x<size_x;x++) {
		for(y=0;y<size_y;y++) {

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

/* Compute the vector of the linear form associated to the least squares problem that we have to solve */
vect least_squares_lin(int size_x, int size_y, double** flow_x, double** flow_y) {

	vect l;
	l.size = 6;

	int x,y,i;

	for(i=0;i<6;i++)
		l.v[i] = 0.0;

	for(x=0;x<size_x;x++){
		for(y=0;y<size_y; y++) {

			double a = flow_x[x][y];
			double b = flow_y[x][y];

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

// Compute an approximation of the motion parameters using the optical flow
params least_squares_params(int size_x, int size_y, double** flow_x, double** flow_y){

	mat U = least_squares_quad(size_x, size_y);
	vect B = least_squares_lin(size_xsize_y, flow_x, flow_y);
        
	mat L = cholesky(U);
 	
	int i;
	for(i=0;i<6;i++)
		B.v[i] *= (-0.5);

	vect C = res_upper_tri(L, res_lower_tri(transpose(L), B));
	params p = {C.v[0], C.v[1], C.v[2], C.v[3], C.v[4], C.v[5]};     	
	
	return p;
}

