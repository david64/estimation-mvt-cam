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

#include "motion_params.h"
#include <stdlib.h>
#include <stdio.h>

// Return the size of a optical flow, which one component is stored in file
size flow_size(char* file) {

    FILE* f;
    f = fopen(file, "r");
    char lec[512];

    size s;

    int row = 1;
   
    while(fgets(lec, 512, f) != NULL && row<3) {
        
        if(row==2)
            sscanf(lec, "%d %d", &s.w, &s.h);        
        
        row++;
    }   
    
    return s;
}

// Read the component of a optical flow stored in file. Write in u.
// u must have the good size. Use flow_size.
void read_flow(double** u, size s, char* file) {

    FILE* f;
    f = fopen(file, "r");
    char lec[512];

    int row = -3;
   
    while(fgets(lec, 512, f) != NULL) {

        if(row > -1) {
            sscanf(lec, "%lf\n", &u[row/s.w][row % s.w]);
        }
        row++;
    }
}

