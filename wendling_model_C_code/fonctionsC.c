/* Model described in
Authors: Wendling F, Hernandez A, Bellanger JJ, Chauvel P, Bartolomei F
Title: Interictal to ictal transition in human temporal lobe epilepsy:
insights from a computational model of intracerebral EEG.
Journal: J Clin Neurophysiol. 2005 Oct;22(5):343-56.
================================================
 Fabrice WENDLING
================================================
 Laboratoire Traitement du Signal et de L'Image
 INSERM U642 - UNIVERSITE DE RENNES 1
 Campus de Beaulieu
 35042 Rennes Cedex - France -
 http://perso.univ-rennes1.fr/fabrice.wendling/
================================================

fonctionsC. Written in ANSI C
All functions that actually define the model.
*/

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "fonctionsC.h"

//-----------------------------------------------------------------------
void saveAsBin(char *fileName, float *data, int nbL)
{
    FILE *fpBin;

    fpBin = (FILE*)fopen(fileName,"wb");

    fwrite(data, sizeof(float), nbL, fpBin);

    fclose(fpBin);
}
//-----------------------------------------------------------------------
void saveAsTxt(char *fileName, float **data, int nbC, int nbL, float fEch, int withTime)
{
    int i,j;
    FILE *fpTxt;

    fpTxt = (FILE*)fopen(fileName,"wt");

    for(i=0;i<nbL;i++){
        if (withTime) fprintf(fpTxt,"%f",(float)i/fEch);
        for(j=0;j<nbC;j++){
            fprintf(fpTxt," %.6f",data[j][i]);
        }
        fprintf(fpTxt,"\n");
    }
    fclose(fpTxt);
}


//------------------------------------------------------------------
float *vector(int n)
{
    float *v;
    v = (float*) malloc(n * sizeof(float) );
    return v;
}
//------------------------------------------------------------------
void free_vector(float *v)
{
    free (v);
}
//------------------------------------------------------------------
float sigm(float v, POPULATION_PARAM *P)
{
    float e0, v0, r;

    v0 = P->v0; e0 = P->e0; r = P->r;

    return 2*e0/(1+exp(r*(v0-v))) ;
}
//------------------------------------------------------------------
float p(POPULATION_PARAM *P)
{
    float x, coefMult, m, sigma;

    m = P->meanP; sigma = P->sigmaP;coefMult = P->coefMultP;

    x = coefMult * GaussianNoise(sigma,m);

    return x;
}
//----------------------------------------------------------------------
float GaussianNoise(float sigma,float m)
{
    float gauss, alea1, alea2;
    double M_PI=3.1415926535897932384626433832795;

    alea1 = (float)rand()/(float)(RAND_MAX+1);
    alea2 = (float)rand()/(float)(RAND_MAX+1);
    gauss = sigma * sqrt(-2.0*log(1.0-alea1)) * cos(2.0*M_PI*alea2)+m;

    return(gauss);
}
//------------------------------------------------------------------
void derivs(float t, float *y, float *dydx, POPULATION_PARAM *P, float noise)
{
    float A, B, G, C, C1, C2, C3, C4, C5, C6, C7, a, b, g;

    A = P->A; B = P->B; G = P->G; C = P->C;
    C1 = P->C1; C2 = P->C2; C3 = P->C3; C4 = P->C4;C5 = P->C5;C6 = P->C6;C7 = P->C7;
    a = P->a; b = P->b;g = P->g;

    dydx[0] = y[5];

    dydx[5] = A * a * sigm(y[1]-y[2]-y[3],P) - 2 * a * y[5] - a * a * y[0];

    dydx[1] = y[6];

    dydx[6] =  A * a * ( noise + C2 * sigm(C1* y[0],P) ) - 2 * a * y[6] - a*a * y[1];

    dydx[2] = y[7];

    dydx[7] = B * b * ( C4 * sigm(C3 * y[0],P) ) - 2 * b * y[7] - b*b * y[2];

    dydx[3] = y[8];

    dydx[8] = G * g * ( C7 * sigm((C5 * y[0] - C6 * y[4]),P) ) - 2 * g * y[8] - g*g * y[3];

    dydx[4] = y[9];

    dydx[9] = B * b * ( sigm(C3 * y[0],P) ) - 2 * b * y[9] - b*b * y[4];
}
//------------------------------------------------------------------
/* Numerical Integration. Euler Method */
//------------------------------------------------------------------
void euler(float *y, float *dydx, int n, float x, float h, float *yout, void aDerivFunction(float, float *, float *, POPULATION_PARAM *, float), POPULATION_PARAM *P )
{
    int i;
    float noise;

    noise = p(P); //p(t) is the input noise in the model

    aDerivFunction(x,y,dydx,P,noise);

    for (i=0;i<n;i++)
        yout[i]=y[i] + h * dydx[i];
}
//------------------------------------------------------------------
void centre_signal(float *s,int Nbp)
{
    float Moy=0.0;
    int i;

    for(i=0; i < Nbp; i++)
        Moy += s[i];

    Moy /= Nbp;

    for(i=0; i < Nbp; i++)
        s[i] = s[i]-Moy;
}
