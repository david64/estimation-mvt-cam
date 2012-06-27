/* Camera motion estimation, by Léo Girardin and David Lafontaine
    Copyright (C) 2012 Léo Girardin and David Lafontaine

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <stdlib.h>
#include <stdio.h>
#include "cam_motion.h"
#include <math.h>
#include <string.h>


void comp_cam_position(params* motion, cam_position* pos, int n, double fc) {

    int i,j;
    
    mat R;

    R.rows = 3;
    R.columns = 3;

    for(i=0; i<3; i++) {
        
        for(j=0; j<3; j++) {

            if(i==j)
                R.m[i][j] = 1;
            else
                R.m[i][j] = 0;
        }
    }
  
    pos[0].center.size = 3;
    pos[0].i.size = 3;
    pos[0].j.size = 3;
    pos[0].k.size = 3;

    pos[0].center.v[0] = 0;
    pos[0].center.v[1] = 0;
    pos[0].center.v[2] = 0;

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

        vect t; // This is the translation vector
        t.size = 3;
        t.v[0] = - motion[i].A * fc;
        t.v[1] = - motion[i].B * fc;
        t.v[2] = - motion[i].C * fc;

        R = product_mm(R, mat_rot(motion[i]));

        pos[i+1].i = product_mv(R, pos[0].i);
        pos[i+1].j = product_mv(R, pos[0].j);
        pos[i+1].k = product_mv(R, pos[0].k);
        
        pos[i+1].center = sum_vv(pos[i].center, product_mv(R, t)); 

    }

}

// Compute the rotation matrix corresponding to motion m
mat mat_rot(params m) {

    mat R;

    R.rows = 3;
    R.columns = 3;

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

// Write the camera position at each instant in octave format in a file
void octave_cam_motion(cam_position* pos, int n, char* fn) {

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
        sprintf(x, "%f", pos[i].center.v[0]);
        strcat(s,x);
        strcat(s, " ");
    }
    strcat(s, "]; \n");
    strcat(s, "y = [");
    for(i=0; i<n; i++) {
        
        char y[15] = "";
        sprintf(y, "%f", pos[i].center.v[1]);
        strcat(s,y);
        strcat(s, " ");
    }
    strcat(s, "];\n");
    strcat(s, "z = [");
    for(i=0; i<n; i++) {
        
        char z[15] = "";
        sprintf(z, "%f", pos[i].center.v[2]);
        strcat(s,z);
        strcat(s, " ");
    }
    
    strcat(s, "]; \n");
    
    FILE* f = fopen(fn, "w+");
    fputs(s,f);
    fclose(f);

    free(s);
}
