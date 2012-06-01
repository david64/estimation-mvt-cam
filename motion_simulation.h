
/* motion_simulation.h */

#ifndef SIMUL
#define SIMUL

#include <stdlib.h>
#include "matrix.h"

#define fc 100

// Camera motion parameters
typedef struct
{
	double gamma, alpha, beta, A, B, C;
} params; // Same structure in motion_params.h !

typedef struct {

	int h,w;
} size;

// Size of an image
size image_size(char* file);

// Load an image
void load_image(int** f, char* file);

// Convert parameters (theta,alpha,beta,A,B,C) into (a1,a2,c1,c2,q1,q2)
vect reverse_params_conversion(params p);

// Save an image
void save_image(int** f, char* filename, size s);

// Motion simulation
void motion_simulation(char* file, char* out, params p);

#endif

