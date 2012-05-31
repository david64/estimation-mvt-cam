#!/bin/bash

gcc main_parameters_seq.c matrix.c motion_params.c comp_deltatheta.c load_image.c aux.c cam_motion.c -o parameters_seq -lm -lSDL -lSDL_image -std=c99 -Wall


