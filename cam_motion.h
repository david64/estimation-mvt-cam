/* Camera motion estimation, by Léo Girardin and David Lafontaine
    Copyright (C) 2012 Léo Girardin and David Lafontaine

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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

