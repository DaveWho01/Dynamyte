#include "Impactor.h"
#include "PluginParameters.h"

//==============================================================================
Impactor::Impactor()
{
}

Impactor::~Impactor()
{
}

void Impactor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    auxBuffer.setSize(2, samplesPerBlock);
    auxBuffer.clear();
    inputGain.prepareToPlay(sampleRate);
    dryWet.prepareToPlay(sampleRate, samplesPerBlock);
    peakDetector.prepareToPlay(sampleRate);
    gainComputer.prepareToPlay(sampleRate);
    gainControl.prepareToPlay(sampleRate);
    makeupGain.prepareToPlay(sampleRate);
}

void Impactor::releaseResources()
{
    inputGain.releaseResources();
    dryWet.releaseResources();
    peakDetector.releaseResources();
    auxBuffer.setSize(0, 0);
    gainComputer.releaseResources();
    gainControl.releaseResources();
    makeupGain.releaseResources();
}

void Impactor::processBlock(AudioBuffer<float>& mainBuffer, AudioBuffer<float>& scBuffer, const int numSamplesToProcess)
{
    dryWet.copyDrySignal(mainBuffer, numSamplesToProcess);

    inputGain.processBlock(mainBuffer, numSamplesToProcess);
    
    const int numScChannels = scBuffer.getNumChannels();

    auxBuffer.clear();
    for (int ch = 0; ch < numScChannels; ++ch)
        auxBuffer.addFrom(ch, 0, scBuffer, ch, 0, numSamplesToProcess, 1.0f);

    peakDetector.processBlock(auxBuffer, numSamplesToProcess);

    gainComputer.processBlock(auxBuffer, numSamplesToProcess);

    gainControl.processBlock(mainBuffer, auxBuffer, numSamplesToProcess);

    makeupGain.processBlock(mainBuffer, numSamplesToProcess);

    dryWet.merge(mainBuffer, numSamplesToProcess);
    
}

void Impactor::parameterChanged(const String paramID, float newValue)
{
    if (paramID == "AttackTime")
        peakDetector.setAttack(newValue);

    if (paramID == "ReleaseTime")
        peakDetector.setRelease(newValue);

    if (paramID == "InputGain")
        inputGain.setGain(newValue);

    if (paramID == "MakeupGain")
        makeupGain.setGain(newValue);

    if (paramID == "Threshold")
        gainComputer.setThreshold(newValue);

    if (paramID == "Ratio")
        gainComputer.setRatio(newValue);

    if (paramID == "Knee")
        gainComputer.setKnee(newValue);

    if (paramID == "DryWet")
        dryWet.setDryWetRatio(newValue);
}
