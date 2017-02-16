/*** Allard Group jun.allard@uci.edu                    ***/

void initializeSummary();
void finalizeSummary();
void dataRecording();

/*******************************************************************************/
//  GLOBAL VARIABLES for output control
/*******************************************************************************/

double reeBar_sum, ree2Bar_sum, rMBar_sum;
long POcclude_sum, Prvec0_sum;
double reeBar, ree2Bar, POcclude, Prvec0, reeiSite, rMBar;

/********************************************************************************************************/
void initializeSummary()
{
    // summary variables
    for (i=0;i<N;i++)
        for (j=i+1;j<N;j++)
        {
            proximity_long[i][j] = 0;
        }

}

/********************************************************************************************************/
void finalizeSummary()
{
    // finalize summary statistics

    for (i=0;i<N;i++)
        for (j=i+1;j<N;j++)
        {
            proximity[i][j] = proximity_long[i][j]/(double)(nt-NTCHECK);
            effectiveConcentration[i][j] = proximity[i][j]/(4/3*PI*pow(concentrationBin,3));
        }


    sprintf(tmpString, "%s.summary.dat", runName);
    fSummary = fopen(tmpString, "a");
    fprintf(fSummary, "%ld %lf %lf %lf %lf %lf %lf %lf\n",
                nt,                       // 1
                rAnchorAnchor,            // 2
                lContourITIM1,             // 3
                lContourITIM2,              //4
                ksStatistic,              // 5
                effectiveConcentration[4][6], // 6
                effectiveConcentration[1][6], // 7
                proximity[1][6]); // 8

    fclose(fSummary);


}

/********************************************************************************************************/
// Prepare stuff and optionally write to file - this function is called each timestep
void dataRecording()
{

    // particle distances
    for (i=0;i<N;i++)
        for (j=i+1;j<N;j++)
        {
            particleDistances[i][j] = sqrt( (r[i][0]-r[j][0])*(r[i][0]-r[j][0])
                                          + (r[i][1]-r[j][1])*(r[i][1]-r[j][1])
                                          + (r[i][2]-r[j][2])*(r[i][2]-r[j][2]) );

            if (nt>NTCHECK)
            {
                // Summary statistics (these will be written at the end of the run)
                // get local concentration
                if ( particleDistances[i][j] < concentrationBin+radius[i]+radius[j] )
                    proximity_long[i][j] ++;
            }
        }

    rM = particleDistances[4][6]; // This is the variable whose distribution will be tested for convergence.

    // Verbose output: One line is written each iteration.
    if (verboseTF)
    {
        if (nt>100000 && nt<=120000)
        {
            // output results to file
            fList = fopen(runName, "a");
//            fprintf(fList, "%ld %f %f %f %f %f %ld",
                    //nt,               // 1
                    //E,                // 2
                    //dx,               // 3
                    //rate[0],          // 4
                    //rate[1],          // 5
                    //ksStatistic,      // 6
                    //stericOcclusion); // 7
            
            fprintf(fList, "%ld %f %f %f %f %f %f %f",
                    nt,               // 1
                    ksStatistic,
                    rSH2,
                    lPocketSH2,
                    rF,
                    rAnchorAnchor,
                    NSH2isY1bound,
                    CSH2isY1bound);      // 6

            for (i=0;i<N;i++)
                    fprintf(fList, " %f %f %f %f", r[i][0], r[i][1], r[i][2], 0.0);

            fprintf(fList, "\n");
            fclose(fList);
        }
    }

    if (nt>NTCHECK)
    {
        // update bins for KS test
        if (rM < maxDistance)
            rMCounts[(long)floor(NBINS*rM/maxDistance)]++;
    }
	return;

}
