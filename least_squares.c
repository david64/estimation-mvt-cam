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

/* least_squares.c */

#include "least_squares.h"
#include "motion_params.h"
#include <stdio.h>
#include <math.h>

/* Compute the matrix of the quadratic form associated to the least squares problem that we have to solve */
mat least_squares_quad_form(size s) {

	mat Q;
	Q.rows = 6;
	Q.columns = 6;
	
	int x,y,i,j;
	
	for(i=0;i<6;i++){
		for(j=0;j<6;j++)
			Q.m[i][j] = 0.0;
	}	

    vect e, f;
    e.size = 6;
    f.size = 6;

    int m = margin(s);

	for(x = m; x<s.h-m; x++){
        for(y = m; y<s.w-m; y++) {

            int x_ = x - s.h/2;
            int y_ = y - s.w/2;

            e.v[0] = x_;
            e.v[1] = y_;
            e.v[2] = 1;
            e.v[3] = 0;
            e.v[4] = x_*x_;
            e.v[5] = x_*y_;

            f.v[0] = y_;
            f.v[1] = -x_;
            f.v[2] = 0;
            f.v[3] = 1;
            f.v[4] = x_*y_;
            f.v[5] = y_*y_;
            
            for(i=0;i<6;i++){
                for(j=0;j<6;j++)
                    Q.m[i][j] += (e.v[i]*e.v[j] + f.v[i]*f.v[j]);
            }

        }
    }
   
    return Q;
}

/* Compute the vector of the linear form associated to the least squares problem that we have to solve */
vect least_squares_lin(size s, double** flow_x, double** flow_y) {

	vect l;
	l.size = 6;

	int x,y,i;

	for(i=0;i<6;i++)
		l.v[i] = 0.0;

    int m = margin(s);

	for(x=m;x<s.h-m;x++){
		for(y=m;y<s.w-m; y++) {

			double a = flow_x[x][y];
			double b = flow_y[x][y];

            int x_ = x - s.h/2;
            int y_ = y - s.w/2;

		  	l.v[0] +=  (a*x_ + b*y_);
			l.v[1] +=  (a*y_ - b*x_);
			l.v[2] +=  (a);
			l.v[3] +=  (b);
			l.v[4] +=  (a*x_*x_ + b*x_*y_);
			l.v[5] +=  (b*y_*y_ + a*x_*y_); 
		}
	}
	
	for(i=0;i<6;i++)
		l.v[i] *= (-2.0);
	
	return l;
}

// Compute an approximation of the motion parameters using the optical flow
vect least_squares_params(size s, double** flow_x, double** flow_y){

	mat U = least_squares_quad_form(s);
	vect B = least_squares_lin(s, flow_x, flow_y);
        
	mat L = cholesky(U);

	int i;
	for(i=0;i<6;i++)
		B.v[i] *= (-0.5);

	return res_upper_tri(L, res_lower_tri(transpose(L), B));
	
}

