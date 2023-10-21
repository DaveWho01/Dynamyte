#pragma once
#include <JuceHeader.h>

class GainControl
{
public:
	GainControl();
	~GainControl();

	void prepareToPlay(double sampleRate);
	void releaseResources();
	void processBlock(AudioBuffer<float>& mainBuffer, AudioBuffer<float>& scBuffer, const int numSamplesToProcess);

private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GainControl)
};