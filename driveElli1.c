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
    if (TALKATIVE) printf("This is parameter file: %s\n", paramFileName);

    // output runName
    if(argv[2]) // runName for output files
        strcpy(runName, argv[2]);
    if (TALKATIVE) printf("This is run name: %s\n", runName);

    // IF verboseTF = 0, one line summarizing the run is written to the file listName.
    // IF verboseTF = 1, one line is written each iteration to the file listName
    verboseTF = 0;
    if(argc>3) // Verbose Output
        verboseTF = atoi(argv[3]);
    if (TALKATIVE) printf("This is verbose: %d\n", verboseTF);

    rAnchorAnchor = -1;
    if(argc>4) // parameter from command line
        rAnchorAnchor = atof(argv[4]);
    if (TALKATIVE) printf("This is rAnchorAnchor: %lf\n", rAnchorAnchor);

    lContourITIM1 = -1;
    if(argc>5) // parameter from command line
        lContourITIM1 = atof(argv[5]);
    if (TALKATIVE) printf("This is lContourITIM1: %lf\n", lContourITIM1);
    
    lContourITIM2 = -1;
    if(argc>5) // parameter from command line
        lContourITIM2 = atof(argv[6]);
    if (TALKATIVE) printf("This is lContourITIM2: %lf\n", lContourITIM2);

    lPersistenceITIM = -1;
    if(argc>6) // parameter from command line
        lPersistenceITIM = atof(argv[7]);
    if (TALKATIVE) printf("This is lPersistenceITIM: %lf\n", lPersistenceITIM);
    
    // load parameters
    getParams();

    //printf("lContourITIM=%lf\n", lContourITIM);

    elliMetropolis();

    return 0;

} // finished main
