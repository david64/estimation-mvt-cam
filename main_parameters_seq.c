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
#include "motion_params.h"
#include <string.h>
#include <math.h>
#include "cam_motion.h"


int main(int argc, char* argv[]) {

	if(argc<6) {
		printf("Not enough arguments !\n");
		return 1;
	}


    int i,j;
    
    // Arguments
    
    char* dir = argv[1];
    int first;
	sscanf(argv[2], "%i", &first);
    int last;
    sscanf(argv[3], "%i", &last);
    char* ext = argv[4];

    int n = last-first+1;

    printf("\033[2J\033[0;0H");
    printf("Estimation of the camera motion in the sequence stored in %s\n", dir);
    
    // Creation of the file list
    
    char** files;
    files = malloc(n*sizeof(char*));
    for(i=0; i<n; i++)
            files[i] = malloc(100*sizeof(char));

    for(i=first; i<=last; i++) {

        char filename[100] = "";
        
        strcat(filename, dir);
        strcat(filename, "/");
        
        int nb_zero = 8 - ((int) log10(i) + 1);
        int j;
        for(j=0;j<nb_zero;j++)
            strcat(filename, "0");

        char ch_i[8] = "";
        sprintf(ch_i, "%i", i);
        
        strcat(filename, ch_i);
        strcat(filename, ".");
        strcat(filename, ext);

        strcpy(files[i-first], filename);
    }
    
    // Estimation of the camera motion
  
    params* motion;

    motion = malloc(sizeof(params) * (n-1));

    double fc = 1.0;
    sscanf(argv[5], "%lf", &fc);

    float freq = 100.0/(n-1);
    float p = 0;

    for(i=0; i<n-1; i++) {

        motion[i] = motion_params(files[i], files[i+1], fc);	
        
        if(argc==7) {
            
            p = p + freq;
            printf("\033[2J\033[0;0H");
            printf("Estimation of the camera motion in the sequence stored in %s\n Progression : [", dir);
            for(j=0;j<(int) p;j++)
                printf(".");
            for(j=(int) p;j<100;j++)
                printf(" ");
            printf("] %f %% \n", p);
        
        } else {
	    
            printf("Parameters of the motion %s -> %s : \n", files[i], files[i+1]);
            printf("theta=%le ; alpha=%le ; beta=%le ; A=%le ; B=%le ; C=%le \n", motion[i].gamma, motion[i].alpha, motion[i].beta, motion[i].A, motion[i].B, motion[i].C);
        }

    }

    // Compute the camera position for octave displaying

    if(argc==7){
   
        cam_position* pos = malloc(sizeof(cam_position)*n);

        comp_cam_position(motion, pos, n, fc);
        octave_cam_motion(pos, n, argv[6]);

        free(pos);

        printf("Matrices describing the camera position for use in octave written in ");
        printf(argv[6]);
        printf("\n");
    }

    free(motion);

    // Deallocation of the file list
    for(i=0; i<n; i++)
        free(files[i]);

    free(files);

    return EXIT_SUCCESS;
}

