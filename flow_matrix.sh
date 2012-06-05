#!/bin/bash

# This script allows to use the Horn-Schunck framework on IPOL to test our motion estimator as an optical flow algorithm.

# First, compute the motion between images $1 and $2 with focale $3
parameters $1 $2 $3 > cam_motion_params
P=$(/bin/cat cam_motion_params)

# Then, compute the vertical flow associated to motion $P with focale $3 and size of image $1
u1 $P $3 $1 > vertical_flow

# Then, compute the horizontal flow associated to motion $P with focale $3 and size of image $1
u2 $P $3 $1 > horizontal_flow

# Finally, merge the two flows in a .tiff image.
plambda horizontal_flow vertical_flow "x y join" > $4

