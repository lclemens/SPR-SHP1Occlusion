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
    fprintf(fSummary, "%lf %lf %ld %lf %lf %lf %lf\n",
                rAnchorAnchor,            // 1
                lContourITIM,             // 2
                nt,                       // 3
                ksStatistic,              // 4
                effectiveConcentration[1][4], // 5
                effectiveConcentration[0][1], // 6
                proximity[0][1]); // 7

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

    rM = particleDistances[1][4]; // This is the variable whose distribution will be tested for convergence.

    // Verbose output: One line is written each iteration.
    if (verboseTF)
    {
        // output results to file
        fList = fopen(runName, "a");
        fprintf(fList, "%ld %f %f %f %f %f %f %ld",
                nt,               // 1
                E,                // 2
                dx,               // 3
                dx,               // 4
                rate[0],          // 5
                rate[1],          // 6
                ksStatistic,      // 7
                stericOcclusion); // 8

        for (i=0;i<N;i++)
                fprintf(fList, " %f %f %f %f", r[i][0], r[i][1], r[i][2], 0.0);

        fprintf(fList, "\n");
        fclose(fList);
    }

    if (nt>NTCHECK)
    {
        // update bins for KS test
        if (rM < maxDistance)
            rMCounts[(long)floor(NBINS*rM/maxDistance)]++;
    }
	return;

}
