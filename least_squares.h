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

/* least_squares.h */
// Compute an appoximation of (a1,a2,c1,c2,q1,q2) as they are described in the Jonchery thesis with a least squares method
// and an input flow computed with a classical method

#ifndef LEAST_SQUARES
#define LEAST_SQUARES

#include "matrix.h"
#include "motion_params.h"

// Quadratic form of the least squares method
mat least_squares_quad_form(size s); 

// Linear form of the least squares method
vect least_squares_lin(size s, double** flow_x, double** flow_y); 

// Final computation
vect least_squares_params(size s, double** flow_x, double** flow_y);


#endif

