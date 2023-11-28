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
*/

typedef struct
{
	float A;
	float B;
	float G;

	float C;
	float C1;
	float C2;
	float C3;
	float C4;
	float C5;
	float C6;
	float C7;

	float a;
	float b;
	float g;

	float v0;
	float e0;
	float r;

	float meanP;
	float sigmaP;
	float coefMultP;

}	POPULATION_PARAM; // Vector of model parameters

void saveAsTxt(char *fileName, float **data, int nbC, int nbL, float fEch, int withTime);
//------------------------------------------------------------------
void saveAsBin(char *fileName, float *data, int nbL);
//------------------------------------------------------------------
void euler(float *y, float *dydx, int n, float x, float h, float *yout, void aDerivFunction(float, float *, float *, POPULATION_PARAM *, float), POPULATION_PARAM *P );
//------------------------------------------------------------------
float sigm(float v, POPULATION_PARAM *P);
//------------------------------------------------------------------
float p(POPULATION_PARAM *P);
//------------------------------------------------------------------
float GaussianNoise(float sigma,float m);
//------------------------------------------------------------------
void derivs(float t, float *y, float *dydx, POPULATION_PARAM *P, float noise);
//------------------------------------------------------------------
float * vector(int n);
//------------------------------------------------------------------
void free_vector(float *v);
//------------------------------------------------------------------
void centre_signal(float *s,int Nbp);
