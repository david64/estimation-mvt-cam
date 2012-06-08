

/* aux.c */
/* Contains all auxiliary functions */


#include "motion_params.h"
#include <math.h>
#include "io_png.h"


#ifndef M_PI
	#define M_PI 3.14
#endif


// Compute DF_theta, write the result into DF
void comp_DFtheta (double** DF, double** u1, double** u2, float* f, float* g, double xi, size s){

	int x,y;

    int m = margin(s);

	for(x=m; x<s.h-m; x++) {
		for(y=m; y<s.w-m; y++){

            double x_ = x + u1[x][y];
			double y_ = y + u2[x][y];
			
			if(-1<x_ && x_<s.h-1 && -1<y_ && y_<s.w-1)
				DF[x][y] = img_px_interp(g, x_, y_,s) - get_pixel(f,x,y,s) + xi;
		}	
	}
}

// Compute the discrete gradient of g. Write the result in dgdx and dgdy.
void comp_grad(double** dgdx, double** dgdy, float* g, size s) {

	int x,y;
	for (x = 1 ; x < s.h-1 ; x++) {
	
		for (y = 1 ; y < s.w-1 ; y++) {
	
			dgdx[x][y] = (get_pixel(g,x+1,y,s) - get_pixel(g,x-1,y,s))/2;
			dgdy[x][y] = (get_pixel(g,x,y+1,s) - get_pixel(g,x,y-1,s))/2;
		}
	}
}


// Compute u_theta given motion parameters theta. Write the result in u1 and u2
void comp_utheta(double** u1, double** u2, vect theta, size s) {

	int x,y;

    int m = margin(s);

	for (x = m ; x < s.h-m ; x++) {
	
		for (y = m ; y < s.w-m ; y++){ 
		
			u1[x][y] = theta.v[2] + theta.v[0]*(x-s.h/2) + theta.v[1]*(y-s.w/2) + theta.v[4]*(x-s.h/2)*(x-s.h/2) + theta.v[5]*(x-s.h/2)*(y-s.w/2);
			u2[x][y] = theta.v[3] - theta.v[1]*(x-s.h/2) + theta.v[0]*(y-s.w/2) + theta.v[4]*(x-s.h/2)*(y-s.w/2) + theta.v[5]*(y-s.w/2)*(y-s.w/2);
		}
	}
}

// Convert motion parameters (a1, a2, c1, c2, q1, q2, xi) into (gamma, beta, alpha, A, B, C)
params params_conversion(vect theta, int fc) {

	// Recall : theta = (a_1, a_2, c_1, c_2, q_1, q_2, xi)
	params p;
	p.alpha = fc*sqrt(theta.v[4]*theta.v[4] + theta.v[5]*theta.v[5]);
	p.beta = theta.v[1];

	if (theta.v[5] > 0.0)
		p.gamma = -atan(theta.v[4]/theta.v[5]);
	else if (theta.v[5] < 0.0)
		p.gamma = -atan(theta.v[4]/theta.v[5]) + M_PI;
	else if (theta.v[4] > 0.0)
		p.gamma = M_PI/2;
	else if (theta.v[4] < 0.0)
		p.gamma = -M_PI/2;

	p.A = theta.v[2]/fc + (p.alpha)*sin(p.gamma);
	p.B = theta.v[3]/fc - (p.alpha)*cos(p.gamma);
	p.C = -theta.v[0];
	return p;
}

// Interpolate the value of t[x_][y_], where x_ and y_ are not integers
double px_interp(double** t, double x_, double y_){

	int x = x_;
	int y = y_;
	
	return  (x_- x)*(y_-y)*t[x+1][y+1] + (x_-x)*(1-y_+y)*t[x+1][y] + (1-x_+x)*(y_-y)*t[x][y+1] + (1-x_+x)*(1-y_+y)*t[x][y];

}

// Same function with integers values in t
int int_px_interp(int** t, double x_, double y_){

	int x = x_;
	int y = y_;
	
	return  (x_- x)*(y_-y)*t[x+1][y+1] + (x_-x)*(1-y_+y)*t[x+1][y] + (1-x_+x)*(y_-y)*t[x][y+1] + (1-x_+x)*(1-y_+y)*t[x][y];

}

// Same function with an image
float img_px_interp(float* t, double x_, double y_, size s){

	int x = x_;
	int y = y_;
	
	return  (x_- x)*(y_-y)*get_pixel(t,x+1,y+1,s) + (x_-x)*(1-y_+y)*get_pixel(t,x+1,y,s) + (1-x_+x)*(y_-y)*get_pixel(t,x,y+1,s) + (1-x_+x)*(1-y_+y)*get_pixel(t,x,y,s);

}

// Stopping criterion, found empirically
int stop_criterion(vect deltas[N], int i) {

   if(i<10) 
        return 0;

    double s = 0;
    int j;

    for(j=i-10;j<=i;j++)
        s += (deltas[j]).v[2];

    return (fabs(s) <= fabs((deltas[i]).v[2] - (deltas[i-1]).v[2])/2);

}

// Return the pixel (i,j) of the image
float get_pixel(float* img, int i, int j, size s) { return img[j + s.w*i]; }

// Set the pixel (i,j) of an image
void set_pixel(float* img, int i, int j, size s, float p) { img[j + s.w*i] = p; }

// Convert parameters (theta, alpha, beta, A, B, C) into parameters (a1, a2, c1, c2, q1, q2)
vect reverse_params_conversion(params p, int fc) {

	vect theta;
	theta.v[0] = -p.C;
	theta.v[1] = p.beta;
	theta.v[2] = fc*(p.A - (p.alpha)*sin(p.gamma));
	theta.v[3] = fc*(p.B + (p.alpha)*cos(p.gamma));
	theta.v[4] = -(p.alpha)*sin(p.gamma)/fc;
	theta.v[5] = (p.alpha)*cos(p.gamma)/fc;
	return theta;
}

// Return the size of the png image "file"
size image_size(char* file) {

    size s;
    size_t nx, ny;
    io_png_read_flt(file, &ny, &nx, NULL);
    s.h = (int) nx;
    s.w = (int) ny;
    return s;
}

int margin(size s) {
/*
    if (s.h>s.w) {
	   if(s.w/10 % 2)
	   	return s.w/10 + 1;
	   else
		return s.w/10;
    } else {	   
	   if(s.h/10 % 2)
	   	return s.h/10 + 1;
	   else
		return s.h/10;
   }
*/
	return 50;
}

