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

#ifndef FLOW_INPUT_H
#define FLOW_INPUT_H

#include "motion_params.h"

// Return the size of a optical flow, whicg one component is stored in file
size flow_size(char* file);

// Read the component of a optical flow stored in file. Write in u.
// u must have the good size. Use flow_size.
void read_flow(double** u, size s, char* file);

#endif

