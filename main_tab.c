
#include <stdlib.h>
#include <stdio.h>

void main(int argc, char* argv[]) {

    double theta, alpha, beta, A, B, C;
    sscanf(argv[1], "%lf", &theta);
    sscanf(argv[2], "%lf", &alpha);
    sscanf(argv[3], "%lf", &beta);
    sscanf(argv[4], "%lf", &A);
    sscanf(argv[5], "%lf", &B);
    sscanf(argv[6], "%lf", &C);
    printf("<table border=\"1\" cellpadding=\"6\" cellspacing=\"0\" style=\"margin-left:0px;margin-right:auto\"> <tr bgcolor=\"#cccccc\"> <th> &theta; </th> <th> &alpha; </th> <th> &beta; </th> <th> A </th> <th> B </th> <th> C </th> </tr> \
            <tr> <td> %le </td> <td> %le </td> <td> %le </td> <td> %le </td> <td> %le </td> <td> %le </td> </tr> </table>", theta, alpha, beta, A, B, C);
    return;
}
