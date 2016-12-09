/*** Jun Allard jun.allard@uci.edu                   ***/

#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "twister.c"

/*******************************************************************************/
//  INCLUDES
/*******************************************************************************/

#include "elli1.h"
#include "outputControl.c"
#include "getParams.c"
#include "elli1.c"

/*******************************************************************************/
//  MAIN
/*******************************************************************************/

// arguments: listName, dimension, nBar, N, dt
int main( int argc, char *argv[] )
{
    // Intialize random number generator (twister.c)
    RanInit(0);

    if(argv[1]) // parameter file suffix
        strcpy(paramFileName, argv[1]);

    // output runName
    if(argv[2]) // runName for output files
        strcpy(runName, argv[2]);

    // IF verboseTF = 0, one line summarizing the run is written to the file listName.
    // IF verboseTF = 1, one line is written each iteration to the file listName
    verboseTF = 0;
    if(argc>3) // Verbose Output
        verboseTF = atoi(argv[3]);

    rAnchorAnchor = -1;
    if(argc>4) // parameter from command line
        rAnchorAnchor = atof(argv[4]);

    lContourITIM = -1;
    if(argc>5) // parameter from command line
        lContourITIM = atof(argv[5]);

    // load parameters
    getParams();

    //printf("lContourITIM=%lf\n", lContourITIM);

    elliMetropolis();

    return 0;

} // finished main
