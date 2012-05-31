

/* params_mvt.h */


#ifndef PARAMS
#define PARAMS

#include <stdlib.h>
#include "matrices.h"

#define N 100		
#define MARGE 50 	

// Parametres d'un mouvement de camera
typedef struct
{
	double gamma, alpha, beta, A, B, C; 
} params; // Le theta minuscule de la these s'appelle ici gamma pour eviter toute confusion

// Taille d'une image
typedef struct
{
	int h, l; // h pour hauteur (nbr de lignes) et l pour doubleueur (nbr de colonnes)
} taille;

// Calcul les parametres d'un mouvement de camera envoyant l'image f sur g
params param_mvt(char* file_f, char* file_g, int fc);

// Donne la taille d'une image
taille taille_image(char* file);

// Charge l'image en niveaux de gris dans file_g. Ecrit dans g. /!\ g est supposé alloué.
void charger_image(int** g, char* file_g);

// Calcule le gradient de g. Ecrit le resultat dans (dgdx, dgdy)
void calc_grad(double** dgdx, double** dgdy, int** g, taille t); 

// Calcule le flot optique u parametre par theta. Ecrit dans u
void calc_utheta(double** u1, double** u2, vect theta, taille t); 

// Calcule DF_theta (quantite que l'on souhaite minimiser !). Ecrit dans DF
void calc_DFtheta(double** DF, double** u1, double** u2, int** f, int** g, double xi, taille t);

// Calcule deltatheta minimisant somme(1/2 * w(x,y) * r_deltatheta^2)
vect calc_deltatheta(double** DF, double** dgdx, double** dgdy, double** u1, double** u2, taille t);

// Convertit les parametres (a1,a2,c1,c2,q1,q2,xi) en parametres de camera interpretables (theta, alpha, beta, A, B, C)
params conversion_params(vect, int fc);

// Calcule la moyenne ponderee des pixels autour d'une coordonnee non entiere
double interp_pixel(double**, double, double);

// Idem, mais pour des tableaux d'entiers
int interp_pixeli(int**, double, double);

// double max_derniers_ecarts_moy(double norme[N1], int k); 


int critere_arret(vect deltas[N], int i);

#endif

