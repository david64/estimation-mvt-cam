#!/bin/bash

gcc main_parameters.c matrix.c motion_params.c comp_deltatheta.c load_image.c aux.c -o parameters -lm -lSDL -lSDL_image -std=c99 -Wall


