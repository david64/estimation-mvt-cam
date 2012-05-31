
/* matrices.h */
/* Quelques fonctions de manipulation de matrices */
/* Les matrices sont supposées petites (nous utiliserons des
matrices de taille 7x7) de telle sorte que nous n'avons pas
besoin d'allouer la mémoire dynamiquement */


#ifndef MATRICES
#define MATRICES


#define MAT_TAILLE 10

/* Une matrice */
typedef struct {
	double m[MAT_TAILLE][MAT_TAILLE];
	int lignes;
	int colonnes;
} mat;

/* Un vecteur */
typedef struct {
	double v[MAT_TAILLE];
	int taille;
} vect;

/* Somme des produits des coefficients des colonnes a et b */
double somme_p(mat M, int a, int b);

/* Renvoie la matrice de Cholesky d'une matrice symétrique définie positive */
mat cholesky(mat M);

/* Affiche une matrice */
void print_mat(mat M);

/* Transpose une matrice */
mat transpose(mat M);

/* Produit de deux matrices (algorithme naïf) */
mat produit_mm(mat A, mat B);

/* Produit d'une matrice par un vecteur */
vect produit_mv(mat A, vect X);

/* Résoud PX = B avec P triangulaire supérieure */
vect res_tri_sup(mat P, vect B);

/* Résoud PX = B avec P triangulaire inférieure */
vect res_tri_inf(mat P, vect B);

/* Résoud MX = Y par pivot de gauss. M est supposée carrée de même taille que Y et le système obtenu inversible */
vect gauss(mat A, vect U);

// addition de deux vecteurs
vect somme_vv(vect u, vect v);

#endif

