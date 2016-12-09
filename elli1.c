void elliMetropolis();
void stationarity();
void appendBins();

void elliMetropolis()
{

    // initial configuration
    for(i=0;i<N;i++)
    {
        r[i][0] = 0.5*boxSize*(2*TWISTER-1);
        r[i][1] = 0.5*boxSize*(2*TWISTER-1);
        r[i][2] = boxSize*TWISTER;
    }

    convergedTF=0;
    nt=0;
    E = INF;

    // stuff needed for automatic perturbation size adaptation
    for(iParam=0;iParam<2;iParam++)
    {
        dx = dxInit;
        proposals[iParam] = 0;
        accepts[iParam] = 0;
    }

    // stuff needed for automatic stationarity (convergence) check
    ksStatistic = 1;
    ntNextStationarityCheck = 3*NTCHECK;
    for(iBin=0;iBin<NBINS;iBin++)
        rMCounts[iBin] = 0;

    // summary variables
    initializeSummary();

    /********* BEGIN LOOP THROUGH ITERATIONS! *******************/

    while(!convergedTF && nt < NTMAX) // Time loop!
    {

        // adapt step size
        if (!(nt % NTADAPT))
        {
            rate[0] = (double)accepts[0]/(double)proposals[0];
            rate[1] = (double)accepts[1]/(double)proposals[1];

            for(iParam=0;iParam<1;iParam++)
            {
                accepts[iParam] = 0;
                proposals[iParam] = 0;
                if (nt < NTCHECK)
                {
                    if (rate[iParam] > 0.5 || rate[iParam] < 0.3)
                    {
                        dx = dx*rate[iParam]/0.44;
                        if (dx > DXMAX)
                            dx = DXMAX;
                        if (dx < DXMIN)
                            dx = DXMIN;
                    }
                }
            }

        } // done adapting step

        /********* OUTLINE OF ALGORITHM *******************/
        // 1. We create a new proposal configuration and
        // then decide:
        // 2. whether the proposal configuration satisfies any constraints (e.g., box edges), and
        // 3. whether the proposal configuration is accepted by Metropolis test )
        // After the configuration update, we:
        // 4. collect any data of interest and optionally write it to file
        // 5. test for stationarity (convergence)
        // 6. increment the iteration and repeat

        /********* 1. Generate proposal configuration *******************/

        for(i=0;i<N;i++)
            for(ix=0;ix<3;ix++)
                rPropose[i][ix] = r[i][ix];

        iPropose = floor(N*TWISTER); // This is the particle we will adjust this time.
        proposals[0]++;

        constraintSatisfiedTF = 0;
        while(!constraintSatisfiedTF) // keep generating proposal configurations until we get one that satisfies the constraint
        {
            for(ix=0;ix<3;ix++)
                rPropose[iPropose][ix] = r[iPropose][ix] + dx*sqrt(-2*log(TWISTER))*cos(2*PI*TWISTER);
                  
            /********* 2. Test constraints *******************/
            constraintSatisfiedTF=1;

            // particle-particle hard-wall constraints
            for (i=0;i<N;i++)
            {
              // Note that the isBound matrix should be symmetric but is not, for efficiency.
                if( i!=iPropose && isBound[iPropose][i]==0 && isBound[i][iPropose]==0 &&
                   (rPropose[i][0]-rPropose[iPropose][0])*(rPropose[i][0]-rPropose[iPropose][0])
                 + (rPropose[i][1]-rPropose[iPropose][1])*(rPropose[i][1]-rPropose[iPropose][1])
                 + (rPropose[i][2]-rPropose[iPropose][2])*(rPropose[i][2]-rPropose[iPropose][2]) < (radius[iPropose] + radius[i])*(radius[iPropose] + radius[i]))
                {
                    constraintSatisfiedTF=0;
                    i=N+1; // short-circuit out of loop for efficiency
                }
            }

            // box
            if (membraneTF)
            {
                if (   rPropose[iPropose][2] < radius[iPropose] || rPropose[iPropose][2] > boxSize
                    || rPropose[iPropose][0] < -(boxSize/2-radius[iPropose]) || rPropose[iPropose][0] > +(boxSize/2-radius[iPropose])
                    || rPropose[iPropose][1] < -(boxSize/2-radius[iPropose]) || rPropose[iPropose][1] > +(boxSize/2-radius[iPropose]))
                {
                    constraintSatisfiedTF=0;
                } // done checking constraint
            }

        } // finished while-loop to impose constraint

        /********* 3. Metropolis test *******************/
        // We now have a propsoal configuration that passes the constraints.
        // Step 3 is to see if it passes our acceptance test (Metropolis test).

        // Compute energy
        // Energy in units of pNnm.
        ENew =
              // ITIM (between membrane and Monkey-Giraffe Y1)
              0.5*kITIM  *pow((sqrt(pow((0-rPropose[0][0]),2)
                                   +pow((0-rPropose[0][1]),2)
                                   +pow((0-rPropose[0][2]),2))-(xITIM+radius[0])),2)
              // ITIM (between membrane and unoccupied Giraffe Y2)
            + 0.5*kITIM  *pow((sqrt(pow((rAnchorAnchor-rPropose[1][0]),2)
                                   +pow((0            -rPropose[1][1]),2)
                                   +pow((0            -rPropose[1][2]),2))-(xITIM+radius[1])),2)
              // NSH2-CSH2 link
            + 0.5*kSH2SH2*pow((sqrt(pow((rPropose[2][0]-rPropose[3][0]),2)
                                   +pow((rPropose[2][1]-rPropose[3][1]),2)
                                   +pow((rPropose[2][2]-rPropose[3][2]),2))-(xSH2SH2+radius[2]+radius[3])),2)
              // CSH2-F link
            + 0.5*kSH2F  *pow((sqrt(pow((rPropose[3][0]-rPropose[4][0]),2)
                                   +pow((rPropose[3][1]-rPropose[4][1]),2)
                                   +pow((rPropose[3][2]-rPropose[4][2]),2))-(xSH2F+radius[2]+radius[3])),2)
            + 0; // --- TODO --- binding energies to include dynamic binding/unbinding

        // Bonds
        for (i=0;i<N;i++)
            for (j=i+1;j<N;j++)
            {
                if(isBound[j][i]==1 || isBound[i][j]==1) // Note that the isBound matrix should be symmetric but is not, for efficiency.
                {
                    ENew += 0.5*kBond*pow(sqrt(pow((rPropose[i][0]-rPropose[j][0]),2)
                                              +pow((rPropose[i][1]-rPropose[j][1]),2)
                                              +pow((rPropose[i][2]-rPropose[j][2]),2))-(radius[i]+radius[j]-lPocketSH2),2);
                }
            }


        //printf("nt=%ld, ENew=%lf\n", nt, ENew);

        if ( TWISTER < exp((E-ENew)/KBT) )
        {
            E = ENew;

            // Make configuration into the proposal configuration
            for(i=0;i<N;i++)
                for(ix=0;ix<3;ix++)
                    r[i][ix] = rPropose[i][ix];

            if(iPropose<N)
                accepts[0] ++;
            else
                accepts[1] ++;

        }

        /********* 4. Data collection and output to file *******************/

        if (1)
        {
            /********* 5. Test for stationarity *******************/
            // This test for stationarity automatically stops the iterations when the distribution is converged to within the tolerance KSCRITICAL.
            if (nt == 2*NTCHECK)
                appendBins();

            if (nt == ntNextStationarityCheck)
                stationarity();
        }

        // output to time series file
        dataRecording();

        /********* 6. Increment time *******************/
        nt++;

    } // done time loop

    // finalize summary statistics
    finalizeSummary();

}



