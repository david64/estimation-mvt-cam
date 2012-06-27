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

