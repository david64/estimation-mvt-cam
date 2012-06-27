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
#!/bin/bash

# Subsample the images to accelerate the computation
subsampling $1 little_a.png $3
FC=$(subsampling $2 little_b.png $3)

# Compute the motion between images $1 and $2 with focale $3
parameters little_a.png little_b.png $FC > cam_motion_params_jonchery
P=$(/bin/cat cam_motion_params_jonchery)

# Some table formatting
table $P > cam_motion_params_jonchery

# Then, compute the vertical flow associated to motion $P with focale $3 and size of image $1
u1 $P $3 $1 > vert_flow_jonchery

# Then, compute the horizontal flow associated to motion $P with focale $3 and size of image $1
u2 $P $3 $1 > horiz_flow_jonchery

# Finally, merge the two flows in a .tiff image.
plambda horiz_flow_jonchery vert_flow_jonchery "x y join" > $4

