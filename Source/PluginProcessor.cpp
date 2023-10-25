/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DynamyteAudioProcessor::DynamyteAudioProcessor()
     : AudioProcessor (BusesProperties()
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                       .withInput  ("SideChain", juce::AudioChannelSet::disabled())
                       ),
    parameters(*this, &undoManager, "DynamyteParameters", Parameters::createParameterLayout())
{
    Parameters::addListenerToAllParameters(parameters, this);
    bypass = false;
    band1Bypass = false;
    band2Bypass = false;
    band3Bypass = false;
    beenCopied = true;
    lowCrossoverFreq = bandSplitter.getLowCrossoverFreq();
    highCrossoverFreq = bandSplitter.getHighCrossoverFreq();
    band1Threshold = 0.0f;
    band2Threshold = 0.0f;
    band3Threshold = 0.0f;
}

DynamyteAudioProcessor::~DynamyteAudioProcessor()
{
}

//==============================================================================
const juce::String DynamyteAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DynamyteAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DynamyteAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DynamyteAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DynamyteAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DynamyteAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DynamyteAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DynamyteAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String DynamyteAudioProcessor::getProgramName (int index)
{
    return {};
}

void DynamyteAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void DynamyteAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    sr = sampleRate;
    auto numOutputCh = getNumOutputChannels();

    firstBandBuffer.setSize(numOutputCh, samplesPerBlock);
    secondBandBuffer.setSize(numOutputCh, samplesPerBlock);
    thirdBandBuffer.setSize(numOutputCh, samplesPerBlock);

    firstBandBuffer.clear();
    secondBandBuffer.clear();
    thirdBandBuffer.clear();

    bandSplitter.prepareToPlay(sampleRate, samplesPerBlock, numOutputCh);

    b1Comp.prepareToPlay(sampleRate, samplesPerBlock);
    b2Comp.prepareToPlay(sampleRate, samplesPerBlock);
    b3Comp.prepareToPlay(sampleRate, samplesPerBlock);

    generalInputGain.prepareToPlay(sampleRate);
    generalOutputGain.prepareToPlay(sampleRate);

    bufferForFFT.prepareToPlay(sampleRate, 2048, numOutputCh);
}

void DynamyteAudioProcessor::releaseResources()
{
    firstBandBuffer.setSize(0, 0);
    secondBandBuffer.setSize(0, 0);
    thirdBandBuffer.setSize(0, 0);

    bandSplitter.releaseResources();

    b1Comp.releaseResources();
    b2Comp.releaseResources();
    b3Comp.releaseResources();

    generalInputGain.releaseResources();
    generalOutputGain.releaseResources();

}

bool DynamyteAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;

    if (layouts.inputBuses[1] != juce::AudioChannelSet::mono()
        && layouts.inputBuses[1] != juce::AudioChannelSet::stereo()
        && layouts.inputBuses[1] != juce::AudioChannelSet::disabled())
        return false;

    return true;
}

void DynamyteAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    auto mainBuffer = getBusBuffer(buffer, true, 0);
    auto scBuffer = getBusBuffer(buffer, true, 1);

    auto samplesToProcess = mainBuffer.getNumSamples();

    if (!bypass)
    {
        generalInputGain.processBlock(buffer, samplesToProcess);
        
        bandSplitter.splitSignal(mainBuffer, firstBandBuffer, secondBandBuffer, thirdBandBuffer);

        if (scBuffer.getNumChannels())
        {
            if (!band1Bypass)
                b1Comp.processBlock(firstBandBuffer, scBuffer, samplesToProcess);
            if (!band2Bypass)
                b2Comp.processBlock(secondBandBuffer, scBuffer, samplesToProcess);
            if (!band3Bypass)
                b3Comp.processBlock(thirdBandBuffer, scBuffer, samplesToProcess);
        }
        else
        {
            if (!band1Bypass)
                b1Comp.processBlock(firstBandBuffer, firstBandBuffer, samplesToProcess);
            if (!band2Bypass)
                b2Comp.processBlock(secondBandBuffer, secondBandBuffer, samplesToProcess);
            if (!band3Bypass)
                b3Comp.processBlock(thirdBandBuffer, thirdBandBuffer, samplesToProcess);
        }
        
        bandSplitter.mix(mainBuffer, firstBandBuffer, secondBandBuffer, thirdBandBuffer);

        generalOutputGain.processBlock(mainBuffer, samplesToProcess);
    }
    
    // spectrum
    if (beenCopied.get()) // se nella classe fftPerformer è stato copiato il buffer
    {
        bufferForFFT.pushNextBlock(mainBuffer);
    }


}

//==============================================================================
bool DynamyteAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* DynamyteAudioProcessor::createEditor()
{
    //return nullptr;
    return new PluginEditor(*this, parameters);
}

//==============================================================================
void DynamyteAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = parameters.copyState();
    std::unique_ptr<XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void DynamyteAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(parameters.state.getType()))
            parameters.replaceState(ValueTree::fromXml(*xmlState));
}

void DynamyteAudioProcessor::setGeneralBypass(bool newValue)
{
    bypass = newValue;
}

