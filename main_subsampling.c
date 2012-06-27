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

#include "io_png.h"
#include "motion_params.h"
#include <stdio.h>

int main(int argc, char* argv[]){

    if(argc<2) {
        printf("Not enought parameters");
        return 1;
    }

    float *f;
    size_t nx, ny;
    size s;

    f = io_png_read_flt_opt(argv[1], &ny, &nx, NULL, IO_PNG_OPT_GRAY);
    s.h = (int) nx;
    s.w = (int) ny;

   double fc = 1.0;
   sscanf(argv[3], "%lf", &fc);
   
   if(s.w > 400) {

        float *g;
        g = malloc(sizeof(float)*s.h*s.w/4);

        size s_g;
        s_g.h = s.h/2;
        s_g.w = s.w/2;

        int i, j;

        for(i=0;i<s_g.h;i++) {
            for(j=0;j<s_g.w;j++)
               set_pixel(g, i, j, s_g, 0.0);
        }

        for(i=0;i<s.h-1;i=i+2) {
            for(j=0;j<s.w-1;j=j+2) {
                float p = (get_pixel(f, i, j, s) + get_pixel(f,i+1,j,s) + get_pixel(f,i,j+1,s) + get_pixel(f,i+1,j+1,s))/4;
                set_pixel(g, i/2, j/2, s_g, p);
            }
        }

        io_png_write_flt(argv[2], g, (size_t) s_g.w, (size_t) s_g.h, 1);
        printf("%le", fc/2);     
    }
    
    else {
        io_png_write_flt(argv[2], f, (size_t) s.w, (size_t) s.h, 1);
        printf("%le", fc);
    }
    
    return EXIT_SUCCESS;
}


