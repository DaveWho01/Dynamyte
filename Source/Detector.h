#pragma once
#include <JuceHeader.h>
#include "PluginParameters.h"

class Detector
{
public:
    Detector
    (
        float defaultAlphaAttack = Parameters::defaultAlphaAttack,
        float defaultAlphaRelease = Parameters::defaultAlphaRelease,
        double initSampleRate = Parameters::initSampleRate,
        float initSamplePeak = Parameters::initSamplePeak
    );
    ~Detector();

    void prepareToPlay(double sr);
    void releaseResources();
    void processBlock(AudioBuffer<float>& buffer, const int numSamplesToProcess);

    void setAttack(float newValue);
    void setRelease(float newValue);

private:

    Atomic<float> envelopeHistory;

    SmoothedValue<float, ValueSmoothingTypes::Multiplicative> alphaAttack;
    SmoothedValue<float, ValueSmoothingTypes::Multiplicative> alphaRelease;
    float samplePeak;
    double audioSampleRate;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Detector)
};