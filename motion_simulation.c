

#include "motion_simulation.h"


int int_px_interp(int** t, double x_, double y_);


void motion_simulation(char* file, char* out, params p)
{

	size s = image_size(file);

	int **f, **g;
	double **u1, **u2;

	// Allocation
	f = malloc(s.h * sizeof(int*));
	g = malloc(s.h * sizeof(int*));
	u1 = malloc(s.h * sizeof(double*));
	u2 = malloc(s.h * sizeof(double*));

	int i;
	for (i = 0 ; i < s.h ; i++)
	{
		f[i] = malloc(s.w * sizeof(int));
		g[i] = malloc(s.w * sizeof(int));
		u1[i] = malloc(s.w * sizeof(double));
		u2[i] = malloc(s.w * sizeof(double));
	}

	// Load image f
	load_image(f, file);

	// Compute optical flow u
	vect theta = reverse_params_conversion(p);
	
	int x,y;
	for (x = 0 ; x < s.h ; x++) {
	
		for (y = 0 ; y < s.w ; y++) { 
		
			u1[x][y] = theta.v[2] + theta.v[0]*(x-s.h/2) + theta.v[1]*(y-s.w/2) + theta.v[4]*(x-s.h/2)*(x-s.h/2) + theta.v[5]*(x-s.h/2)*(y-s.w/2);
			u2[x][y] = theta.v[3] - theta.v[1]*(x-s.h/2) + theta.v[0]*(y-s.w/2) + theta.v[4]*(x-s.h/2)*(y-s.w)/2 + theta.v[5]*(y-s.w/2)*(y-s.w/2);
		}
	}

	// Compute g	
	for (x = 0 ; x < s.h ; x++)
	{	
		for (y=0 ; y<s.w ; y++)
		{
			if ( -1 < x - u1[x][y] && x - u1[x][y] < s.h -1 &&  -1 < y - u2[x][y] && y - u2[x][y]<s.w -1 ) 
				g[x][y] = int_px_interp(f, x - u1[x][y], y - u2[x][y]);
			else
				g[x][y] = 0;
		}
	}

    printf("h : %d, l : %d \n", s.h, s.w);

	// Save g
	save_image(g, out, s);

	// Deallocation
	for (i=0 ; i < s.h ; i++)
	{
		free(f[i]);
		free(g[i]);
		free(u1[i]);
		free(u2[i]);
	}

	free(f);
	free(g);
	free(u1);
	free(u2);
}


int int_px_interp(int** t, double x_, double y_){

	int x = x_;
	int y = y_;
	
	return  (x_- x)*(y_-y)*t[x+1][y+1] + (x_-x)*(1-y_+y)*t[x+1][y] + (1-x_+x)*(y_-y)*t[x][y+1] + (1-x_+x)*(1-y_+y)*t[x][y];

}


