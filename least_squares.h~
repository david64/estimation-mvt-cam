
/* moindres_carres.h */
/* Calcule une approximation des paramètres du mouvement de caméra a1,a2,c1,c2,q1,q2
décrits dans la thèse de C.Jonchéry en utilisant la méthode des moindres carrés */


#ifndef MOINDRES_CARRES
#define MOINDRES_CARRES


#include "matrices.h"

/* Paramètres du mouvement de caméra tels que décrits dans la thèse de C. Jonchéry */
typedef struct {

	double a1,a2,c1,c2,q1,q2;

} params;

/* Calcule la forme quadratique associée à la détermination des paramètres du mouvement par moindres carrés,
pour le mouvement de caméra à 6 paramètres */
mat mat_forme_quadratique(int taille_x, int taille_y); 

/* Calcule la forme linéaire associée à la détermination des paramètres du mouvement par moindres carrés,
pour le mouvement de caméra à 6 paramètres, où (flot_x, flot_y) est le flot optique entre les deux images
consécutives */
vect vect_forme_lineaire(int taille_x, int taille_y, double** flot_x, double** flot_y); 

/* Calcule une approximation des paramètres du mouvement par la méthode des moindres carrés, où (flot_x,flot_y)
est le flot optique entre les deux images consécutives */
params params_moindres_carres(int taille_x, int taille_y, double** flot_x, double** flot_y);


#endif

