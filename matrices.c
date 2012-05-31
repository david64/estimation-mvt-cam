
/* matrices.c */
/* Quelques fonctions de manipulation de matrices */

#include <math.h>
#include <stdio.h>

#include "matrices.h"

double somme_p(mat M, int a, int b) {

	double r = 0.0;
	int k;
	for(k=0; k<M.lignes; k++)
		r = r + M.m[k][a]*M.m[k][b];
	return r;
}

/* Matrice de cholesky d'une matrice symétrique définie positive */
mat cholesky(mat M) {

	mat L;
	
	if(M.lignes != M.colonnes)
		return L;

	int n = M.lignes;
	L.lignes = n;
	L.colonnes = n;

	int i,j;

	for(i=0;i<n;i++) {
		for(j=0;j<n;j++)
			L.m[i][j] = 0.0;
	}

	for(i=0;i<n;i++){
		L.m[i][i] = sqrt(M.m[i][i] - somme_p(L, i, i));
		for(j=i+1;j<n;j++)
			L.m[i][j] = (M.m[i][j] - somme_p(L, j, i))/L.m[i][i];
	}
	return L;
}

/* Affiche une matrice */
void print_mat(mat M){

	printf("\n");

	int i,j;
	for(i=0;i<M.lignes;i++) {
		for(j=0;j<M.colonnes;j++) {
			printf("%e ",M.m[i][j]);
		}
		printf("\n");
	}
}

/* Transpose une matrice */
mat transpose(mat M) {

	mat T;
	T.lignes = M.colonnes;
	T.colonnes = M.lignes;

	int i,j;
	for(i=0;i<M.lignes;i++) {
		for(j=0;j<M.colonnes;j++){
			T.m[i][j] = M.m[j][i];
		}
	}
	return T;
}

/* Produit de deux matrices (naïf) */
mat produit_mm(mat A, mat B){

	mat M;

	if(A.colonnes != B.lignes)
		return M;
	
	M.lignes = A.lignes;
	M.colonnes = B.colonnes;
	
	int i,j,k;

	for(i=0;i<A.lignes;i++){
		for(j=0;j<B.colonnes;j++){
			M.m[i][j] = 0.0;
			for(k=0;k<A.colonnes;k++)
				M.m[i][j] = M.m[i][j] + A.m[i][k]*B.m[k][j];
		}
	}
	
	return M;
}

/* Produit d'une matrice par un vecteur */
vect produit_mv(mat A, vect X) {

	vect Y;

	if(A.colonnes != X.taille)
		return Y;
	
	Y.taille = A.lignes;

	int i,k;
	for(k=0;k<A.lignes;k++) {
		Y.v[k] = 0.0;
		for(i=0;i<A.colonnes;i++)
			Y.v[k] = Y.v[k] + A.m[k][i]*X.v[i];		
	}
	
	return Y;
}

/* Résoud PX = B où P est triangulaire supérieure */
vect res_tri_sup(mat P, vect B) {

	vect X;
	
	if(P.lignes != B.taille || P.lignes != P.colonnes)
		return X;

	int i,k;
	
	X.taille = P.lignes;

	for(i=B.taille-1;i>=0;i--) {
		double s = 0.0;
		for(k=i+1;k<B.taille;k++)
			s = s + P.m[i][k] * X.v[k];
		X.v[i] = (B.v[i]-s)/P.m[i][i];	
	}

	return X;
}

/* Résoud PX = B où P est triangulaire inférieure */
vect res_tri_inf(mat P, vect B) {

	vect X;
	
	if(P.lignes != B.taille || P.lignes != P.colonnes)
		return X;

	int i,k;
	
	X.taille = P.lignes;
	
	for(i=0;i<B.taille;i++) {
		double s = 0.0;
		for(k=0;k<i;k++)
			s = s + P.m[i][k] * X.v[k];
		X.v[i] = (B.v[i]-s)/P.m[i][i];	
	}

	return X;
}

/* Résoud le système supposé inversible MX = Y par pivot de Gauss */
vect gauss(mat M, vect Y) {

	int n = Y.taille;
	int k,i,j;
	
	for(k=0;k<n-1;k++){
		
		// Recherche d'un pivot l
	 	int l=k;
		double max = fabs(M.m[k][k]);
	
		for(i=k+1; i<n; i++){
			if(max < fabs(M.m[i][k])){
				max = fabs(M.m[i][k]);
				l = i;
			}
		}	
	
		if(l>k) {
			// Echange des lignes l et k  
			double tmp;
  			for (j=k; j<n; j++) {
    				tmp = M.m[k][j];
    				M.m[k][j] = M.m[l][j];
    				M.m[l][j] = tmp;
  			}
  			tmp = Y.v[k];
  			Y.v[k] = Y.v[l];
  			Y.v[l] = tmp;
		}
		// On pivote
		for (i=k+1; i<n; i++) {

    			double q = M.m[i][k]/M.m[k][k];
    			Y.v[i] = Y.v[i] - q * Y.v[k];
    			for (j=k+1; j<n; j++) {
      				M.m[i][j] = M.m[i][j] - q * M.m[k][j];
    			}
		}

	}
	
	// Le système est maintenant triangulaire supérieur, on l'inverse
	return res_tri_sup(M, Y);
}


vect somme_vv(vect u, vect v) {

    vect w;

    if(u.taille != v.taille)
        return w;

    w.taille = u.taille;

    int i;

    for(i=0; i<v.taille; i++)
        w.v[i] = u.v[i] + v.v[i] ;

    return w;
}
