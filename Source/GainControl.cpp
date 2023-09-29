#include "GainControl.h"

GainControl::GainControl()
{
}

GainControl::~GainControl()
{
}

void GainControl::prepareToPlay(double sampleRate)
{
}

void GainControl::releaseResources()
{
}

void GainControl::processBlock(AudioBuffer<float>& mainBuffer, AudioBuffer<float>& scBuffer)
{
    auto numSamples = jmin(mainBuffer.getNumSamples(), scBuffer.getNumSamples());
    auto mainNumChannels = mainBuffer.getNumChannels();

    auto mainData = mainBuffer.getArrayOfWritePointers();
    auto scData = scBuffer.getArrayOfWritePointers();

    for (int smp = 0; smp < numSamples; ++smp)
        scData[0][smp] = Decibels::decibelsToGain(scData[0][smp]);

    for (int ch = 0; ch < mainNumChannels; ++ch)
        FloatVectorOperations::multiply(mainData[ch], scData[0], numSamples);
}


