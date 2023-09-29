#include "Detector.h"

Detector::Detector(float defaultAlphaAttack, float defaultAlphaRelease,
	double initSampleRate, float initSamplePeak)
	: audioSampleRate(initSampleRate), samplePeak(initSamplePeak)
{
	alphaAttack.setCurrentAndTargetValue(defaultAlphaAttack);
	alphaRelease.setCurrentAndTargetValue(defaultAlphaRelease);
}

Detector::~Detector()
{
}

void Detector::prepareToPlay(double sr)
{
	audioSampleRate = sr;
	alphaAttack.reset(sr, 0.005);
	alphaRelease.reset(sr, 0.005);
}

void Detector::releaseResources()
{
}

void Detector::processBlock(AudioBuffer<float>& buffer)
{
	auto numChannels = buffer.getNumChannels();
	auto numSamples = buffer.getNumSamples();
	auto bufferData = buffer.getArrayOfWritePointers();

	for (int ch = 0; ch < numChannels; ch++)
		FloatVectorOperations::abs(bufferData[ch], bufferData[ch], numSamples);

	for (int smp = 0; smp < numSamples; ++smp)
	{
		if (numChannels > 1)
			samplePeak = jmax(bufferData[0][smp], bufferData[1][smp]);
		else
			samplePeak = bufferData[0][smp];

		auto alphaAttackValue = alphaAttack.getNextValue();
		auto alphaReleaseValue = alphaRelease.getNextValue();

		if (samplePeak > envelopeHistory.get())
			bufferData[0][smp] = alphaAttackValue * envelopeHistory.get() + (1 - alphaAttackValue) * samplePeak;
		else
			bufferData[0][smp] = alphaReleaseValue * envelopeHistory.get() + (1 - alphaReleaseValue) * samplePeak;

		envelopeHistory.set(bufferData[0][smp]);
	}

	buffer.clear(1, 0, numSamples);
}

void Detector::setAttack(float newValue)
{
	alphaAttack.setTargetValue(exp(-1.0f / (newValue * 0.001f * audioSampleRate)));
}

void Detector::setRelease(float newValue)
{
	alphaRelease.setTargetValue(exp(-1.0f / (newValue * 0.001f * audioSampleRate)));
}
