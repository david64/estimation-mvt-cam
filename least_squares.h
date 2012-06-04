
/* least_squares.h */
// Compute an appoximation of (a1,a2,c1,c2,q1,q2) as they are described in the Jonchery thesis with a least squares method


#ifndef LEAST_SQUARES
#define LEAST_SQUARES


#include "matrix.h"

// Camera motion parameters
typedef struct {

	double a1,a2,c1,c2,q1,q2;

} params;

// Quadratic form of the least squares method
mat least_squares_quad(int size_x, int size_y); 

// Linear form of the least squares method
vect least_squares_lin(int size_x, int size_y, double** flow_x, double** flow_y); 

// Final computation
params least_squares_params(int size_x, int size_y, double** flow_x, double** flow_y);


#endif

