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

@interface popManager:NSApplication
{
    id  CA1Pop; // Neuronal Pop. Object

    id	managerWindow; // GUI window of popManager

    id	finalTimeTxtField; // GUI Text Field for duration of the simulation

    id	fEchTxtField; // GUI Text Field for sampling frequency
    float SamplingFreq; // Text Field for sampling frequency

    float *simulatedLFP; // Pointer on array for storing the simulated signal

    int nbSamples; // Number of nbSamples in simulated signal
}

+ (void)initialize;

- (void)createANewPopulation:(id)sender;

- (void)simulate:(id)sender;

- (void)saveSignalsInBinFile:(id)sender;

@end
