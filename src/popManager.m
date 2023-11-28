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

popManager. Written in Objective C
Allows for instantiation of an object that manages a population of neurons:
- Create a neuronalPop object (called CA1Pop)
- Simulate a signal from this population ("simulate" method)
*/

#import "popManager.h"
#import "population.h"

@implementation popManager

+ (void)initialize
{
    [super initialize];
}

- (void)awakeFromNib
{
    [managerWindow makeKeyAndOrderFront:self];
    simulatedLFP = NULL;
}

- (void)createANewPopulation:(id)sender
{
    if (!CA1Pop) 

    {
	CA1Pop = [[neuronalPop alloc] init]; // create population
        [managerWindow setTitle:@"Neuronal Population CA1"];

        [NSBundle loadNibNamed:@"population.nib" owner:CA1Pop]; // load the parameter interface for created population
    }
    [[CA1Pop parametersWindow] makeKeyAndOrderFront:self]; // display the parameter interface of CA1 pop
}

- (void)saveSignalsInBinFile:(id)sender
{
    FILE *fp;

    // Descriptor for the binary file
    fp = (FILE *)fopen("C:/tmp/CA1.des","wt");
    fprintf(fp,"[patient] SIMUL_CA1\n[date] 00/00/0000\n[time] 00:00:00\n[samplingfreq] %f\n[nbsamples] %d\n[nbchannels] %d\n[channelnames] :\n EEG ------", SamplingFreq, nbSamples, 1);
    fclose(fp);

    // Simulated signal. Binary Format
    saveAsBin("C:/tmp/CA1.bin", simulatedLFP, nbSamples);
}

- (void)simulate:(id)sender
{
    float t = 0., dt;
    float finalTime;
    int tt;

    //------------------------------------------------
    SamplingFreq = [fEchTxtField floatValue]; // user-defined via GUI (typical: 512 Hz)
    finalTime=[finalTimeTxtField floatValue]; // user-defined via GUI (in sec)

    dt = 1./SamplingFreq;
    nbSamples = finalTime / dt;

    [CA1Pop reset];
    [CA1Pop setParameters];

    if (simulatedLFP) free(simulatedLFP);
    simulatedLFP = (float *)calloc(nbSamples, sizeof(float));

    //------Simulation Loop-------------------------
    for(tt=0;tt<nbSamples;tt++)
      {
        [CA1Pop integrate:t:dt];

        t += dt;

        simulatedLFP[tt] = [CA1Pop EEGoutput];
      }
    //--------------------------------

    centre_signal(simulatedLFP, nbSamples); // remove DC offset as in actual EEG (hardware filter on Deltamed System)

    [self saveSignalsInBinFile:self];
}

@end
