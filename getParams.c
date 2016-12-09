/*** Jun Allard (jun.allard@uci.edu)                   ***/

void getParams( void )
{
    
    // All distances in nm.
    // Energies in pNnm
    
    /************************ Model and numerical parameters DEFINED HERE *******************************/

    boxSize = 64; // nm
    // N what's? particles?  I.e. 2 ITIMs, 2 SH2, 1F domain? What happens if N>5?
    N=5;
    
    /************************ Model and numerical parameters FROM FILE *******************************/
    
    fParams = fopen(paramFileName, "r");
    
    // radius of SH2 domain, ??, radius of F domain
    fscanf(fParams,"%s %lf", tmpString, &rSH2);
    fscanf(fParams,"%s %lf", tmpString, &lPocketSH2);
    fscanf(fParams,"%s %lf", tmpString, &rF);

    // These are either read from the command line arguments or, if absent, input here.
    // anchor to anchor separation distance
    if (rAnchorAnchor<0)
        fscanf(fParams,"%s %lf", tmpString, &rAnchorAnchor);
    else
        fscanf(fParams,"%s %lf", tmpString, &tmpDouble);

    //Interdomain parameters - contour length, peristence length, x, k??
    fscanf(fParams,"%s %lf", tmpString, &lContourSH2SH2);
    fscanf(fParams,"%s %lf", tmpString, &lPersistenceSH2SH2);
    fscanf(fParams,"%s %lf", tmpString, &xSH2SH2);
    fscanf(fParams,"%s %lf", tmpString, &kSH2SH2);
    fscanf(fParams,"%s %lf", tmpString, &lContourSH2F);
    fscanf(fParams,"%s %lf", tmpString, &lPersistenceSH2F);
    fscanf(fParams,"%s %lf", tmpString, &xSH2F);
    fscanf(fParams,"%s %lf", tmpString, &kSH2F);

    // These are either read from the command line arguments or, if absent, input here.
    // contour length from origin to ITIM
    if (lContourITIM<0)
        fscanf(fParams,"%s %lf", tmpString, &lContourITIM);
    else
        fscanf(fParams,"%s %lf", tmpString, &tmpDouble);
    
    // persistence length, x, k??
    fscanf(fParams,"%s %lf", tmpString, &lPersistenceITIM);
    fscanf(fParams,"%s %lf", tmpString, &xITIM);
    fscanf(fParams,"%s %lf", tmpString, &kITIM);
    
    
    // membrane on/off, which domain is bound (why lf??)
    fscanf(fParams,"%s %d",  tmpString, &membraneTF);    // True or false (1 or 0)
    fscanf(fParams,"%s %lf", tmpString, &NSH2isY1bound);  // Set to a negative for binding energy in pNnm --- TO DO ---
    fscanf(fParams,"%s %lf", tmpString, &CSH2isY1bound);  // Set to a negative for binding energy in pNnm --- TO DO ---
    
    fclose(fParams);
    
    // radii
    
    // radii of what???
    radius[0] = 0;
    radius[1] = 0;
    radius[2] = rSH2;
    radius[3] = rSH2;
    radius[4] = rF;
    
    // what is this part doing?
    if (lContourSH2SH2 >0)
    {
        xSH2SH2 = 0;
        kSH2SH2 = 3*KBT/(lContourSH2SH2*lPersistenceSH2SH2); // CHECK THE FACTOR OF SIX IS CORRECT
    }
    if (lContourSH2F >0)
    {
        xSH2F = 0;
        kSH2F = 3*KBT/(lContourSH2F*lPersistenceSH2F);
    }

    if (lContourITIM >0)
    {
        xITIM = 0;
        kITIM = 3*KBT/(lContourITIM*lPersistenceITIM);
    }

    //xITIM = 0;
    //kITIM = 100;
    
    //rAnchorAnchor = 5.1;
    
    kBond = 10*(kITIM+kSH2F+kSH2SH2);
    
    /************************ bound states *******************************/
    for (i=0;i<N;i++)
        for (j=i+1;j<N;j++)
            isBound[i][j] = 0;
    
    isBound[0][2] = (int)NSH2isY1bound;
    isBound[0][3] = (int)CSH2isY1bound;

    
    /************************ other derivative parameters *******************************/

    // initial perturbation size
    dxInit = rF;
    
    // ???
    iEllipsoid = N-1;
    
    // max distance between what?
    maxDistance = rAnchorAnchor+2*lContourITIM+lContourSH2F+lContourSH2SH2;


    return;
}
