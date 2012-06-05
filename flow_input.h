
#ifndef FLOW_INPUT_H
#define FLOW_INPUT_H

#include "motion_params.h"

// Return the size of a optical flow, whicg one component is stored in file
size flow_size(char* file);

// Read the component of a optical flow stored in file. Write in u.
// u must have the good size. Use flow_size.
void read_flow(double** u, size s, char* file);

#endif

