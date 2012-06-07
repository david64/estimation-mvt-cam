
option=-lSDL -std=c99 -Wall -D EXIT_SUCCESS=0

all : parameters parameters_seq u1 u2 parameters_flow_input deltathetas motion_simulation table

parameters: main_parameters.c matrix.c motion_params.c comp_deltatheta.c load_image.c aux.c motion_params.h matrix.h
	gcc main_parameters.c matrix.c motion_params.c comp_deltatheta.c load_image.c aux.c -o parameters -lm -lSDL_image $(option)

parameters_seq:main_parameters.c matrix.c motion_params.c comp_deltatheta.c load_image.c aux.c motion_params.h matrix.h
	gcc main_parameters_seq.c matrix.c motion_params.c comp_deltatheta.c load_image.c aux.c cam_motion.c -o parameters_seq -lm -lSDL_image $(option)

u1:main_parameters.c load_image.c motion_params.h 
	gcc main_u1.c load_image.c -o u1 -lm -lSDL_image $(option)

u2:main_u2.c load_image.c aux.c motion_params.h 
	gcc main_u2.c load_image.c -o u2 -lm -lSDL_image $(option)

parameters_flow_input:main_flow_input.c least_squares.c least_squares.h matrix.c motion_params.c motion_params.h matrix.h
	gcc main_flow_input.c least_squares.c aux.c matrix.c flow_input.c -o params_flow_input -lm $(option)

deltathetas:main_deltathetas.c matrix.c motion_params.c comp_deltatheta.c load_image.c aux.c motion_params.h matrix.h
	gcc main_deltathetas.c matrix.c motion_params.c comp_deltatheta.c load_image.c aux.c -D STAT_STUDY -o deltathetas -lm -lSDL_image $(option)

motion_simulation: main_motion_simulation.c reverse_params_conversion.c motion_params.h motion_simulation.c save_image.c load_image.c 
	gcc motion_simulation.c reverse_params_conversion.c save_image.c load_image.c main_motion_simulation.c -o motion_simulation -lSDL_image $(option)

table: main_tab.c
	gcc main_tab.c -o table $(option)

