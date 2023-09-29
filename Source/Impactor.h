#pragma once

#include <JuceHeader.h>
#include "Detector.h"
#include "GainStage.h"
#include "GainComputer.h"
#include "GainControl.h"
#include "ImpactorDryWet.h"


class Impactor
{
public:
    Impactor();
    ~Impactor();

    void prepareToPlay(double sampleRate, int samplesPerBlock);
    void releaseResources();

    void processBlock(AudioBuffer<float>& mainBuffer, AudioBuffer<float>& scBuffer);
    void parameterChanged(const String paramID, float newValue);

private:


    AudioBuffer<float> auxBuffer;

    GainStage inputGain;
    Detector peakDetector;
    GainComputer gainComputer;
    GainControl gainControl;
    GainStage makeupGain;
    ImpactorDryWet dryWet;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Impactor)
};
