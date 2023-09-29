#pragma once
#include <JuceHeader.h>
#include "PluginParameters.h"

class BandSplitter
{
public:

	BandSplitter();
	~BandSplitter();

	void prepareToPlay(double sampleRate, int samplesPerBlock, int numOutputChannels);
	void releaseResources();
	void splitSignal(AudioBuffer<float>& sourceBuffer,
		AudioBuffer<float>& firstBandBuffer,
		AudioBuffer<float>& secondBandBuffer,
		AudioBuffer<float>& thirdBandBuffer
	);

	void mix(AudioBuffer<float>& destBuffer,
		AudioBuffer<float>& firstBandBuffer,
		AudioBuffer<float>& secondBandBuffer,
		AudioBuffer<float>& thirdBandBuffer
	);

	void toggleMuteBand(int nBand, float newValue);

	void setLowCrossoverFreq(float newValue);
	void setHighCrossoverFreq(float newValue);

private:

	dsp::LinkwitzRileyFilter<float> LP1, HP1, AP2, LP2, HP2;

	float lowCrossFreq;
	float highCrossFreq;

	bool band1Mute;
	bool band2Mute;
	bool band3Mute;

	// per testing
	//dsp::LinkwitzRileyFilter<float> invAP1, invAP2;
	//AudioBuffer<float> invAPBuffer;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BandSplitter)

};