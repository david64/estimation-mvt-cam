
#include <stdlib.h>
#include <stdio.h>
#include "motion_params.h"


int main(int argc, char* argv[]) {

	if(argc<3) {
		printf("Not enough arguments \n");
		return 1;
	}
	
	motion_params(argv[1], argv[2], 180);
        return EXIT_SUCCESS;
}



