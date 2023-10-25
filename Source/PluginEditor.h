/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 7.0.5

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "DynamyteTheme.h"
#include "CustomGUIclasses.h"
#include "PresetManager.h"
#include "IconPath.h"

typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;

#define HIDDEN      0.5f
#define VISIBLE     1.0f
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class PluginEditor  : public juce::AudioProcessorEditor,
                      public juce::Slider::Listener,
                      public juce::Button::Listener
{
public:
    //==============================================================================
    PluginEditor (DynamyteAudioProcessor& p, AudioProcessorValueTreeState& vts);
    ~PluginEditor() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void setSectionOpacity(std::vector<std::unique_ptr<juce::Slider>>& slidersToHide, bool shouldHide);
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void sliderValueChanged (juce::Slider* sliderThatWasMoved) override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

    DynamyteAudioProcessor& processor;
    AudioProcessorValueTreeState& valueTreeState;
    DynamyteTheme dynamyteTheme;

    // band 1
    std::unique_ptr<SliderAttachment> b1_inputGainAttachment;
    std::unique_ptr<SliderAttachment> b1_makeupGainAttachment;
    std::unique_ptr<SliderAttachment> b1_thresholdAttachment;
    std::unique_ptr<SliderAttachment> b1_ratioAttachment;
    std::unique_ptr<SliderAttachment> b1_kneeAttachment;
    std::unique_ptr<SliderAttachment> b1_attackAttachment;
    std::unique_ptr<SliderAttachment> b1_releaseAttachment;
    std::unique_ptr<SliderAttachment> b1_dryWetAttachment;
    std::unique_ptr<ButtonAttachment> b1_muteAttachment;
    std::unique_ptr<ButtonAttachment> b1_bypassAttachment;

    // band 2
    std::unique_ptr<SliderAttachment> b2_inputGainAttachment;
    std::unique_ptr<SliderAttachment> b2_makeupGainAttachment;
    std::unique_ptr<SliderAttachment> b2_thresholdAttachment;
    std::unique_ptr<SliderAttachment> b2_ratioAttachment;
    std::unique_ptr<SliderAttachment> b2_kneeAttachment;
    std::unique_ptr<SliderAttachment> b2_attackAttachment;
    std::unique_ptr<SliderAttachment> b2_releaseAttachment;
    std::unique_ptr<SliderAttachment> b2_dryWetAttachment;
    std::unique_ptr<ButtonAttachment> b2_muteAttachment;
    std::unique_ptr<ButtonAttachment> b2_bypassAttachment;

    // band 3
    std::unique_ptr<SliderAttachment> b3_inputGainAttachment;
    std::unique_ptr<SliderAttachment> b3_makeupGainAttachment;
    std::unique_ptr<SliderAttachment> b3_thresholdAttachment;
    std::unique_ptr<SliderAttachment> b3_ratioAttachment;
    std::unique_ptr<SliderAttachment> b3_kneeAttachment;
    std::unique_ptr<SliderAttachment> b3_attackAttachment;
    std::unique_ptr<SliderAttachment> b3_releaseAttachment;
    std::unique_ptr<SliderAttachment> b3_dryWetAttachment;
    std::unique_ptr<ButtonAttachment> b3_muteAttachment;
    std::unique_ptr<ButtonAttachment> b3_bypassAttachment;

    // multiband
    std::unique_ptr<SliderAttachment> lowFreqAttachment;
    std::unique_ptr<SliderAttachment> highFreqAttachment;
    std::unique_ptr<SliderAttachment> inputGainAttachment;
    std::unique_ptr<SliderAttachment> outputGainAttachment;
    std::unique_ptr<ButtonAttachment> genBypassAttachment;

    // preset management
    PresetManager presetManager;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<FFTperformer> spectrumVisualizer;
    std::unique_ptr<juce::Slider> b1_attack;
    std::unique_ptr<juce::Slider> b1_release;
    std::unique_ptr<juce::Slider> b1_threshold;
    std::unique_ptr<juce::Slider> b1_ratio;
    std::unique_ptr<juce::Slider> b1_inputGain;
    std::unique_ptr<juce::Slider> b1_knee;
    std::unique_ptr<juce::Slider> b1_makeupGain;
    std::unique_ptr<juce::Slider> b1_dryWet;
    std::unique_ptr<juce::ToggleButton> b1_mute;
    std::unique_ptr<juce::ToggleButton> b1_bypass;
    std::unique_ptr<juce::Slider> b2_attack;
    std::unique_ptr<juce::Slider> b2_release;
    std::unique_ptr<juce::Slider> b2_threshold;
    std::unique_ptr<juce::Slider> b2_ratio;
    std::unique_ptr<juce::Slider> b2_inputGain;
    std::unique_ptr<juce::Slider> b2_knee;
    std::unique_ptr<juce::Slider> b2_makeupGain;
    std::unique_ptr<juce::Slider> b2_dryWet;
    std::unique_ptr<juce::ToggleButton> b2_mute;
    std::unique_ptr<juce::ToggleButton> b2_bypass;
    std::unique_ptr<juce::Slider> b3_attack;
    std::unique_ptr<juce::Slider> b3_release;
    std::unique_ptr<juce::Slider> b3_threshold;
    std::unique_ptr<juce::Slider> b3_ratio;
    std::unique_ptr<juce::Slider> b3_inputGain;
    std::unique_ptr<juce::Slider> b3_knee;
    std::unique_ptr<juce::Slider> b3_makeupGain;
    std::unique_ptr<juce::Slider> b3_dryWet;
    std::unique_ptr<juce::ToggleButton> b3_mute;
    std::unique_ptr<juce::ToggleButton> b3_bypass;
    std::unique_ptr<juce::Slider> lowFreqSlider;
    std::unique_ptr<juce::Slider> highFreqSlider;
    std::unique_ptr<juce::Slider> inputGainSlider;
    std::unique_ptr<juce::Slider> outputGainSlider;
    std::unique_ptr<juce::TextEditor> currentPresetLabel;
    std::unique_ptr<IconButtons> savePresetBtn;
    std::unique_ptr<IconButtons> undoBtn;
    std::unique_ptr<IconButtons> redoBtn;
    std::unique_ptr<IconButtons> loadPresetBtn;
    std::unique_ptr<IconButtons> prevPresetBtn;
    std::unique_ptr<IconButtons> nextPresetBtn;
    std::unique_ptr<juce::ToggleButton> genBypass;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

