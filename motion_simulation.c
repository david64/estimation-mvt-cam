

#include <stdio.h>
#include "motion_params.h"
#include "io_png.h"


void motion_simulation(char* file, char* out, params p, int fc) {

	size s = image_size(file);

	double **u1, **u2;
    float *f, *g;

	// Allocation
    g = malloc(sizeof(float) * s.h * s.w);
    
    u1 = malloc(s.h * sizeof(double*));
	u2 = malloc(s.h * sizeof(double*));

	int i;
	for (i = 0 ; i < s.h ; i++) {
		
		u1[i] = malloc(s.w * sizeof(double));
		u2[i] = malloc(s.w * sizeof(double));
	}

    // Load image
    f = io_png_read_flt_opt(file,NULL, NULL, NULL, IO_PNG_OPT_GRAY);

	// Compute optical flow u
	vect theta = reverse_params_conversion(p, fc);
	
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
				set_pixel(g, x, y, s, img_px_interp(f, x - u1[x][y], y - u2[x][y], s));
			else
				set_pixel(g, x, y, s, 0.0);
		}
	}

	// Write g
    io_png_write_flt(out, g, (size_t) s.h, (size_t) s.w, 1);

	// Deallocation
	for (i=0 ; i < s.h ; i++) {
		
        free(u1[i]);
		free(u2[i]);
	}

	free(f);
	free(g);
	free(u1);
	free(u2);
}


