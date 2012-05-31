#!/bin/bash

gcc main_parametres_seq.c matrices.c params_mvt.c calc_deltatheta.c charger_image.c aux.c mvt_cam.c -o parametres_seq -lm -lSDL -lSDL_image -std=c99 -Wall


