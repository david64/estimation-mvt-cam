#!/bin/bash

parametres $1 $2 $3 > params_mvt_cam
P=$(/bin/cat params_mvt_cam)

u1 $P $3 $1 > flot_vertical
u2 $P $3 $1 > flot_horizontal
plambda flot_horizontal flot_vertical "x y join" > $4

