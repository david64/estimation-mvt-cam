

/* comp_deltatheta.c */


#include "motion_params.h"
#include "matrix.h"
#include <math.h>


// Computation of the matrices of the quadratic form and of the linear form associated to the minimization during the k-th iteration

// Compute the elementary matrix in (x,y) of the quadratic form
// a := DF_thetak
// (b, c) := (grad g)(...)
mat M_elem(double x, double y, double a, double b, double c) {

	mat M;
	M.rows = 7;
	M.columns = 7;

	int i,j;

	for(i=0;i<7;i++) {
		for(j=0;j<7;j++)
			M.m[i][j] = 0.0;
	}

	double e1[6], e2[6];

	e1[0] = x;
	e1[1] = y;
	e1[2] = 1.0;
	e1[3] = 0.0;
	e1[4] = x*x;
	e1[5] = x*y;

	e2[0] = y;
	e2[1] = -x;
	e2[2] = 0.0;
	e2[3] = 1.0;
	e2[4] = x*y;
	e2[5] = y*y;

	for(i=0;i<6;i++){
		for(j=i;j<6;j++)
			M.m[i][j] = b*b*e1[i]*e1[j] + c*c*e2[i]*e2[j];
	}

	M.m[0][0] += (2*b*c*x*y);
	M.m[0][1] += (b*c*(-x*x+y*y));
	M.m[0][2] += (b*c*y);
	M.m[0][3] += (b*c*x);
	M.m[0][4] += (2*b*c*x*x*y);
	M.m[0][5] += (2*b*c*x*y*y);	
	M.m[0][6] += (b*x+c*y);
	
	M.m[1][1] += (-2*b*c*x*y);
	M.m[1][2] += (-b*c*x);
	M.m[1][3] += (b*c*y);
	M.m[1][4] += (b*c*(-x*x*x+x*y*y));
	M.m[1][5] += (b*c*(y*y*y-x*x*y));
	M.m[1][6] += (b*y-c*x);

//	M.m[2][2] += 0;
	M.m[2][3] += (b*c);
	M.m[2][4] += (b*c*x*y);
	M.m[2][5] += (b*c*y*y);
	M.m[2][6] += b;

//	M.m[3][3] += 0;
	M.m[3][4] += (b*c*x*x);
	M.m[3][5] += (b*c*x*y);
	M.m[3][6] += c;

    M.m[4][4] += (2*b*c*(x*x*x*y));
    M.m[4][5] += (2*b*c*x*x*y*y);
	M.m[4][6] += (b*x*x+c*x*y);
	
    M.m[5][5] += (2*b*c*x*y*y*y);
    M.m[5][6] += (b*x*y+c*y*y);

	M.m[6][6] += 1.0;
	
	for(i=0;i<7;i++) {
		for(j=0;j<i;j++)
			M.m[i][j] = M.m[j][i];
	}	

	return M;
}


// Compute the elementary vector in (x,y) of the quadratic form
vect V_elem(double x, double y, double a, double b, double c){

	vect V;
	V.size = 7;

	V.v[0] = 2*a*(b*x+c*y);
	V.v[1] = 2*a*(-c*x+b*y);
	V.v[2] = 2*a*b;
	V.v[3] = 2*a*c;
	V.v[4] = 2*a*(b*x*x+c*x*y);
	V.v[5] = 2*a*(c*y*y+b*x*y);
	V.v[6] = 2*a;
	
	return V;
}

// Matrix of the quadratic form
mat mat_quad_form(size s, double** DF, double** dgdx, double** dgdy, double** u1, double** u2) {

	mat U;
	U.rows = 7;
	U.columns = 7;

	int x,y,i,j;

	for(i=0;i<7;i++) {
		for(j=0;j<7;j++)
			U.m[i][j] = 0.0;
	}	

    int m = margin(s);

	for(x=m; x<s.h-m; x++) {
		for(y=m; y<s.w-m; y++){
			
			double x_ = x + u1[x][y];
			double y_ = y + u2[x][y];

			
			if(-1<x_ && x_<s.h-1 && -1<y_ && y_<s.w-1) {

				mat U_xy = M_elem(x-s.h/2,y-s.w/2,DF[x][y],px_interp(dgdx, x_, y_), px_interp(dgdy, x_,y_));

				for(i=0; i<7; i++) {
					for(j=0; j<7; j++)
						U.m[i][j] += U_xy.m[i][j];
				}
			}
		}
	}
	
	return U;
}


// Vector of the linear form
vect vect_lin_form(size s,  double** DF, double** dgdx, double** dgdy, double** u1, double** u2) {

	vect B;
	B.size = 7;

	int x,y,i;
	
	for(i=0;i<7;i++)
		B.v[i] = 0.0;

    int m = margin(s);

	for(x=m; x<s.h-m; x++){
		for(y=m; y<s.w-m; y++) {
			
			double x_ = x + u1[x][y];
			double y_ = y + u2[x][y];
			
			if(-1<x_ && x_<s.h-1 && -1<y_ && y_<s.w-1){
			
				vect B_xy = V_elem(x-s.h/2,y-s.w/2,DF[x][y],px_interp(dgdx, x_, y_), px_interp(dgdy, x_, y_));
			
				for(i=0; i<7; i++)
					B.v[i] += B_xy.v[i];
			}
		
		}
	}

	return B;
}

// Compute deltatheta which minimizes sum(1/2*w(x,y)*(r_deltatheta(x,y)^2))
vect comp_deltatheta(double** DF, double** dgdx, double** dgdy, double** u1, double** u2, size s){


	mat U = mat_quad_form(s,DF,dgdx,dgdy,u1,u2);
	vect B = vect_lin_form(s,DF,dgdx,dgdy,u1,u2);
	mat L = cholesky(U);

	int k;
	for(k=0; k<7; k++)
		B.v[k] *= -0.5;

	return res_upper_tri(L, res_lower_tri(transpose(L), B)); 
}


