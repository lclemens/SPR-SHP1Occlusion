/*** Jun Allard jun.allard@uci.edu                   ***/

#define TWISTER genrand_real3()

#define NMAX                400
#define NTMAX               1e10
#define NTADAPT             20000
#define KSCRITICAL          0.002
#define NTCHECK             1e6
#define NBINS               400
#define PI                  3.14159265359
#define INF                 1e14
#define KBT                 4.2
#define DCHIMIN             0.1
#define concentrationBin    0.2
#define DXMAX               1
#define DXMIN               0.01

// Model parameters
double boxSize;
double radius[NMAX];
double r0[NMAX];
double viscosity;

double rSH2, lPocketSH2, rF;
double lContourSH2SH2, lPersistenceSH2SH2, kSH2SH2, xSH2SH2,
       lContourSH2F,   lPersistenceSH2F,   kSH2F,   xSH2F,
       lContourITIM,   lPersistenceITIM,   kITIM,   xITIM;
double rAnchorAnchor;
double kBond;

int nSH2SH2, n1, n2;

// Model options
int membraneTF;
double NSH2isY1bound, CSH2isY1bound;

// Numerical parameters


// Simulation variables
long nt;
int prematureReturn;

double maxDistance;

double dx, dxInit;
double boxMullerTmp1, boxMullerTmp2;

double lPocketHere;
double rLocal[3];

int occlusionTF;
int isBound[NMAX][NMAX];

FILE *fList;

long N, ntNextStationarityCheck, iBin, iSite, stericOcclusion;
double ksStatistic;
double rM;
long rMCounts[NBINS], rMCountsPrevious[NBINS];
long iseed;

double rPropose[NMAX][3];
double r[NMAX][3];
double rBound[3];
double norm;
double RGlobal[3][3], RLocal[3][3];
double e1_dot_t, e2_dot_t, e2_dot_e1;

long proposals[2], accepts[2], i, j, iPropose, ix, iParam, ntNextStationarityCheck, iEllipsoid;

double E, ENew, rate[2], dChi[2], dChiHere, ksStatistic;

int convergedTF, constraintSatisfiedTF, verboseTF;

// state variables

double particleDistances[NMAX][NMAX], particleDistances_1Bar[NMAX][NMAX], particleDistances_2Bar[NMAX][NMAX];

// input/output files
char paramFileSuffix[100], paramFileName[100], tmpString[100], runName[100];
FILE *fParams;
FILE *fPosition, *fSummary, *fScratch;
double tmpDouble;

// data collection
int isBound1, isBound2, isBoundComplex;
double tReact1, tReact2, tReactComplex;

long proximity_long[NMAX][NMAX];
double proximity[NMAX][NMAX], effectiveConcentration[NMAX][NMAX];

FILE *fBond1On, *fBond1Off, *fBond2On, *fBond2Off, *fBondComplexOn, *fBondComplexOff;


