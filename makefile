
library=-lpng -lm
option=-std=c99 -Wall -Wextra -Werror -D EXIT_SUCCESS=0

all : parameters parameters_seq u1 u2 parameters_flow_input deltathetas motion_simulation table subsampling

parameters: main_parameters.c matrix.c motion_params.c comp_deltatheta.c aux.c motion_params.h matrix.h
	gcc main_parameters.c matrix.c motion_params.c comp_deltatheta.c io_png.c aux.c -o bin/parameters $(library) $(option)

parameters_seq:main_parameters.c matrix.c motion_params.c comp_deltatheta.c aux.c motion_params.h matrix.h
	gcc main_parameters_seq.c matrix.c motion_params.c comp_deltatheta.c io_png.c aux.c cam_motion.c -o bin/parameters_seq $(library) $(option)

u1:main_u1.c motion_params.h 
	gcc main_u1.c aux.c io_png.c -o bin/u1 $(library) $(option)

u2:main_u2.c motion_params.h 
	gcc main_u2.c aux.c io_png.c -o bin/u2 $(library) $(option)

parameters_flow_input:main_flow_input.c least_squares.c least_squares.h matrix.c motion_params.c motion_params.h matrix.h
	gcc main_flow_input.c io_png.c least_squares.c aux.c matrix.c flow_input.c -o bin/params_flow_input $(library) $(option)

deltathetas:main_deltathetas.c matrix.c motion_params.c comp_deltatheta.c aux.c motion_params.h matrix.h
	gcc main_deltathetas.c matrix.c motion_params.c comp_deltatheta.c io_png.c aux.c -D STAT_STUDY -o bin/deltathetas $(library) $(option)

motion_simulation: main_motion_simulation.c motion_params.h motion_simulation.c 
	gcc motion_simulation.c main_motion_simulation.c io_png.c aux.c -o bin/motion_simulation $(library) $(option)

table: main_tab.c
	gcc main_tab.c -o bin/table $(option)

subsampling: main_subsampling.c
	gcc main_subsampling.c io_png.c aux.c -o bin/subsampling $(library) $(option)
