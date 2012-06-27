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

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {

	if(argc<7){
		printf("Not enough arguments !");
        	return 0;
	}

    double theta, alpha, beta, A, B, C;
    sscanf(argv[1], "%lf", &theta);
    sscanf(argv[2], "%lf", &alpha);
    sscanf(argv[3], "%lf", &beta);
    sscanf(argv[4], "%lf", &A);
    sscanf(argv[5], "%lf", &B);
    sscanf(argv[6], "%lf", &C);
    printf("<table border=\"1\" cellpadding=\"6\" cellspacing=\"0\" style=\"margin-left:0px;margin-right:auto\"> <tr bgcolor=\"#cccccc\"> <th> &theta; </th> <th> &alpha; </th> <th> &beta; </th> <th> A </th> <th> B </th> <th> C </th> </tr> \
            <tr> <td> %le </td> <td> %le </td> <td> %le </td> <td> %le </td> <td> %le </td> <td> %le </td> </tr> </table>", theta, alpha, beta, A, B, C);
    return EXIT_SUCCESS;
}
