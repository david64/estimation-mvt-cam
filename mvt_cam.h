
#ifndef MV_CAM_H
#define MVT_CAM_H

#include "matrices.h"
#include "params_mvt.h"


typedef struct {

    vect centre;
    vect i,j,k;

} pos_camera;


// calcule la position de la camera a chaque instant du mouvement parametre par
// le mouvement mvt de n etapes. (Ecrit dans pos)
void calc_pos_camera(params* mvt, pos_camera* pos, int n, int fc);

// calcule la matrice de rotation du mouvement de camera parametre par p
mat mat_rot(params mvt);


void mvt_cam_matlab(pos_camera* pos, int n, char* fn);

#endif

