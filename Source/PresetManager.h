#pragma once
#include <JuceHeader.h>
#include <string>
#include "PluginProcessor.h"

class PresetManager
{
public:

	File defaultDir;
	String extension;

	PresetManager(AudioProcessorValueTreeState& APVTS, DynamyteAudioProcessor& p);
	~PresetManager();

	void loadPreset();
	void savePreset();
	String getCurrentPreset();
	void loadNextPreset();
	void loadPreviousPreset();
	StringArray getAllPresets();

private:

	AudioProcessorValueTreeState& pluginState;
	DynamyteAudioProcessor& processor;
	String currentPreset;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PresetManager)
};