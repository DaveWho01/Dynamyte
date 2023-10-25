#include "GainComputer.h"

GainComputer::GainComputer(float defaultThreshold, float defaultRatio, float defaultKneeWidth)
{
	threshold.setCurrentAndTargetValue(defaultThreshold);
	ratio.setCurrentAndTargetValue(defaultRatio);
	kneeWidth.setCurrentAndTargetValue(defaultKneeWidth);
	halfKnee = defaultKneeWidth * 0.5f;
	inGain = 0.0f;
	invRatio = 1 / defaultRatio;
	outGain = 0.0f;
}

GainComputer::~GainComputer()
{
}

void GainComputer::prepareToPlay(double sampleRate)
{
	threshold.reset(sampleRate, 0.01);
	ratio.reset(sampleRate, 0.01);
	kneeWidth.reset(sampleRate, 0.01);
}

void GainComputer::releaseResources()
{
}

void GainComputer::processBlock(AudioBuffer<float>& buffer, const int numSamplesToProcess)
{
	auto bufferData = buffer.getArrayOfWritePointers();

	for (int smp = 0; smp < numSamplesToProcess; ++smp)
	{
		const auto thresholdValue = threshold.getNextValue();
		const auto ratioValue = ratio.getNextValue();
		const auto kneeWidthValue = kneeWidth.getNextValue();

		inGain = Decibels::gainToDecibels(bufferData[0][smp]);

		outGain = 0.0f;

		const auto overshoot = inGain - thresholdValue;

		invRatio = 1 / ratioValue;
		halfKnee = kneeWidthValue * 0.5f;

		if ((2 * overshoot) < -kneeWidthValue)
		{
			outGain = inGain;
		}
		else if ((2 * abs(overshoot)) <= kneeWidthValue)
		{
			outGain = inGain + (invRatio - 1) * ((overshoot + halfKnee) * (overshoot + halfKnee)) / (2 * kneeWidthValue);
		}
		else if ((2 * overshoot) > kneeWidthValue)
		{
			outGain = thresholdValue + (overshoot)*invRatio;
		}
		bufferData[0][smp] = outGain - inGain;
	}
}

void GainComputer::setThreshold(float newValue)
{
	threshold.setTargetValue(newValue);
}

void GainComputer::setRatio(float newValue)
{
	ratio.setTargetValue(newValue);
}

void GainComputer::setKnee(float newValue)
{
	kneeWidth.setTargetValue(newValue);
}

float GainComputer::getThreshold()
{
	return threshold.getTargetValue();
}
