

#include "simul_mvt.h"


int interp_pixeli(int** t, double x_, double y_);


void simul_mvt(char* fichier, char* out, params p)
{

	taille t = taille_image(fichier);

	int **f, **g;
	double **u1, **u2;

	// Allocation memoire	
	f = malloc(t.h * sizeof(int*));
	g = malloc(t.h * sizeof(int*));
	u1 = malloc(t.h * sizeof(double*));
	u2 = malloc(t.h * sizeof(double*));

	int i;
	for (i = 0 ; i < t.h ; i++)
	{
		f[i] = malloc(t.l * sizeof(int));
		g[i] = malloc(t.l * sizeof(int));
		u1[i] = malloc(t.l * sizeof(double));
		u2[i] = malloc(t.l * sizeof(double));
	}

	// Chargement de l'image f
	charger_image(f, fichier);

	// Calcul du flot optique u
	vect theta = conversion_params_inverse(p);
	
	int x,y;
	for (x = 0 ; x < t.h ; x++) {
	
		for (y = 0 ; y < t.l ; y++) { 
		
			u1[x][y] = theta.v[2] + theta.v[0]*(x-t.h/2) + theta.v[1]*(y-t.l/2) + theta.v[4]*(x-t.h/2)*(x-t.h/2) + theta.v[5]*(x-t.h/2)*(y-t.l/2);
			u2[x][y] = theta.v[3] - theta.v[1]*(x-t.h/2) + theta.v[0]*(y-t.l/2) + theta.v[4]*(x-t.h/2)*(y-t.l)/2 + theta.v[5]*(y-t.l/2)*(y-t.l/2);
		}
	}

	// Calcul de g	
	for (x = 0 ; x < t.h ; x++)
	{	
		for (y=0 ; y<t.l ; y++)
		{
			if ( -1 < x - u1[x][y] && x - u1[x][y] < t.h -1 &&  -1 < y - u2[x][y] && y - u2[x][y]<t.l -1 ) 
				g[x][y] = interp_pixeli(f, x - u1[x][y], y - u2[x][y]);
			else
				g[x][y] = 0;
		}
	}

    printf("h : %d, l : %d \n", t.h, t.l);

	// Enregistrement g
	enregistrer_image(g, out, t);

	// Liberation memoire
	for (i=0 ; i < t.h ; i++)
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


int interp_pixeli(int** t, double x_, double y_){

	int x = x_;
	int y = y_;
	
	return  (x_- x)*(y_-y)*t[x+1][y+1] + (x_-x)*(1-y_+y)*t[x+1][y] + (1-x_+x)*(y_-y)*t[x][y+1] + (1-x_+x)*(1-y_+y)*t[x][y];

}


