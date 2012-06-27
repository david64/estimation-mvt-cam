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

/* matrix.c */
/* Some matrix manipulation functions */

#include <math.h>
#include <stdio.h>

#include "matrix.h"

double sum_p(mat M, int a, int b) {

	double r = 0.0;
	int k;
	for(k=0; k<M.rows; k++)
		r = r + M.m[k][a]*M.m[k][b];
	return r;
}

/* Cholesky matrix of a symmetric positive-definite matrix */
mat cholesky(mat M) {

	mat L;
	
	if(M.rows != M.columns)
		return L;

	int n = M.rows;
	L.rows = n;
	L.columns = n;

	int i,j;

	for(i=0;i<n;i++) {
		for(j=0;j<n;j++)
			L.m[i][j] = 0.0;
	}

	for(i=0;i<n;i++){
		L.m[i][i] = sqrt(M.m[i][i] - sum_p(L, i, i));
		for(j=i+1;j<n;j++)
			L.m[i][j] = (M.m[i][j] - sum_p(L, j, i))/L.m[i][i];
	}
	return L;
}

/* Print a matrix */
void print_mat(mat M){

	printf("\n");

	int i,j;
	for(i=0;i<M.rows;i++) {
		for(j=0;j<M.columns;j++) {
			printf("%e ",M.m[i][j]);
		}
		printf("\n");
	}
}

/* Transpose a matrix */
mat transpose(mat M) {

	mat T;
	T.rows = M.columns;
	T.columns = M.rows;

	int i,j;
	for(i=0;i<M.rows;i++) {
		for(j=0;j<M.columns;j++){
			T.m[i][j] = M.m[j][i];
		}
	}
	return T;
}

/* Naive product of two matrices */
mat product_mm(mat A, mat B){

	mat M;

	if(A.columns != B.rows)
		return M;
	
	M.rows = A.rows;
	M.columns = B.columns;
	
	int i,j,k;

	for(i=0;i<A.rows;i++){
		for(j=0;j<B.columns;j++){
			M.m[i][j] = 0.0;
			for(k=0;k<A.columns;k++)
				M.m[i][j] = M.m[i][j] + A.m[i][k]*B.m[k][j];
		}
	}
	
	return M;
}

/* Product of a matrix by a vector */
vect product_mv(mat A, vect X) {

	vect Y;

	if(A.columns != X.size)
		return Y;
	
	Y.size = A.rows;

	int i,k;
	for(k=0;k<A.rows;k++) {
		Y.v[k] = 0.0;
		for(i=0;i<A.columns;i++)
			Y.v[k] = Y.v[k] + A.m[k][i]*X.v[i];		
	}
	
	return Y;
}

/* Solve PX = B where P is upper triangulary */
vect res_upper_tri(mat P, vect B) {

	vect X;
	
	if(P.rows != B.size || P.rows != P.columns)
		return X;

	int i,k;
	
	X.size = P.rows;

	for(i=B.size-1;i>=0;i--) {
		double s = 0.0;
		for(k=i+1;k<B.size;k++)
			s = s + P.m[i][k] * X.v[k];
		X.v[i] = (B.v[i]-s)/P.m[i][i];	
	}

	return X;
}

/* Solve PX = B where P is lower triangulary */
vect res_lower_tri(mat P, vect B) {

	vect X;
	
	if(P.rows != B.size || P.rows != P.columns)
		return X;

	int i,k;
	
	X.size = P.rows;
	
	for(i=0;i<B.size;i++) {
		double s = 0.0;
		for(k=0;k<i;k++)
			s = s + P.m[i][k] * X.v[k];
		X.v[i] = (B.v[i]-s)/P.m[i][i];	
	}

	return X;
}

/* Solve the expected invertible system MX = Y by Gaussian elimination */
vect gauss(mat M, vect Y) {

	int n = Y.size;
	int k,i,j;
	
	for(k=0;k<n-1;k++){
		
		// Find pivot l
	 	int l=k;
		double max = fabs(M.m[k][k]);
	
		for(i=k+1; i<n; i++){
			if(max < fabs(M.m[i][k])){
				max = fabs(M.m[i][k]);
				l = i;
			}
		}	
	
		if(l>k) {
			// Switching of lines l and k  
			double tmp;
  			for (j=k; j<n; j++) {
    				tmp = M.m[k][j];
    				M.m[k][j] = M.m[l][j];
    				M.m[l][j] = tmp;
  			}
  			tmp = Y.v[k];
  			Y.v[k] = Y.v[l];
  			Y.v[l] = tmp;
		}
		
		// Then pivoting
		for (i=k+1; i<n; i++) {

    			double q = M.m[i][k]/M.m[k][k];
    			Y.v[i] = Y.v[i] - q * Y.v[k];
    			for (j=k+1; j<n; j++) {
      				M.m[i][j] = M.m[i][j] - q * M.m[k][j];
    			}
		}

	}
	
	// Now the system is upper triangulary, so invert it
	return res_upper_tri(M, Y);
}


vect sum_vv(vect u, vect v) {

    vect w;

    if(u.size != v.size)
        return w;

    w.size = u.size;

    int i;

    for(i=0; i<v.size; i++)
        w.v[i] = u.v[i] + v.v[i] ;

    return w;
}

