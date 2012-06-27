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

/* matrix.h */
// Some matrix manipulation functions
// Those matrix are little (7x7) and are not dynamically allocated


#ifndef MATRICES
#define MATRICES


#define MAT_SIZE 10

/* A matrix */
typedef struct {
	double m[MAT_SIZE][MAT_SIZE];
	int rows;
	int columns;
} mat;

/* A vector */
typedef struct {
	double v[MAT_SIZE];
	int size;
} vect;

// Sum of the a_{i}b_{i} where a=(a_i) and b=(b_i) are columns
double sum_p(mat M, int a, int b);

// Cholesky matrix of a symmetric positive-definite matrix
mat cholesky(mat M);

// Print a matrix
void print_mat(mat M);

// Transpose a matrix
mat transpose(mat M);

// Naive product of two matrices
mat product_mm(mat A, mat B);

// Product of a matrix by a vector
vect product_mv(mat A, vect X);

// Solve PX = B with P upper triangulary
vect res_upper_tri(mat P, vect B);

// Solve PX = B with P lower triangulary
vect res_lower_tri(mat P, vect B);

// Solve MX = Y by Gauss elimination. We expect M to be a square matrix, Y a column of the same size and the system invertible 
vect gauss(mat A, vect U);

// Sum of two vectors
vect sum_vv(vect u, vect v);

#endif

