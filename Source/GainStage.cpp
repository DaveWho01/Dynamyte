#include "GainStage.h"

GainStage::GainStage(float defaultInputGain)
{
	gain.setCurrentAndTargetValue(defaultInputGain);
}

GainStage::~GainStage()
{
}

void GainStage::prepareToPlay(double sr)
{
	gain.reset(sr, 0.002);
}

void GainStage::releaseResources()
{
}

void GainStage::processBlock(AudioBuffer<float>& buffer, const int numSamplesToProcess)
{
	gain.applyGain(buffer, numSamplesToProcess);
}

void GainStage::setGain(float newValue)
{
	gain.setTargetValue(Decibels::decibelsToGain(newValue));
}

