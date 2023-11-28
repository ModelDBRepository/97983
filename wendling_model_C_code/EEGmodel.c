#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "fonctionsC.h"

void main(argc,argv)
int argc;
char *argv[];
{
    /*-------------- Variables --------------------------*/
    int nb_fonc; // Number of ODEs
    float *y, *yout, *dydx; // State vector and derivatives
    float SamplingFreq; // Text Field for sampling frequency
    float *simulatedLFP; // Pointer on array for storing the simulated signal
    int nbSamples; // Number of nbSamples in simulated signal

    float t = 0., dt; // time, time step
    float finalTime; // simulation duration (in sec)
    int tt;

    POPULATION_PARAM * P; // Vector of parameters

    /*-------------- DEBUT ------------------------------*/
    if (argc != 2) 
      {
        printf("\nErreur :\n");
        printf("use: %s finalTime (in sec)\n",argv[0]);
        exit(1);
      } 
    else
      {
        finalTime = atof(argv[1]);
      }

    // Initialtisation of the Vector of parameters
    nb_fonc = 10; // Number of ODEs

    y = (float *)calloc(nb_fonc, sizeof(float)); // State vector
    yout = (float *)calloc(nb_fonc, sizeof(float)); // State vector. Output
    dydx = (float *)calloc(nb_fonc, sizeof(float)); // Vector of derivatives

    P = (POPULATION_PARAM *)malloc(1 * sizeof(POPULATION_PARAM)); // Vector of parameters

    //Model parameters. Default values
    P->A = 3.5; // EXC Parameter (excitation)
    P->B = 20.; // SDI Parameter (slow dendritic inhibition)
    P->G = 15.; // FSI Parameter (fast somatic inhibition)

    P->a = 100.; // time constants of EPSPs and IPSPs
    P->b = 30.;
    P->g = 350.;

    P->v0 = 6.; // Sigmoid parameters
    P->e0 = 2.5;
    P->r = 0.56;

    P->C1 = 1.; // Connectivity parameters (to be multiplied by P->C=135)
    P->C2 = .8;
    P->C3 = .25;
    P->C4 = .25;
    P->C5 = .3;
    P->C6 = .1;
    P->C7 = .8;

    P->C = 135.;

    P->C1 *= P->C; P->C2 *= P->C; P->C3 *= P->C; P->C4 *= P->C;
    P->C5 *= P->C; P->C6 *= P->C; P->C7 *= P->C;

    P->meanP = 3.; // Input noise parameters
    P->sigmaP = 1.;
    P->coefMultP = 30.;

    // Simulation parameters
    SamplingFreq = 512.; // user-defined (typical: 512 Hz)

    dt = 1./SamplingFreq; // period
    nbSamples = finalTime / dt; // number of samples

    // Allocation: the array for simulated EEG
    simulatedLFP = (float *)calloc(nbSamples, sizeof(float));

    for(tt=0;tt<nbSamples;tt++)
      {
        euler(y,dydx,nb_fonc,t,dt,yout,derivs,P);
        y = yout;

        t += dt;

        simulatedLFP[tt] = y[1]-y[2]-y[3];
      }

    centre_signal(simulatedLFP, nbSamples); // remove DC offset as in actual EEG (hardware filter on Acquisition Systems)

    for(tt=0;tt<100;tt++) simulatedLFP[tt] = 0.; //Remove the simulation artifact at the begining

    // save simulated signal. Binary Format
    saveAsBin("./CA1.bin", simulatedLFP, nbSamples);
    printf("Created: ./CA1.bin\n");

    // save simulated signal. ascii Format
    saveAsTxt("./CA1.txt", &simulatedLFP, 1, nbSamples, SamplingFreq, 1);
    printf("Created: ./CA1.txt\n");

    // Free memory
    free(y);
    free(yout);
    free(dydx);
    free(simulatedLFP);
}
