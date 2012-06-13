
#ifndef CAM_MOTION_H
#define CAM_MOTION_H

#include "matrix.h"
#include "motion_params.h"


typedef struct {

    vect center;
    vect i,j,k;

} cam_position;

// Compute the camera position at each instant in a n-step motion. Write the result in pos
void comp_cam_position(params* mvt, cam_position* pos, int n, double fc);

// Compute the rotation matrix of a motion
mat mat_rot(params motion);

// Write the motion in a octave-readable format
void octave_cam_motion(cam_position* pos, int n, char* fn);

#endif

