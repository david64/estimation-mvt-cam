
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
            sscanf(lec, "%d %d", &s.h, &s.w);        
        
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

