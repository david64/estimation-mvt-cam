

/* motion_params.h */


#ifndef PARAMS
#define PARAMS

#include <stdlib.h>
#include "matrix.h"

#define N 100		
#define MARGIN 50 	

// Parameters of a camera motion
typedef struct
{
	double gamma, alpha, beta, A, B, C; 
} params; // The lower case theta is here called gamma for clarity

// Size of an image
typedef struct
{
	int h, w;
} size

// Compute the parameters of the motion f -> g
params motion_params(char* file_f, char* file_g, int fc);

// Give the size of an image
size image_size(char* file);

// Load a grayscale image file_g. Write in g. Be careful, g is expected to be already allocated !
void load_image(int** g, char* file_g);

// Compute grad(g). Write the result in (dgdx, dgdy).
void comp_grad(double** dgdx, double** dgdy, int** g, size s); 

// Compute the parametric optical flow u_theta. Write in u.
void comp_utheta(double** u1, double** u2, vect theta, size s); 

// Compute DF_theta. Write in D.F
void comp_DFtheta(double** DF, double** u1, double** u2, int** f, int** g, double xi, size s);

// Compute deltatheta which minimizes sum(1/2 * w(x,y) * r_deltatheta^2)
vect comp_deltatheta(double** DF, double** dgdx, double** dgdy, double** u1, double** u2, size s);

// Convert parameters (a1,a2,c1,c2,q1,q2,xi) into parameters (theta, alpha, beta, A, B, C)
params params_conversion(vect, int fc);

// Compute the weighted mean of pixels around non-integer coordinates
double px_interp(double**, double, double);

// Same thing for integer pixels
int int_px_interp(int**, double, double);

// Stopping criterion
int critere_arret(vect deltas[N], int i);

#endif

