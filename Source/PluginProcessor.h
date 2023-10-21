#pragma once

#include <JuceHeader.h>
#include "Impactor.h"
#include "BandSplitter.h"
#include "FFTperformer.h"
#include "GainStage.h"
#include "CircularBuffer.h"

class DynamyteAudioProcessor  : public juce::AudioProcessor, public AudioProcessorValueTreeState::Listener
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    DynamyteAudioProcessor();
    ~DynamyteAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    void setGeneralBypass(bool newValue);
    void toggleBandBypass(bool newValue, int nBand);
    double getSampleRate();

    CircularBuffer bufferForFFT;
    Atomic<bool> beenCopied;

private:
    void parameterChanged(const String& paramID, float newValue) override;
    AudioProcessorValueTreeState parameters;

    double sr;

    BandSplitter bandSplitter;

    AudioBuffer<float> firstBandBuffer;
    AudioBuffer<float> secondBandBuffer;
    AudioBuffer<float> thirdBandBuffer;

    Impactor b1Comp;
    Impactor b2Comp;
    Impactor b3Comp;

    bool bypass;
    bool band1Bypass;
    bool band2Bypass;
    bool band3Bypass;

    GainStage generalInputGain;
    GainStage generalOutputGain;

    UndoManager undoManager;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DynamyteAudioProcessor)
};
