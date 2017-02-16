/*** Jun Allard (jun.allard@uci.edu)                   ***/

void getParams( void )
{
    
    // All distances in nm.
    // Energies in pNnm
    
    /************************ Model and numerical parameters DEFINED HERE *******************************/

    //boxSize = 64; // nm
    boxSize = 64; //nm
    // N what's? particles?  I.e. 2 ITIMs, 2 SH2, 1F domain? What happens if N>5?
    N=7;
    
    /************************ Model and numerical parameters FROM FILE *******************************/
    
    fParams = fopen(paramFileName, "r");
    
    // radius of SH2 domain, ??, radius of F domain
    fscanf(fParams,"%s %lf", tmpString, &rSH2);
    if (TALKATIVE) printf("This is rSH2: %lf\n", rSH2);
    
    fscanf(fParams,"%s %lf", tmpString, &lPocketSH2);
    if (TALKATIVE) printf("This is lPocketSH2: %lf\n", lPocketSH2);
    
    fscanf(fParams,"%s %lf", tmpString, &rF);
    if (TALKATIVE) printf("This is rF: %lf\n", rF);

    // These are either read from the command line arguments or, if absent, input here.
    // anchor to anchor separation distance
    if (rAnchorAnchor<0)
        fscanf(fParams,"%s %lf", tmpString, &rAnchorAnchor);
    else
        fscanf(fParams,"%s %lf", tmpString, &tmpDouble);
    if (TALKATIVE) printf("This is rAnchorAnchor: %lf\n", rAnchorAnchor);
    
    // Which one do we want to overrule, existence of a k parameter, or existence of contour parameter?  Relocate k's to be below contour, then they can overwrite?
    // reset x to zero below if contour length greater than zero
    //Interdomain parameters - contour length, peristence length, x, k??
    fscanf(fParams,"%s %lf", tmpString, &lContourSH2SH2);
    if (TALKATIVE) printf("This is lContourSH2SH2: %lf\n", lContourSH2SH2);
    
    fscanf(fParams,"%s %lf", tmpString, &lPersistenceSH2SH2);
    if (TALKATIVE) printf("This is lPersistenceSH2SH2: %lf\n", lPersistenceSH2SH2);
    
    fscanf(fParams,"%s %lf", tmpString, &xSH2SH2);
    if (TALKATIVE) printf("This is xSH2SH2: %lf\n", xSH2SH2);
    
    fscanf(fParams,"%s %lf", tmpString, &kSH2SH2);
    if (TALKATIVE) printf("This is kSH2SH2: %lf\n", kSH2SH2);
    
    fscanf(fParams,"%s %lf", tmpString, &lContourSH2F);
    if (TALKATIVE) printf("This is lContourSH2F: %lf\n", lContourSH2F);
    
    fscanf(fParams,"%s %lf", tmpString, &lPersistenceSH2F);
    if (TALKATIVE) printf("This is lPersistenceSH2F: %lf\n", lPersistenceSH2F);
    
    fscanf(fParams,"%s %lf", tmpString, &xSH2F);
    if (TALKATIVE) printf("This is xSH2F: %lf\n", xSH2F);
    
    fscanf(fParams,"%s %lf", tmpString, &kSH2F);
    if (TALKATIVE) printf("This is kSH2F: %lf\n", kSH2F);
    // These are either read from the command line arguments or, if absent, input here.
    // contour length from origin to ITIM
    if (lContourITIM1<0)
        fscanf(fParams,"%s %lf", tmpString, &lContourITIM1);
    else
        fscanf(fParams,"%s %lf", tmpString, &tmpDouble);
    if (TALKATIVE) printf("This is lContourITIM1: %lf\n", lContourITIM1);
    
    if (lContourITIM2<0)
        fscanf(fParams,"%s %lf", tmpString, &lContourITIM2);
    else
        fscanf(fParams,"%s %lf", tmpString, &tmpDouble);
    if (TALKATIVE) printf("This is lContourITIM2: %lf\n", lContourITIM2);
    
    // persistence length, x, k??
    if (lPersistenceITIM<0)
        fscanf(fParams,"%s %lf", tmpString, &lPersistenceITIM);
    else
        fscanf(fParams,"%s %lf", tmpString, &tmpDouble);
    if (TALKATIVE) printf("This is lPersistenceITIM: %lf\n", lPersistenceITIM);

    fscanf(fParams,"%s %lf", tmpString, &xITIM1);
    if (TALKATIVE) printf("This is xITIM1: %lf\n", xITIM1);
    
    fscanf(fParams,"%s %lf", tmpString, &xITIM2);
    if (TALKATIVE) printf("This is xITIM2: %lf\n", xITIM2);
    
    fscanf(fParams,"%s %lf", tmpString, &kITIM1);
    if (TALKATIVE) printf("This is kITIM1: %lf\n", kITIM1);
    
    fscanf(fParams,"%s %lf", tmpString, &kITIM2);
    if (TALKATIVE) printf("This is kITIM2: %lf\n", kITIM2);
    
    // membrane on/off, which domain is bound (why lf??)
    fscanf(fParams,"%s %d",  tmpString, &membraneTF);    // True or false (1 or 0)
    if (TALKATIVE) printf("This is membraneTF: %d\n", membraneTF);
    
    // binding to first and second tyrosines/ITIMs
    
    fscanf(fParams,"%s %lf", tmpString, &NSH2isY1bound);  // Set to a negative for binding energy in pNnm --- TO DO ---
    if (TALKATIVE) printf("This is NSH2isY1bound: %lf\n", NSH2isY1bound);
    
    fscanf(fParams,"%s %lf", tmpString, &CSH2isY1bound);  // Set to a negative for binding energy in pNnm --- TO DO ---
    if (TALKATIVE) printf("This is CSH2isY1bound: %lf\n", CSH2isY1bound);
    
    fscanf(fParams,"%s %lf", tmpString, &NSH2isY2bound);  // Set to a negative for binding energy in pNnm --- TO DO ---
    if (TALKATIVE) printf("This is NSH2isY1bound: %lf\n", NSH2isY2bound);
    
    fscanf(fParams,"%s %lf", tmpString, &CSH2isY2bound);  // Set to a negative for binding energy in pNnm --- TO DO ---
    if (TALKATIVE) printf("This is CSH2isY1bound: %lf\n", CSH2isY2bound);
    
    fclose(fParams);
    
    // radii
    radius[0] = 0;      // ITIM1, Giraffe1 (closest to membrane)
    radius[1] = 0;      // ITIM2, Giraffe1 (furthest from membrane)
    radius[2] = rSH2;   //NSH2
    radius[3] = rSH2;   //CSH2
    radius[4] = rF;     //F
    radius[5] = 0;      //ITIM1, Giraffe2 (closest to membrane)
    radius[6] = 0;      //ITIM2,Giraffe2 (furthest from membrane)
    
    //calculates appropriate spring constant based on persistence length and contour length parameters
    if (lContourSH2SH2 >0)
    {
        xSH2SH2 = 0;
        kSH2SH2 = 3*KBT/(lContourSH2SH2*lPersistenceSH2SH2); // CHECK THE FACTOR OF SIX IS CORRECT
        
        if (TALKATIVE) printf("This is xSH2SH2: %lf\n", xSH2SH2);
        if (TALKATIVE) printf("This is kSH2SH2: %lf\n", kSH2SH2);

    }
    if (lContourSH2F >0)
    {
        xSH2F = 0;
        kSH2F = 3*KBT/(lContourSH2F*lPersistenceSH2F);
        
        if (TALKATIVE) printf("This is xSH2F: %lf\n", xSH2F);
        if (TALKATIVE) printf("This is kSH2F: %lf\n", kSH2F);
    }

    if (lContourITIM1 >0)
    {
        xITIM1 = 0;
        kITIM1 = 3*KBT/(lContourITIM1*lPersistenceITIM);
        
        if (TALKATIVE) printf("This is xITIM1: %lf\n", xITIM1);
        if (TALKATIVE) printf("This is kITIM1: %lf\n", kITIM1);
    }
    
    if (lContourITIM2 >0)
    {
        xITIM2 = 0;
        kITIM2 = 3*KBT/(lContourITIM2*lPersistenceITIM);
        
        if (TALKATIVE) printf("This is xITIM2: %lf\n", xITIM2);
        if (TALKATIVE) printf("This is kITIM2: %lf\n", kITIM2);
    }

    //xITIM = 0;
    //kITIM = 100;
    
    //rAnchorAnchor = 5.1;
    
    // want the bond strength to be large compared to the polymer stiffness
    kBond = 10*(kITIM1+kITIM2+kSH2F+kSH2SH2);
    if (TALKATIVE) printf("This is kBond: %lf\n", kBond);
    
    /************************ bound states *******************************/
    for (i=0;i<N;i++)
        for (j=i+1;j<N;j++)
            isBound[i][j] = 0;
    
    
    isBound[0][2] = (int)NSH2isY1bound;
    isBound[0][3] = (int)CSH2isY1bound;
    isBound[1][2] = (int)NSH2isY2bound;
    isBound[1][3] = (int)CSH2isY2bound;
    
    if((isBound[0][2]==1 && isBound[1][2]) || (isBound[0][3] && isBound[1][3]))
    {
        printf("Error! Same domain bound to two ITIMs. \n");
        fflush(stdout);
        
        exit(0);
    }
    if((isBound[0][2] && isBound[0][3]) || (isBound[1][2] && isBound[1][3]))
    {
        printf("Error! Multiple domains bound to same ITIM. \n");
        fflush(stdout);
        
        exit(1);
    }
    
    /************************ other derivative parameters *******************************/

    // initial perturbation size
    dxInit = rF;
    
    // ???
    iEllipsoid = N-1;
    
    // max distance between what?
    // this definition seems arbitrary
    maxDistance = rAnchorAnchor+2*(lContourITIM1+lContourITIM2)+lContourSH2F+lContourSH2SH2;


    return;
}
