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

neuronalPop. Written in Objective C
Allows for instantiation of a population of neurons and integration of the corresponding set of ODEs.
*/

#import "population.h"

@implementation neuronalPop

- init
{
    [super init];

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

    P->C1 = 1.; // Connectivity parameters (multiplied by C=135)
    P->C2 = .8;
    P->C3 = .25;
    P->C4 = .25;
    P->C5 = .3;
    P->C6 = .1;
    P->C7 = .8;
    P->C = 135.;

    P->meanP = 3.; // Input noise parameters
    P->sigmaP = 1.;
    P->coefMultP = 30.;

    return self;
}

- (void)setParameters
{
    //User-defined values read from Graphical Inferface
    P->A = [self A]; P->B = [self B]; P->G = [self G];P->C = [self C];
    P->C1 = [self C1]; P->C2 = [self C2]; P->C3 = [self C3]; P->C4 = [self C4];P->C5 = [self C5];P->C6 = [self C6];P->C7 = [self C7];

    P->a = [self a];
    P->b = [self b];
    P->g = [self g];

    P->meanP = [self meanP];
    P->sigmaP = [self sigmaP];
    P->coefMultP = [self coefMultP];
}

//----------Returns user-defined parameters from GUI-----------------
- (float)A { return [ATxtField floatValue]; }
- (float)B { return [BTxtField floatValue]; }
- (float)G { return [GTxtField floatValue]; }
- (float)a { return [aTxtField floatValue]; }
- (float)b { return [bTxtField floatValue]; }
- (float)g { return [gTxtField floatValue]; }

- (float)C { return [CTxtField floatValue]; }
- (float)C1 { return [C1TxtField floatValue] * [CTxtField floatValue]; }
- (float)C2 { return [C2TxtField floatValue] * [CTxtField floatValue]; }
- (float)C3 { return [C3TxtField floatValue] * [CTxtField floatValue]; }
- (float)C4 { return [C4TxtField floatValue] * [CTxtField floatValue]; }
- (float)C5 { return [C5TxtField floatValue] * [CTxtField floatValue]; }
- (float)C6 { return [C6TxtField floatValue] * [CTxtField floatValue]; }
- (float)C7 { return [C7TxtField floatValue] * [CTxtField floatValue]; }

- (float)meanP { return [moyPTxtField floatValue]; }
- (float)sigmaP { return [sigmaPTxtField floatValue]; }
- (float)coefMultP { return [coefMultPTxtField floatValue]; }

//----------------------------------------------------------------
- (float) EEGoutput
{
    return (y[1]-y[2]-y[3]); // Model ouptut = Summation of avg EPSP and IPSPs
}

//----------------------------------------------------------------
- (void)integrate:(float)t :(float)dt
{
    euler(y,dydx,nb_fonc,t,dt,yout,derivs,P);
    y = yout;
}
//----------------------------------------------------------------
- (void)reset
{
    int i;

    for(i=0;i<nb_fonc;i++)
      {
        y[i] = 0.;
        yout[i] = 0.;
        dydx[i] = 0.;
      }
}
//----------------------------------------------------------------
- (id) parametersWindow
{
    return parametersWindow;
}

//----------------------------------------------------------------
- (void)dealloc
{	
    free(y);
    free(yout);
    free(dydx);
    free(P);

    [super dealloc];
}

@end
