#include "ImpactorDryWet.h"

ImpactorDryWet::ImpactorDryWet(float defaultDWRatio)
    : dryWetRatio(defaultDWRatio)
{
    dryLevel.setCurrentAndTargetValue(defaultDWRatio);
    wetLevel.setCurrentAndTargetValue(defaultDWRatio);
}

ImpactorDryWet::~ImpactorDryWet()
{
}

void ImpactorDryWet::prepareToPlay(const double sr, const int maxNumSamples)
{
    drySignal.setSize(2, maxNumSamples);
    drySignal.clear();

    dryLevel.reset(sr, 0.02f);
    wetLevel.reset(sr, 0.02f);

    updateInternalState();
}

void ImpactorDryWet::releaseResources()
{
    drySignal.setSize(0, 0);
}

void ImpactorDryWet::copyDrySignal(const AudioBuffer<float>& buffer)
{
    const auto numCh = buffer.getNumChannels();
    const auto numSamples = buffer.getNumSamples();

    for (int ch = 0; ch < numCh; ++ch)
        drySignal.copyFrom(ch, 0, buffer, ch, 0, numSamples);
}

void ImpactorDryWet::merge(AudioBuffer<float> buffer)
{
    const auto numCh = buffer.getNumChannels();
    const auto numSamples = buffer.getNumSamples();

    wetLevel.applyGain(buffer, numSamples);
    dryLevel.applyGain(drySignal, numSamples);


    for (int ch = 0; ch < numCh; ++ch)
        buffer.addFrom(ch, 0, drySignal, ch, 0, numSamples);
}

void ImpactorDryWet::setDryWetRatio(const float newValue)
{
    dryWetRatio = newValue * 0.01f;
    updateInternalState();
}

void ImpactorDryWet::updateInternalState()
{
    dryLevel.setTargetValue(sqrt(1 - dryWetRatio));
    wetLevel.setTargetValue(sqrt(dryWetRatio));
}
