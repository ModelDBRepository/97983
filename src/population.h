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

#import <AppKit/AppKit.h>
#include "fonctionsC.h"

@interface neuronalPop:NSObject
{
    id	parametersWindow; // GUI Parameter window of neuronal pop object

    id	ATxtField; // GUI. Text Field for A parameter (=EXC)
    id	BTxtField; // GUI. Text Field for B parameter (=SDI)
    id	GTxtField; // GUI. Text Field for G parameter (=FSI)
    id	aTxtField; // etc ...
    id	bTxtField;
    id	gTxtField;

    id	CTxtField;
    id	C1TxtField;
    id	C2TxtField;
    id	C3TxtField;
    id	C4TxtField;
    id	C5TxtField;
    id	C6TxtField;
    id	C7TxtField;

    id	coefMultPTxtField; // GUI. Text Fields for noise parameters
    id	moyPTxtField;
    id	sigmaPTxtField;

    int nb_fonc; // Number of ODEs
    float *y, *yout, *dydx; // State vector and derivatives

    POPULATION_PARAM * P; // Vector of parameters
}

- init;

- (void)setParameters; // Apply user-defined parameters defined in the GUI
- (void)reset; // Reset the state vector
- (float) EEGoutput; // Model output at time t
- (void)integrate:(float)t :(float)dt; // Numerical integration of the set of ODEs
- (id) parametersWindow; // GUI parameter window
- (void)dealloc;

- (float)A; // returns parameter A (EXC) defined in the GUI
- (float)B; // returns parameter B (SDI) defined in the GUI
- (float)G; // returns parameter G (FSI) defined in the GUI
- (float)a; // etc...
- (float)b;
- (float)g;
- (float)C;
- (float)C1;
- (float)C2;
- (float)C3;
- (float)C4;
- (float)C5;
- (float)C6;
- (float)C7;

- (float)meanP;
- (float)sigmaP;
- (float)coefMultP;

@end
