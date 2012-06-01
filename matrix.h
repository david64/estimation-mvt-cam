
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

