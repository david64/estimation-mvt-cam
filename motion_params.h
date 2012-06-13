

/* motion_params.h */


#ifndef PARAMS
#define PARAMS

#include <stdlib.h>
#include "matrix.h"

#define N 100		

// Parameters of a camera motion
typedef struct
{
	double gamma, alpha, beta, A, B, C; 
} params; // The lower case theta is here called gamma for clarity

// Size of an image
typedef struct
{
	int h, w;
} size;

// Return the pixel (i,j) of an image
float get_pixel(float* img, int i, int j, size s);

// Compute the parameters of the motion f -> g
params motion_params(char* file_f, char* file_g, double fc);

// Compute grad(g). Write the result in (dgdx, dgdy).
void comp_grad(double** dgdx, double** dgdy, float* g, size s); 

// Compute the parametric optical flow u_theta. Write in u.
void comp_utheta(double** u1, double** u2, vect theta, size s); 

// Compute DF_theta. Write in D.F
void comp_DFtheta(double** DF, double** u1, double** u2, float* f, float* g, double xi, size s);

// Compute deltatheta which minimizes sum(1/2 * w(x,y) * r_deltatheta^2)
vect comp_deltatheta(double** DF, double** dgdx, double** dgdy, double** u1, double** u2, size s);

// Convert parameters (a1,a2,c1,c2,q1,q2,xi) into parameters (theta, alpha, beta, A, B, C)
params params_conversion(vect, double fc);

// Compute the weighted mean of pixels around non-integer coordinates
double px_interp(double**, double, double);

// Same thing for integer pixels
int int_px_interp(int**, double, double);

// Same thing for and image
float img_px_interp(float*, double, double, size);

// Stopping criterion
int stop_criterion(vect deltas[N], int i);

// Convert parameters (theta, alpha, beta, A, B, C) into parameters (a1, a2, c1, c2, q1, q2)
vect reverse_params_conversion(params p, double fc);

// Return the size of the png image "file"
size image_size(char* file);

// Get the pixel (i,j) of an image
float get_pixel(float* img, int i, int j, size s);

// Set the pixel (i,j) of an image
void set_pixel(float* img, int i, int j, size s, float p);

// Return a margin adapted to the size of the image 
int margin(size s);

#endif

