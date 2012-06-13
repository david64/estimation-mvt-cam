

#include <stdlib.h>
#include <stdio.h>
#include "params_mvt.h"
#include <string.h>
#include <math.h>
#include "mvt_cam.h"


int main(int argc, char* argv[]) {

	if(argc<6) {
		printf("Pas assez d'arguments !\n");
		return 0;
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
    printf("Estimation du mouvement de la camera dans la sequence stockee dans ");
    printf(dir);
    printf("\n");
    
    // Creation de la liste des fichiers
    
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
    
   
    // Estimation du mouvement de la camera
  
    params* mvt;

    mvt = malloc(sizeof(params) * (n-1));

    int fc = 1;
    sscanf(argv[5], "%i", &fc);

    float freq = 100.0/(n-1);
    float p = 0;

    for(i=0; i<n-1; i++) {

        mvt[i] = param_mvt(files[i], files[i+1], fc);	
        
        if(argc==7) {
            
            p = p + freq;
            printf("\033[2J\033[0;0H");
            printf("Estimation du mouvement de la camera dans la sequence stockee dans ");
            printf(dir);
            printf("\n");
            printf("Progression : [");
            for(j=0;j<(int) p;j++)
                printf(".");
            for(j=(int) p;j<100;j++)
                printf(" ");
            printf("] ");
            printf("%i % \n", (int) p);
        
        } else {
	    
            printf("Parametres du mouvement pour %s -> %s : \n", files[i], files[i+1]);
            printf("theta=%le ; alpha=%le ; beta=%le ; A=%le ; B=%le ; C=%le \n", mvt[i].gamma, mvt[i].alpha, mvt[i].beta, mvt[i].A, mvt[i].B, mvt[i].C);
        }

    }

    // Calcul eventuel de la position de la camera pour affichage sous Matlab

    if(argc==7){
   
        pos_camera* pos = malloc(sizeof(pos_camera)*n);

        calc_pos_camera(mvt, pos, n, fc);
        mvt_cam_matlab(pos, n, argv[6]);

        free(pos);

        printf("Matrices decrivant la positition de la camera pour exploitation dans matlab ecrites dans ");
        printf(argv[6]);
        printf("\n");
    }

    free(mvt);

    // Desallocation de la liste des fichiers
    for(i=0; i<n; i++)
        free(files[i]);

    free(files);

    return 0;
}


