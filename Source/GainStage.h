#pragma once
#include <JuceHeader.h>
#include "PluginParameters.h"

class GainStage
{
public:
	GainStage(float defaultInputGain = Parameters::defaultInputGain);
	~GainStage();

	void prepareToPlay(double sr);
	void releaseResources();
	void processBlock(AudioBuffer<float>& buffer, const int numSamplesToProcess);

	void setGain(float newValue);

private:

	SmoothedValue<float, ValueSmoothingTypes::Linear> gain;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GainStage)
};