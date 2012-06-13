

/* calc_deltatheta.c */


#include "params_mvt.h"
#include "matrices.h"
#include <math.h>


// Calcul des matrices de la forme quadratique et de la forme lineaire
// associees a la minimisation lors de la k-ieme iteration

// Calcule la matrice elementaire en (x,y) de la forme quadratique
// associee a la minimisation lors de la k-ieme iteration
// a := DF_thetak
// (b, c) := (grad g)(...)
mat M_elem(double x, double y, double a, double b, double c) {

	mat M;
	M.lignes = 7;
	M.colonnes = 7;

	int i,j;

	for(i=0;i<7;i++) {
		for(j=0;j<7;j++)
			M.m[i][j] = 0;
	}

	double e1[6], e2[6];

	e1[0] = x;
	e1[1] = y;
	e1[2] = 1;
	e1[3] = 0;
	e1[4] = x*x;
	e1[5] = x*y;

	e2[0] = y;
	e2[1] = -x;
	e2[2] = 0;
	e2[3] = 1;
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

	M.m[6][6] += 1;
	
	for(i=0;i<7;i++) {
		for(j=0;j<i;j++)
			M.m[i][j] = M.m[j][i];
	}	

	return M;
}


// Calcule le vecteur associe a la forme quadratique elementaire
// en (x,y), associee a la minimisation lors de la k-ieme
// iteration
vect V_elem(double x, double y, double a, double b, double c){

	vect V;
	V.taille = 7;

	V.v[0] = 2*a*(b*x+c*y);
	V.v[1] = 2*a*(-c*x+b*y);
	V.v[2] = 2*a*b;
	V.v[3] = 2*a*c;
	V.v[4] = 2*a*(b*x*x+c*x*y);
	V.v[5] = 2*a*(c*y*y+b*x*y);
	V.v[6] = 2*a;
	
	return V;
}

// matrice de la forme quadratique associee a la minimisation lors de la k-ième
// iteration.
mat mat_forme_q(taille t, double** DF, double** dgdx, double** dgdy, double** u1, double** u2) {

	mat U;
	U.lignes = 7;
	U.colonnes = 7;

	int x,y,i,j;

	for(i=0;i<7;i++) {
		for(j=0;j<7;j++)
			U.m[i][j] = 0.0;
	}	
	
	for(x=MARGE; x<t.h-MARGE; x++) {
		for(y=MARGE; y<t.l-MARGE; y++){
			
			double x_ = x + u1[x][y];
			double y_ = y + u2[x][y];

			
			if(-1<x_ && x_<t.h-1 && -1<y_ && y_<t.l-1) {

				mat U_xy = M_elem(x-t.h/2,y-t.l/2,DF[x][y],interp_pixel(dgdx, x_, y_), interp_pixel(dgdy, x_,y_));

				for(i=0; i<7; i++) {
					for(j=0; j<7; j++)
						U.m[i][j] += U_xy.m[i][j];
				}
			}
		}
	}
	
	return U;
}


// vecteur associe a la forme lineaire associee a la minimisation lors de la k-ieme
// iteration.
vect vect_forme_lin(taille t,  double** DF, double** dgdx, double** dgdy, double** u1, double** u2) {

	vect B;
	B.taille = 7;

	int x,y,i;
	
	for(i=0;i<7;i++)
		B.v[i] = 0.0;

	for(x=MARGE; x<t.h-MARGE; x++){
		for(y=MARGE; y<t.l-MARGE; y++) {
			
			double x_ = x + u1[x][y];
			double y_ = y + u2[x][y];
			
			if(-1<x_ && x_<t.h-1 && -1<y_ && y_<t.l-1){
			
				vect B_xy = V_elem(x-t.h/2,y-t.l/2,DF[x][y],interp_pixel(dgdx, x_, y_), interp_pixel(dgdy, x_, y_));
			
				for(i=0; i<7; i++)
					B.v[i] += B_xy.v[i];
			}
		
		}
	}

	return B;
}

// calcule deltatheta minimisant somme(1/2*w(x,y)*(r_deltatheta(x,y)^2))
vect calc_deltatheta(double** DF, double** dgdx, double** dgdy, double** u1, double** u2, taille t){


	mat U = mat_forme_q(t,DF,dgdx,dgdy,u1,u2);
	vect B = vect_forme_lin(t,DF,dgdx,dgdy,u1,u2);
	mat L = cholesky(U);

	int k;
	for(k=0; k<7; k++)
		B.v[k] *= -0.5;

	return res_tri_sup(L, res_tri_inf(transpose(L), B)); 
}


