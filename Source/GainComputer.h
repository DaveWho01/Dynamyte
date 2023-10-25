#pragma once
#include <JuceHeader.h>
#include "PluginParameters.h"

class GainComputer
{
public:
	GainComputer
	(
		float defaultThreshold = Parameters::defaultThreshold,
		float defaultRatio = Parameters::defaultRatio,
		float defaultKneeWidth = Parameters::defaultKnee
	);
	~GainComputer();

	void prepareToPlay(double sampleRate);
	void releaseResources();
	void processBlock(AudioBuffer<float>& buffer, const int numSamplesToProcess);

	void setThreshold(float newValue);
	void setRatio(float newValue);
	void setKnee(float newValue);

	float getThreshold();

private:

	SmoothedValue<float, ValueSmoothingTypes::Linear> threshold;
	SmoothedValue<float, ValueSmoothingTypes::Multiplicative> ratio;
	SmoothedValue<float, ValueSmoothingTypes::Linear> kneeWidth;

	float inGain;
	float outGain;
	float invRatio;
	float halfKnee;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GainComputer)
};