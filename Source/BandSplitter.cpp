#include "BandSplitter.h"

BandSplitter::BandSplitter()
	: lowCrossFreq(Parameters::defaultLowCrossFreq), highCrossFreq(Parameters::defaultHighCrossFreq),
	band1Mute(false), band2Mute(false), band3Mute(false)
{
	LP1.setType(dsp::LinkwitzRileyFilterType::lowpass);
	LP2.setType(dsp::LinkwitzRileyFilterType::lowpass);
	HP1.setType(dsp::LinkwitzRileyFilterType::highpass);
	HP2.setType(dsp::LinkwitzRileyFilterType::highpass);
	AP2.setType(dsp::LinkwitzRileyFilterType::allpass);

	// per testing
	//invAP1.setType(dsp::LinkwitzRileyFilterType::allpass);
	//invAP2.setType(dsp::LinkwitzRileyFilterType::allpass);

	LP1.setCutoffFrequency(lowCrossFreq);
	HP1.setCutoffFrequency(lowCrossFreq);

	LP2.setCutoffFrequency(highCrossFreq);
	HP2.setCutoffFrequency(highCrossFreq);
	AP2.setCutoffFrequency(highCrossFreq);
	
	// per testing
	//invAP1.setCutoffFrequency(1000);
	//invAP2.setCutoffFrequency(5000);
}

BandSplitter::~BandSplitter()
{
}

void BandSplitter::prepareToPlay(double sampleRate, int samplesPerBlock, int numOutputChannels)
{
	dsp::ProcessSpec spec;
	spec.numChannels = numOutputChannels;
	spec.maximumBlockSize = samplesPerBlock;
	spec.sampleRate = sampleRate;

	LP1.prepare(spec);
	LP2.prepare(spec);
	HP1.prepare(spec);
	HP2.prepare(spec);
	AP2.prepare(spec);

	
	// per testing
	//invAPBuffer.setSize(2, samplesPerBlock);
	//invAPBuffer.clear();

	//invAP1.prepare(spec);
	//invAP2.prepare(spec);
}

void BandSplitter::releaseResources()
{
}

void BandSplitter::splitSignal(AudioBuffer<float>& sourceBuffer, AudioBuffer<float>& firstBandBuffer, AudioBuffer<float>& secondBandBuffer, AudioBuffer<float>& thirdBandBuffer)
{
	const auto numChannels = sourceBuffer.getNumChannels();
	const auto numSamples = sourceBuffer.getNumSamples();
	firstBandBuffer.clear();
	secondBandBuffer.clear();
	thirdBandBuffer.clear();

	for (int ch = 0; ch < numChannels; ++ch)
	{
		firstBandBuffer.copyFrom(ch, 0, sourceBuffer, ch, 0, numSamples);
		secondBandBuffer.copyFrom(ch, 0, sourceBuffer, ch, 0, numSamples);
		// per testing
		//invAPBuffer.copyFrom(ch, 0, sourceBuffer, ch, 0, numSamples);
	}

	// blocks and context
	auto fb1Block = dsp::AudioBlock<float>(firstBandBuffer).getSubBlock(0, numSamples);
	auto fb1Context = dsp::ProcessContextReplacing<float>(fb1Block);
	auto fb2Block = dsp::AudioBlock<float>(secondBandBuffer).getSubBlock(0, numSamples);
	auto fb2Context = dsp::ProcessContextReplacing<float>(fb2Block);

	// processing
	LP1.process(fb1Context);
	AP2.process(fb1Context);

	HP1.process(fb2Context);

	// lo splitto copiandolo sul terzo buffer
	for (int ch = 0; ch < numChannels; ++ch)
	{
		thirdBandBuffer.copyFrom(ch, 0, secondBandBuffer, ch, 0, numSamples);
	}
	auto fb3Block = dsp::AudioBlock<float>(thirdBandBuffer).getSubBlock(0, numSamples);
	auto fb3Context = dsp::ProcessContextReplacing(fb3Block);

	// LP2 che agisce sul buffer in uscita da HP1
	LP2.process(fb2Context);

	// HP2 che agisce sul buffer in uscita da HP1 (quello copiato)
	HP2.process(fb3Context);



		//per testing allpass
	//auto apblock = dsp::AudioBlock<float>(invAPBuffer);
	//auto apcontext = dsp::ProcessContextReplacing(apblock);
	//invAP1.process(apcontext);
	//invAP2.process(apcontext);
}

void BandSplitter::mix(AudioBuffer<float>& destBuffer, AudioBuffer<float>& firstBandBuffer, AudioBuffer<float>& secondBandBuffer, AudioBuffer<float>& thirdBandBuffer)
{

	auto const numChannels = destBuffer.getNumChannels();
	auto const numSamples = destBuffer.getNumSamples();

	destBuffer.clear();

	for (int ch = 0; ch < numChannels; ++ch)
	{
		if (!band1Mute)
			destBuffer.addFrom(ch, 0, firstBandBuffer, ch, 0, numSamples);
		if (!band2Mute)
			destBuffer.addFrom(ch, 0, secondBandBuffer, ch, 0, numSamples);
		if (!band3Mute)
			destBuffer.addFrom(ch, 0, thirdBandBuffer, ch, 0, numSamples);
		// per testing allpass
		//FloatVectorOperations::multiply(invAPBuffer.getArrayOfWritePointers()[ch], -1.0f, numSamples);
		//destBuffer.addFrom(ch, 0, invAPBuffer, ch, 0, numSamples);
	}

}

void BandSplitter::toggleMuteBand(int nBand, float newValue)
{
	if (nBand == 1)
		band1Mute = static_cast<bool>(newValue);
	if (nBand == 2)
		band2Mute = static_cast<bool>(newValue);
	if (nBand == 3)
		band3Mute = static_cast<bool>(newValue);
}

void BandSplitter::setLowCrossoverFreq(float newValue)
{
	lowCrossFreq = newValue;
	LP1.setCutoffFrequency(lowCrossFreq);
	HP1.setCutoffFrequency(lowCrossFreq);
}

void BandSplitter::setHighCrossoverFreq(float newValue)
{
	highCrossFreq = newValue;
	LP2.setCutoffFrequency(highCrossFreq);
	HP2.setCutoffFrequency(highCrossFreq);
	AP2.setCutoffFrequency(highCrossFreq);
}


