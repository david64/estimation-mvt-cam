
/* simul_mvt.h */

#ifndef SIMUL
#define SIMUL

#include <stdlib.h>
#include "matrices.h"

#define fc 100

// Paramètres de mouvement de camÃ©ra
typedef struct
{
	double gamma, alpha, beta, A, B, C;
} params; // Même structure que dans params_mvt.h !

typedef struct {

	int h,l;
} taille;

// Donne la taille d'une image
taille taille_image(char* file);

// Charger une image
void charger_image(int** f, char* fichier);

// Revenir Ã  (a1, â€¦)
vect conversion_params_inverse(params p);

// Enregistrer l'image modifiée
void enregistrer_image(int** f, char* filename, taille t);

// Simuler le mouvement
void simul_mvt(char* fichier, char* out, params p);

#endif