void DynamyteAudioProcessor::toggleBandBypass(bool newValue, int nBand)
{
    if (nBand == 1)
        band1Bypass = newValue;
    else if (nBand == 2)
        band2Bypass = newValue;
    else if (nBand == 3)
        band3Bypass = newValue;
}

double DynamyteAudioProcessor::getSampleRate()
{
    return sr;
}

void DynamyteAudioProcessor::parameterChanged(const String& paramID, float newValue)
{
    if (paramID == Parameters::nameBypass)
        setGeneralBypass(newValue);

    if (paramID == Parameters::nameGeneralInputGain)
        generalInputGain.setGain(newValue);

    if (paramID == Parameters::nameGeneralOutputGain)
        generalOutputGain.setGain(newValue);

    // multiband
    if (paramID == Parameters::nameLowCrossFreq)
    {
        bandSplitter.setLowCrossoverFreq(newValue);
        lowCrossoverFreq = bandSplitter.getLowCrossoverFreq();
    }
    
    if (paramID == Parameters::nameHighCrossFreq)
    {
        bandSplitter.setHighCrossoverFreq(newValue);
        highCrossoverFreq = bandSplitter.getHighCrossoverFreq();
    }

    if (paramID == Parameters::nameBand1Muted)
        bandSplitter.toggleMuteBand(1, newValue);

    if (paramID == Parameters::nameBand2Muted)
        bandSplitter.toggleMuteBand(2, newValue);

    if (paramID == Parameters::nameBand3Muted)
        bandSplitter.toggleMuteBand(3, newValue);

    if (paramID == Parameters::nameBypass1)
        toggleBandBypass(newValue, 1);

    if (paramID == Parameters::nameBypass2)
        toggleBandBypass(newValue, 2);

    if (paramID == Parameters::nameBypass3)
        toggleBandBypass(newValue, 3);

    // first band compressor
    if (paramID == Parameters::nameAttackTime_1)
        b1Comp.parameterChanged("AttackTime", newValue);

    if (paramID == Parameters::nameReleaseTime_1)
        b1Comp.parameterChanged("ReleaseTime", newValue);

    if (paramID == Parameters::nameInputGain_1)
        b1Comp.parameterChanged("InputGain", newValue);

    if (paramID == Parameters::nameMakeupGain_1)
        b1Comp.parameterChanged("MakeupGain", newValue);

    if (paramID == Parameters::nameThreshold_1)
    {
        b1Comp.parameterChanged("Threshold", newValue);
        band1Threshold = b1Comp.getThreshold();
    }

    if (paramID == Parameters::nameRatio_1)
        b1Comp.parameterChanged("Ratio", newValue);

    if (paramID == Parameters::nameKnee_1)
        b1Comp.parameterChanged("Knee", newValue);

    if (paramID == Parameters::nameDryWetRatio_1)
        b1Comp.parameterChanged("DryWet", newValue);


    // second band compressor
    if (paramID == Parameters::nameAttackTime_2)
        b2Comp.parameterChanged("AttackTime", newValue);

    if (paramID == Parameters::nameReleaseTime_2)
        b2Comp.parameterChanged("ReleaseTime", newValue);

    if (paramID == Parameters::nameInputGain_2)
        b2Comp.parameterChanged("InputGain", newValue);

    if (paramID == Parameters::nameMakeupGain_2)
        b2Comp.parameterChanged("MakeupGain", newValue);

    if (paramID == Parameters::nameThreshold_2)
    {
        b2Comp.parameterChanged("Threshold", newValue);
        band2Threshold = b2Comp.getThreshold();
    }

    if (paramID == Parameters::nameRatio_2)
        b2Comp.parameterChanged("Ratio", newValue);

    if (paramID == Parameters::nameKnee_2)
        b2Comp.parameterChanged("Knee", newValue);

    if (paramID == Parameters::nameDryWetRatio_2)
        b2Comp.parameterChanged("DryWet", newValue);


    // third band compressor
    if (paramID == Parameters::nameAttackTime_3)
        b3Comp.parameterChanged("AttackTime", newValue);

    if (paramID == Parameters::nameReleaseTime_3)
        b3Comp.parameterChanged("ReleaseTime", newValue);

    if (paramID == Parameters::nameInputGain_3)
        b3Comp.parameterChanged("InputGain", newValue);

    if (paramID == Parameters::nameMakeupGain_3)
        b3Comp.parameterChanged("MakeupGain", newValue);

    if (paramID == Parameters::nameThreshold_3)
    {
        b3Comp.parameterChanged("Threshold", newValue);
        band3Threshold = b3Comp.getThreshold();
    }

    if (paramID == Parameters::nameRatio_3)
        b3Comp.parameterChanged("Ratio", newValue);

    if (paramID == Parameters::nameKnee_3)
        b3Comp.parameterChanged("Knee", newValue);

    if (paramID == Parameters::nameDryWetRatio_3)
        b3Comp.parameterChanged("DryWet", newValue);
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DynamyteAudioProcessor();
}
