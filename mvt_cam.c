

#include <stdlib.h>
#include <stdio.h>
#include "mvt_cam.h"
#include <math.h>
#include <string.h>


void calc_pos_camera(params* mvt, pos_camera* pos, int n, int fc) {

    int i,j;
    
    mat R;

    R.lignes = 3;
    R.colonnes = 3;

    for(i=0; i<3; i++) {
        
        for(j=0; j<3; j++) {

            if(i==j)
                R.m[i][j] = 1;
            else
                R.m[i][j] = 0;
        }
    }
  
    pos[0].centre.taille = 3;
    pos[0].i.taille = 3;
    pos[0].j.taille = 3;
    pos[0].k.taille = 3;

    pos[0].centre.v[0] = 0;
    pos[0].centre.v[1] = 0;
    pos[0].centre.v[2] = 0;

    pos[0].i.v[0] = 1;
    pos[0].i.v[1] = 0;
    pos[0].i.v[2] = 0;

    pos[0].j.v[0] = 0;
    pos[0].j.v[1] = 1;
    pos[0].j.v[2] = 0;
    
    pos[0].k.v[0] = 0;
    pos[0].k.v[1] = 0;
    pos[0].k.v[2] = 1;
    
    for(i=0; i<n-1; i++){

        vect t;
        t.taille = 3;
        t.v[0] = - mvt[i].A * fc;
        t.v[1] = - mvt[i].B * fc;
        t.v[2] = - mvt[i].C * fc;

        R = produit_mm(R, mat_rot(mvt[i]));

        pos[i+1].i = produit_mv(R, pos[0].i);
        pos[i+1].j = produit_mv(R, pos[0].j);
        pos[i+1].k = produit_mv(R, pos[0].k);
        
        pos[i+1].centre = somme_vv(pos[i].centre, produit_mv(R, t)); 

    }

}

mat mat_rot(params m) {

    mat R;

    R.lignes = 3;
    R.colonnes = 3;

    R.m[0][0] = cos(m.beta) - (1-cos(m.alpha)) * sin(m.gamma) * sin(m.gamma - m. beta);
    R.m[0][1] = - sin(m.beta) + (1 - cos(m.alpha)) * sin(m.gamma) * cos(m.gamma - m.beta);
    R.m[0][2] = sin(m.gamma) * sin(m.alpha);

    R.m[1][0] = sin(m.beta) + (1-cos(m.alpha)) * cos(m.gamma) * sin(m.gamma - m.beta);
    R.m[1][1] = cos(m.beta) - (1-cos(m.alpha)) * cos(m.gamma) * cos(m.gamma - m.beta);
    R.m[1][2] = - cos(m.gamma) * sin(m.alpha);
    
    R.m[2][0] = - sin(m.alpha) * sin(m.gamma - m.beta);
    R.m[2][1] =   sin(m.alpha) * cos(m.gamma - m.beta);
    R.m[2][2] = cos(m.alpha);

    return R;
}


// Ecrit la position de la camera a chaque instant dans un fichier exploitable
// par Matlab
void mvt_cam_matlab(pos_camera* pos, int n, char* fn) {

    char* s = malloc(sizeof(char)*4*500*n);
    s[0] = '\0';
  
    int i;

    // I

    strcat(s, "I = [");
    for(i=0; i<n; i++) {
        
        char x[15] = "";
        sprintf(x, "%f", pos[i].i.v[0]);
        strcat(s,x);
        strcat(s, " ");
    }
    strcat(s, ";");
    for(i=0; i<n; i++) {
        
        char y[15] = "";
        sprintf(y, "%f", pos[i].i.v[1]);
        strcat(s,y);
        strcat(s, " ");
    }
    strcat(s, ";");
    for(i=0; i<n; i++) {
        
        char z[15] = "";
        sprintf(z, "%f", pos[i].i.v[2]);
        strcat(s,z);
        strcat(s, " ");
    }
    strcat(s, "]; \n");
    
    // J

    strcat(s, "J = [");
    for(i=0; i<n; i++) {
        
        char x[15] = "";
        sprintf(x, "%f", pos[i].j.v[0]);
        strcat(s,x);
        strcat(s, " ");
    }
    strcat(s, ";");
    for(i=0; i<n; i++) {
        
        char y[15] = "";
        sprintf(y, "%f", pos[i].j.v[1]);
        strcat(s,y);
        strcat(s, " ");
    }
    strcat(s, ";");
    for(i=0; i<n; i++) {
        
        char z[15] = "";
        sprintf(z, "%f", pos[i].j.v[2]);
        strcat(s,z);
        strcat(s, " ");
    }
    strcat(s, "]; \n");
    
    
    // K

    strcat(s, "K = [");
    for(i=0; i<n; i++) {
        
        char x[15] = "";
        sprintf(x, "%f", pos[i].k.v[0]);
        strcat(s,x);
        strcat(s, " ");
    }
    strcat(s, ";");
    for(i=0; i<n; i++) {
        
        char y[15] = "";
        sprintf(y, "%f", pos[i].k.v[1]);
        strcat(s,y);
        strcat(s, " ");
    }
    strcat(s, ";");
    for(i=0; i<n; i++) {
        
        char z[15] = "";
        sprintf(z, "%f", pos[i].k.v[2]);
        strcat(s,z);
        strcat(s, " ");
    }
    strcat(s, "]; \n");
    
    
    // X

    strcat(s, "x = [");
    for(i=0; i<n; i++) {
        
        char x[15] = "";
        sprintf(x, "%f", pos[i].centre.v[0]);
        strcat(s,x);
        strcat(s, " ");
    }
    strcat(s, "]; \n");
    strcat(s, "y = [");
    for(i=0; i<n; i++) {
        
        char y[15] = "";
        sprintf(y, "%f", pos[i].centre.v[1]);
        strcat(s,y);
        strcat(s, " ");
    }
    strcat(s, "];\n");
    strcat(s, "z = [");
    for(i=0; i<n; i++) {
        
        char z[15] = "";
        sprintf(z, "%f", pos[i].centre.v[2]);
        strcat(s,z);
        strcat(s, " ");
    }
    
    strcat(s, "]; \n");
    
    FILE* f = fopen(fn, "w+");
    fputs(s,f);
    fclose(f);

    free(s);
}