/********************************************************************************************************/
// Test for convergence ("stationarity")
void stationarity()
{
    double cdf1, cdf2;
    ksStatistic = 0;
    cdf1=0;
    cdf2=0;
    for(iBin=0;iBin<NBINS;iBin++)
    {

        cdf1 += (double)rMCountsPrevious[iBin]/(((double)nt-(double)NTCHECK)/2.0);
        cdf2 += (double)rMCounts[iBin]/(((double)nt-(double)NTCHECK)/2.0);

        if (fabs(cdf1-cdf2)>ksStatistic)
            ksStatistic = fabs(cdf1-cdf2);
        //printf("rMCounts[%d]: %d, %d \t\t\t cdf: %f, %f\n", iBin, rMCountsPrevious[iBin],rMCounts[iBin], cdf1, cdf2);

    }

    //printf("ksStatistic=%f\n", ksStatistic);

    if (ksStatistic<KSCRITICAL)
        convergedTF=1;

    appendBins();

    ntNextStationarityCheck = 2*(ntNextStationarityCheck-NTCHECK)+NTCHECK;
    return;
}

// Helper function needed by test for convergence ("stationarity")
void appendBins()
{
    for(iBin=0;iBin<NBINS;iBin++)
    {
        rMCountsPrevious[iBin] += rMCounts[iBin];
        rMCounts[iBin] = 0;
    }
}
