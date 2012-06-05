
option=-std=c99 -Wall

all : parameters parameters_seq u1 u2 parameters_flow_input deltathetas motion_simulation

parameters:
	gcc main_parameters.c matrix.c motion_params.c comp_deltatheta.c load_image.c aux.c -o parameters -lm -lSDL -lSDL_image $(option)

parameters_seq:
	gcc main_parameters_seq.c matrix.c motion_params.c comp_deltatheta.c load_image.c aux.c cam_motion.c -o parameters_seq -lm -lSDL -lSDL_image $(option)

u1:
	gcc main_u1.c load_image.c -o u1 -lm -lSDL -lSDL_image $(option)

u2:
	gcc main_u2.c load_image.c -o u2 -lm -lSDL -lSDL_image $(option)

parameters_flow_input:
	gcc main_flow_input.c least_squares.c aux.c matrix.c flow_input.c -o params_flow_input -lm -lSDL $(option)

deltathetas:
	gcc main_deltathetas.c matrix.c motion_params.c comp_deltatheta.c load_image.c aux.c -D STAT_STUDY -o deltathetas -lm -lSDL -lSDL_image $(option)

motion_simulation:
	gcc motion_simulation.c reverse_params_conversion.c save_image.c load_image.c main_motion_simulation.c -o motion_simulation -lSDL -lSDL_image $(option)


