#!/bin/bash

gcc main_parametres.c matrices.c params_mvt.c calc_deltatheta.c charger_image.c aux.c -o parametres -lm -lSDL -lSDL_image -std=c99 -Wall


