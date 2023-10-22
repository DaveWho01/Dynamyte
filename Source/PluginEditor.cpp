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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
PluginEditor::PluginEditor (DynamyteAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor(&p), processor(p), valueTreeState(vts),
      presetManager(vts, p)
{
    //[Constructor_pre] You can add your own custom stuff here..

    //[/Constructor_pre]

    spectrumVisualizer.reset (new FFTperformer (p.getSampleRate()));
    addAndMakeVisible (spectrumVisualizer.get());
    spectrumVisualizer->setName ("spectrumVisualizer");

    spectrumVisualizer->setBounds (190, 60, 520, 274);

    b1_attack.reset (new juce::Slider ("b1_attack"));
    addAndMakeVisible (b1_attack.get());
    b1_attack->setRange (0, 10, 0);
    b1_attack->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    b1_attack->setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 13);
    b1_attack->setColour (juce::Slider::textBoxOutlineColourId, juce::Colour (0x008e989b));
    b1_attack->addListener (this);

    b1_attack->setBounds (64, 441, 60, 60);

    b1_release.reset (new juce::Slider ("b1_release"));
    addAndMakeVisible (b1_release.get());
    b1_release->setRange (0, 10, 0);
    b1_release->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    b1_release->setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 13);
    b1_release->setColour (juce::Slider::textBoxOutlineColourId, juce::Colour (0x008e989b));
    b1_release->addListener (this);

    b1_release->setBounds (149, 441, 60, 60);

    b1_threshold.reset (new juce::Slider ("b1_threshold"));
    addAndMakeVisible (b1_threshold.get());
    b1_threshold->setRange (0, 10, 0);
    b1_threshold->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    b1_threshold->setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 20);
    b1_threshold->setColour (juce::Slider::textBoxOutlineColourId, juce::Colour (0x008e989b));
    b1_threshold->addListener (this);

    b1_threshold->setBounds (54, 350, 80, 80);

    b1_ratio.reset (new juce::Slider ("b1_ratio"));
    addAndMakeVisible (b1_ratio.get());
    b1_ratio->setRange (0, 10, 0);
    b1_ratio->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    b1_ratio->setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 20);
    b1_ratio->setColour (juce::Slider::textBoxOutlineColourId, juce::Colour (0x008e989b));
    b1_ratio->addListener (this);

    b1_ratio->setBounds (139, 350, 80, 80);

    b1_inputGain.reset (new juce::Slider ("b1_inputGain"));
    addAndMakeVisible (b1_inputGain.get());
    b1_inputGain->setRange (0, 10, 0);
    b1_inputGain->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    b1_inputGain->setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 13);
    b1_inputGain->setColour (juce::Slider::textBoxOutlineColourId, juce::Colour (0x008e989b));
    b1_inputGain->addListener (this);

    b1_inputGain->setBounds (64, 516, 60, 60);

    b1_knee.reset (new juce::Slider ("b1_knee"));
    addAndMakeVisible (b1_knee.get());
    b1_knee->setRange (0, 10, 0);
    b1_knee->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    b1_knee->setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 13);
    b1_knee->setColour (juce::Slider::textBoxOutlineColourId, juce::Colour (0x008e989b));
    b1_knee->addListener (this);

    b1_knee->setBounds (234, 441, 60, 60);

    b1_makeupGain.reset (new juce::Slider ("b1_makeupGain"));
    addAndMakeVisible (b1_makeupGain.get());
    b1_makeupGain->setRange (0, 10, 0);
    b1_makeupGain->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    b1_makeupGain->setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 13);
    b1_makeupGain->setColour (juce::Slider::textBoxOutlineColourId, juce::Colour (0x008e989b));
    b1_makeupGain->addListener (this);

    b1_makeupGain->setBounds (149, 516, 60, 60);

    b1_dryWet.reset (new juce::Slider ("b1_dryWet"));
    addAndMakeVisible (b1_dryWet.get());
    b1_dryWet->setRange (0, 10, 0);
    b1_dryWet->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    b1_dryWet->setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 13);
    b1_dryWet->setColour (juce::Slider::textBoxOutlineColourId, juce::Colour (0x008e989b));
    b1_dryWet->addListener (this);

    b1_dryWet->setBounds (234, 516, 60, 60);

    b1_mute.reset (new juce::ToggleButton ("b1_mute"));
    addAndMakeVisible (b1_mute.get());
    b1_mute->setButtonText (juce::String());
    b1_mute->addListener (this);

    b1_mute->setBounds (228, 362, 25, 25);

    b1_bypass.reset (new juce::ToggleButton ("b1_bypass"));
    addAndMakeVisible (b1_bypass.get());
    b1_bypass->setButtonText (juce::String());
    b1_bypass->addListener (this);

    b1_bypass->setBounds (228, 396, 25, 25);

    b2_attack.reset (new juce::Slider ("b2_attack"));
    addAndMakeVisible (b2_attack.get());
    b2_attack->setRange (0, 10, 0);
    b2_attack->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    b2_attack->setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 13);
    b2_attack->setColour (juce::Slider::textBoxOutlineColourId, juce::Colour (0x008e989b));
    b2_attack->addListener (this);

    b2_attack->setBounds (336, 441, 60, 60);

    b2_release.reset (new juce::Slider ("b2_release"));
    addAndMakeVisible (b2_release.get());
    b2_release->setRange (0, 10, 0);
    b2_release->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    b2_release->setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 13);
    b2_release->setColour (juce::Slider::textBoxOutlineColourId, juce::Colour (0x008e989b));
    b2_release->addListener (this);

    b2_release->setBounds (421, 441, 60, 60);

    b2_threshold.reset (new juce::Slider ("b2_threshold"));
    addAndMakeVisible (b2_threshold.get());
    b2_threshold->setRange (0, 10, 0);
    b2_threshold->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    b2_threshold->setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 20);
    b2_threshold->setColour (juce::Slider::textBoxOutlineColourId, juce::Colour (0x008e989b));
    b2_threshold->addListener (this);

    b2_threshold->setBounds (326, 350, 80, 80);

    b2_ratio.reset (new juce::Slider ("b2_ratio"));
    addAndMakeVisible (b2_ratio.get());
    b2_ratio->setRange (0, 10, 0);
    b2_ratio->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    b2_ratio->setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 20);
    b2_ratio->setColour (juce::Slider::textBoxOutlineColourId, juce::Colour (0x008e989b));
    b2_ratio->addListener (this);

    b2_ratio->setBounds (411, 350, 80, 80);

    b2_inputGain.reset (new juce::Slider ("b2_inputGain"));
    addAndMakeVisible (b2_inputGain.get());
    b2_inputGain->setRange (0, 10, 0);
    b2_inputGain->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    b2_inputGain->setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 13);
    b2_inputGain->setColour (juce::Slider::textBoxOutlineColourId, juce::Colour (0x008e989b));
    b2_inputGain->addListener (this);

    b2_inputGain->setBounds (336, 516, 60, 60);

    b2_knee.reset (new juce::Slider ("b2_knee"));
    addAndMakeVisible (b2_knee.get());
    b2_knee->setRange (0, 10, 0);
    b2_knee->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    b2_knee->setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 13);
    b2_knee->setColour (juce::Slider::textBoxOutlineColourId, juce::Colour (0x008e989b));
    b2_knee->addListener (this);

    b2_knee->setBounds (506, 441, 60, 60);

    b2_makeupGain.reset (new juce::Slider ("b2_makeupGain"));
    addAndMakeVisible (b2_makeupGain.get());
    b2_makeupGain->setRange (0, 10, 0);
    b2_makeupGain->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    b2_makeupGain->setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 13);
    b2_makeupGain->setColour (juce::Slider::textBoxOutlineColourId, juce::Colour (0x008e989b));
    b2_makeupGain->addListener (this);

    b2_makeupGain->setBounds (421, 516, 60, 60);

    b2_dryWet.reset (new juce::Slider ("b2_dryWet"));
    addAndMakeVisible (b2_dryWet.get());
    b2_dryWet->setRange (0, 10, 0);
    b2_dryWet->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    b2_dryWet->setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 13);
    b2_dryWet->setColour (juce::Slider::textBoxOutlineColourId, juce::Colour (0x008e989b));
    b2_dryWet->addListener (this);

    b2_dryWet->setBounds (506, 516, 60, 60);

    b2_mute.reset (new juce::ToggleButton ("b2_mute"));
    addAndMakeVisible (b2_mute.get());
    b2_mute->setButtonText (juce::String());
    b2_mute->addListener (this);

    b2_mute->setBounds (500, 362, 25, 25);

    b2_bypass.reset (new juce::ToggleButton ("b2_bypass"));
    addAndMakeVisible (b2_bypass.get());
    b2_bypass->setButtonText (juce::String());
    b2_bypass->addListener (this);

    b2_bypass->setBounds (500, 396, 25, 25);

    b3_attack.reset (new juce::Slider ("b3_attack"));
    addAndMakeVisible (b3_attack.get());
    b3_attack->setRange (0, 10, 0);
    b3_attack->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    b3_attack->setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 13);
    b3_attack->setColour (juce::Slider::textBoxOutlineColourId, juce::Colour (0x008e989b));
    b3_attack->addListener (this);

    b3_attack->setBounds (608, 441, 60, 60);

    b3_release.reset (new juce::Slider ("b3_release"));
    addAndMakeVisible (b3_release.get());
    b3_release->setRange (0, 10, 0);
    b3_release->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    b3_release->setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 13);
    b3_release->setColour (juce::Slider::textBoxOutlineColourId, juce::Colour (0x008e989b));
    b3_release->addListener (this);

    b3_release->setBounds (693, 441, 60, 60);

    b3_threshold.reset (new juce::Slider ("b3_threshold"));
    addAndMakeVisible (b3_threshold.get());
    b3_threshold->setRange (0, 10, 0);
    b3_threshold->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    b3_threshold->setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 20);
    b3_threshold->setColour (juce::Slider::textBoxOutlineColourId, juce::Colour (0x008e989b));
    b3_threshold->addListener (this);

    b3_threshold->setBounds (598, 350, 80, 80);

    b3_ratio.reset (new juce::Slider ("b3_ratio"));
    addAndMakeVisible (b3_ratio.get());
    b3_ratio->setRange (0, 10, 0);
    b3_ratio->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    b3_ratio->setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 20);
    b3_ratio->setColour (juce::Slider::textBoxOutlineColourId, juce::Colour (0x008e989b));
    b3_ratio->addListener (this);

    b3_ratio->setBounds (683, 350, 80, 80);

    b3_inputGain.reset (new juce::Slider ("b3_inputGain"));
    addAndMakeVisible (b3_inputGain.get());
    b3_inputGain->setRange (0, 10, 0);
    b3_inputGain->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    b3_inputGain->setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 13);
    b3_inputGain->setColour (juce::Slider::textBoxOutlineColourId, juce::Colour (0x008e989b));
    b3_inputGain->addListener (this);

    b3_inputGain->setBounds (608, 516, 60, 60);

    b3_knee.reset (new juce::Slider ("b3_knee"));
    addAndMakeVisible (b3_knee.get());
    b3_knee->setRange (0, 10, 0);
    b3_knee->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    b3_knee->setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 13);
    b3_knee->setColour (juce::Slider::textBoxOutlineColourId, juce::Colour (0x008e989b));
    b3_knee->addListener (this);

    b3_knee->setBounds (778, 441, 60, 60);

    b3_makeupGain.reset (new juce::Slider ("b3_makeupGain"));
    addAndMakeVisible (b3_makeupGain.get());
    b3_makeupGain->setRange (0, 10, 0);
    b3_makeupGain->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    b3_makeupGain->setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 13);
    b3_makeupGain->setColour (juce::Slider::textBoxOutlineColourId, juce::Colour (0x008e989b));
    b3_makeupGain->addListener (this);

    b3_makeupGain->setBounds (693, 516, 60, 60);

    b3_dryWet.reset (new juce::Slider ("b3_dryWet"));
    addAndMakeVisible (b3_dryWet.get());
    b3_dryWet->setRange (0, 10, 0);
    b3_dryWet->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    b3_dryWet->setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 13);
    b3_dryWet->setColour (juce::Slider::textBoxOutlineColourId, juce::Colour (0x008e989b));
    b3_dryWet->addListener (this);

    b3_dryWet->setBounds (778, 516, 60, 60);

    b3_mute.reset (new juce::ToggleButton ("b3_mute"));
    addAndMakeVisible (b3_mute.get());
    b3_mute->setButtonText (juce::String());
    b3_mute->addListener (this);

    b3_mute->setBounds (772, 362, 25, 25);

    b3_bypass.reset (new juce::ToggleButton ("b3_bypass"));
    addAndMakeVisible (b3_bypass.get());
    b3_bypass->setButtonText (juce::String());
    b3_bypass->addListener (this);

    b3_bypass->setBounds (772, 396, 25, 25);

    lowFreqSlider.reset (new juce::Slider ("lowFreqSlider"));
    addAndMakeVisible (lowFreqSlider.get());
    lowFreqSlider->setRange (0, 10, 0);
    lowFreqSlider->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    lowFreqSlider->setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 20);
    lowFreqSlider->addListener (this);

    lowFreqSlider->setBounds (74, 100, 80, 80);

    highFreqSlider.reset (new juce::Slider ("highFreqSlider"));
    addAndMakeVisible (highFreqSlider.get());
    highFreqSlider->setRange (0, 10, 0);
    highFreqSlider->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    highFreqSlider->setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 20);
    highFreqSlider->addListener (this);

    highFreqSlider->setBounds (74, 217, 80, 80);

    inputGainSlider.reset (new juce::Slider ("inputGainSlider"));
    addAndMakeVisible (inputGainSlider.get());
    inputGainSlider->setRange (0, 10, 0);
    inputGainSlider->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    inputGainSlider->setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 20);
    inputGainSlider->setColour (juce::Slider::textBoxOutlineColourId, juce::Colour (0x008e989b));
    inputGainSlider->addListener (this);

    inputGainSlider->setBounds (746, 100, 80, 80);

    outputGainSlider.reset (new juce::Slider ("outputGainSlider"));
    addAndMakeVisible (outputGainSlider.get());
    outputGainSlider->setRange (0, 10, 0);
    outputGainSlider->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    outputGainSlider->setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 20);
    outputGainSlider->setColour (juce::Slider::textBoxOutlineColourId, juce::Colour (0x008e989b));
    outputGainSlider->addListener (this);

    outputGainSlider->setBounds (746, 217, 80, 80);

    currentPresetLabel.reset (new juce::TextEditor ("currentPresetLabel"));
    addAndMakeVisible (currentPresetLabel.get());
    currentPresetLabel->setMultiLine (false);
    currentPresetLabel->setReturnKeyStartsNewLine (false);
    currentPresetLabel->setReadOnly (true);
    currentPresetLabel->setScrollbarsShown (true);
    currentPresetLabel->setCaretVisible (false);
    currentPresetLabel->setPopupMenuEnabled (true);
    currentPresetLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00495358));
    currentPresetLabel->setColour (juce::TextEditor::outlineColourId, juce::Colour (0x00ffffff));
    currentPresetLabel->setText (juce::String());

    currentPresetLabel->setBounds (590, 10, 200, 35);

    savePresetBtn.reset (new IconButtons ("saveBTN", IconsPathData::saveIconPathData,sizeof(IconsPathData::saveIconPathData), 50,50
                                          ));
    addAndMakeVisible (savePresetBtn.get());
    savePresetBtn->setName ("savePresetBtn");

    savePresetBtn->setBounds (424, 11, 38, 38);

    undoBtn.reset (new IconButtons ("undoBTN", IconsPathData::undoIconPathData, sizeof(IconsPathData::undoIconPathData) ,50, 50));
    addAndMakeVisible (undoBtn.get());
    undoBtn->setName ("undoBtn");

    undoBtn->setBounds (281, 11, 38, 38);

    redoBtn.reset (new IconButtons ("redoBTN", IconsPathData::redoIconPathData, sizeof(IconsPathData::redoIconPathData), 50, 50
                                    ));
    addAndMakeVisible (redoBtn.get());
    redoBtn->setName ("redoBtn");

    redoBtn->setBounds (337, 11, 38, 38);

    loadPresetBtn.reset (new IconButtons ("loadBTN", IconsPathData::loadIconPathData,sizeof(IconsPathData::loadIconPathData), 50,50
                                          ));
    addAndMakeVisible (loadPresetBtn.get());
    loadPresetBtn->setName ("loadPresetBtn");

    loadPresetBtn->setBounds (476, 11, 38, 38);

    prevPresetBtn.reset (new IconButtons ("prevPresetBTN", IconsPathData::prevIconPathData,sizeof(IconsPathData::prevIconPathData), 40,40
                                          ));
    addAndMakeVisible (prevPresetBtn.get());
    prevPresetBtn->setName ("prevPresetBtn");

    prevPresetBtn->setBounds (544, 11, 38, 38);

    nextPresetBtn.reset (new IconButtons ("nextPresetBTN", IconsPathData::nextIconPathData,sizeof(IconsPathData::nextIconPathData), 40,40
                                          ));
    addAndMakeVisible (nextPresetBtn.get());
    nextPresetBtn->setName ("nextPresetBtn");

    nextPresetBtn->setBounds (800, 11, 38, 38);


    //[UserPreSize]

    savePresetBtn->addListener(this);
    loadPresetBtn->addListener(this);
    undoBtn->addListener(this);
    redoBtn->addListener(this);
    prevPresetBtn->addListener(this);
    nextPresetBtn->addListener(this);

    // band 1
    b1_inputGainAttachment.reset(new SliderAttachment(valueTreeState, Parameters::nameInputGain_1, *b1_inputGain));
    b1_makeupGainAttachment.reset(new SliderAttachment(valueTreeState, Parameters::nameMakeupGain_1, *b1_makeupGain));
    b1_thresholdAttachment.reset(new SliderAttachment(valueTreeState, Parameters::nameThreshold_1, *b1_threshold));
    b1_ratioAttachment.reset(new SliderAttachment(valueTreeState, Parameters::nameRatio_1, *b1_ratio));
    b1_kneeAttachment.reset(new SliderAttachment(valueTreeState, Parameters::nameKnee_1, *b1_knee));
    b1_attackAttachment.reset(new SliderAttachment(valueTreeState, Parameters::nameAttackTime_1, *b1_attack));
    b1_releaseAttachment.reset(new SliderAttachment(valueTreeState, Parameters::nameReleaseTime_1, *b1_release));
    b1_dryWetAttachment.reset(new SliderAttachment(valueTreeState, Parameters::nameDryWetRatio_1, *b1_dryWet));
    b1_muteAttachment.reset(new ButtonAttachment(valueTreeState, Parameters::nameBand1Muted, *b1_mute));
    b1_bypassAttachment.reset(new ButtonAttachment(valueTreeState, Parameters::nameBypass1, *b1_bypass));

    b1_inputGain->setTextValueSuffix(" dB");
    b1_makeupGain->setTextValueSuffix(" dB");
    b1_threshold->setTextValueSuffix(" dB");
    b1_ratio->setTextValueSuffix(":1");
    b1_knee->setTextValueSuffix(" dB");
    b1_attack->setTextValueSuffix(" ms");
    b1_release->setTextValueSuffix(" ms");
    b1_dryWet->setTextValueSuffix("%");

    b1_inputGain->setPopupDisplayEnabled(true, true, this);
    b1_makeupGain->setPopupDisplayEnabled(true, true, this);
    b1_threshold->setPopupDisplayEnabled(true, true, this);
    b1_ratio->setPopupDisplayEnabled(true, true, this);
    b1_knee->setPopupDisplayEnabled(true, true, this);
    b1_attack->setPopupDisplayEnabled(true, true, this);
    b1_release->setPopupDisplayEnabled(true, true, this);
    b1_dryWet->setPopupDisplayEnabled(true, true, this);

    // band 2
    b2_inputGainAttachment.reset(new SliderAttachment(valueTreeState, Parameters::nameInputGain_2, *b2_inputGain));
    b2_makeupGainAttachment.reset(new SliderAttachment(valueTreeState, Parameters::nameMakeupGain_2, *b2_makeupGain));
    b2_thresholdAttachment.reset(new SliderAttachment(valueTreeState, Parameters::nameThreshold_2, *b2_threshold));
    b2_ratioAttachment.reset(new SliderAttachment(valueTreeState, Parameters::nameRatio_2, *b2_ratio));
    b2_kneeAttachment.reset(new SliderAttachment(valueTreeState, Parameters::nameKnee_2, *b2_knee));
    b2_attackAttachment.reset(new SliderAttachment(valueTreeState, Parameters::nameAttackTime_2, *b2_attack));
    b2_releaseAttachment.reset(new SliderAttachment(valueTreeState, Parameters::nameReleaseTime_2, *b2_release));
    b2_dryWetAttachment.reset(new SliderAttachment(valueTreeState, Parameters::nameDryWetRatio_2, *b2_dryWet));
    b2_muteAttachment.reset(new ButtonAttachment(valueTreeState, Parameters::nameBand2Muted, *b2_mute));
    b2_bypassAttachment.reset(new ButtonAttachment(valueTreeState, Parameters::nameBypass2, *b2_bypass));

    b2_inputGain->setTextValueSuffix(" dB");
    b2_makeupGain->setTextValueSuffix(" dB");
    b2_threshold->setTextValueSuffix(" dB");
    b2_ratio->setTextValueSuffix(":1");
    b2_knee->setTextValueSuffix(" dB");
    b2_attack->setTextValueSuffix(" ms");
    b2_release->setTextValueSuffix(" ms");
    b2_dryWet->setTextValueSuffix("%");

    b2_inputGain->setPopupDisplayEnabled(true, true, this);
    b2_makeupGain->setPopupDisplayEnabled(true, true, this);
    b2_threshold->setPopupDisplayEnabled(true, true, this);
    b2_ratio->setPopupDisplayEnabled(true, true, this);
    b2_knee->setPopupDisplayEnabled(true, true, this);
    b2_attack->setPopupDisplayEnabled(true, true, this);
    b2_release->setPopupDisplayEnabled(true, true, this);
    b2_dryWet->setPopupDisplayEnabled(true, true, this);

    // band 3
    b3_inputGainAttachment.reset(new SliderAttachment(valueTreeState, Parameters::nameInputGain_3, *b3_inputGain));
    b3_makeupGainAttachment.reset(new SliderAttachment(valueTreeState, Parameters::nameMakeupGain_3, *b3_makeupGain));
    b3_thresholdAttachment.reset(new SliderAttachment(valueTreeState, Parameters::nameThreshold_3, *b3_threshold));
    b3_ratioAttachment.reset(new SliderAttachment(valueTreeState, Parameters::nameRatio_3, *b3_ratio));
    b3_kneeAttachment.reset(new SliderAttachment(valueTreeState, Parameters::nameKnee_3, *b3_knee));
    b3_attackAttachment.reset(new SliderAttachment(valueTreeState, Parameters::nameAttackTime_3, *b3_attack));
    b3_releaseAttachment.reset(new SliderAttachment(valueTreeState, Parameters::nameReleaseTime_3, *b3_release));
    b3_dryWetAttachment.reset(new SliderAttachment(valueTreeState, Parameters::nameDryWetRatio_3, *b3_dryWet));
    b3_muteAttachment.reset(new ButtonAttachment(valueTreeState, Parameters::nameBand3Muted, *b3_mute));
    b3_bypassAttachment.reset(new ButtonAttachment(valueTreeState, Parameters::nameBypass3, *b3_bypass));

    b3_inputGain->setTextValueSuffix(" dB");
    b3_makeupGain->setTextValueSuffix(" dB");
    b3_threshold->setTextValueSuffix(" dB");
    b3_ratio->setTextValueSuffix(":1");
    b3_knee->setTextValueSuffix(" dB");
    b3_attack->setTextValueSuffix(" ms");
    b3_release->setTextValueSuffix(" ms");
    b3_dryWet->setTextValueSuffix("%");

    b3_inputGain->setPopupDisplayEnabled(true, true, this);
    b3_makeupGain->setPopupDisplayEnabled(true, true, this);
    b3_threshold->setPopupDisplayEnabled(true, true, this);
    b3_ratio->setPopupDisplayEnabled(true, true, this);
    b3_knee->setPopupDisplayEnabled(true, true, this);
    b3_attack->setPopupDisplayEnabled(true, true, this);
    b3_release->setPopupDisplayEnabled(true, true, this);
    b3_dryWet->setPopupDisplayEnabled(true, true, this);

    // multiband
    lowFreqSlider->setTextValueSuffix(" Hz");
    highFreqSlider->setTextValueSuffix(" Hz");
    lowFreqSlider->setPopupDisplayEnabled(true, true, this);
    highFreqSlider->setPopupDisplayEnabled(true, true, this);

    inputGainSlider->setTextValueSuffix(" dB");
    outputGainSlider->setTextValueSuffix(" dB");
    inputGainSlider->setPopupDisplayEnabled(true, true, this);
    outputGainSlider->setPopupDisplayEnabled(true, true, this);

    lowFreqAttachment.reset(new SliderAttachment(valueTreeState, Parameters::nameLowCrossFreq, *lowFreqSlider));
    highFreqAttachment.reset(new SliderAttachment(valueTreeState, Parameters::nameHighCrossFreq, *highFreqSlider));
    inputGainAttachment.reset(new SliderAttachment(valueTreeState, Parameters::nameGeneralInputGain, *inputGainSlider));
    outputGainAttachment.reset(new SliderAttachment(valueTreeState, Parameters::nameGeneralOutputGain, *outputGainSlider));

    // preset management
    currentPresetLabel->setJustification(Justification::centred);
    currentPresetLabel->setText(presetManager.getCurrentPreset());

    // spectrum
    spectrumVisualizer->connectToBufferPointer(p.bufferForFFT, p.beenCopied);

    this->setLookAndFeel(&dynamyteTheme);

    //[/UserPreSize]

    setSize (900, 600);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

PluginEditor::~PluginEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..

    // band 1
    b1_inputGainAttachment.reset();
    b1_makeupGainAttachment.reset();
    b1_thresholdAttachment.reset();
    b1_ratioAttachment.reset();
    b1_kneeAttachment.reset();
    b1_attackAttachment.reset();
    b1_releaseAttachment.reset();
    b1_dryWetAttachment.reset();
    b1_muteAttachment.reset();
    b1_bypassAttachment.reset();

    // band 2
    b2_inputGainAttachment.reset();
    b2_makeupGainAttachment.reset();
    b2_thresholdAttachment.reset();
    b2_ratioAttachment.reset();
    b2_kneeAttachment.reset();
    b2_attackAttachment.reset();
    b2_releaseAttachment.reset();
    b2_dryWetAttachment.reset();
    b2_muteAttachment.reset();
    b2_bypassAttachment.reset();

    // band 3
    b3_inputGainAttachment.reset();
    b3_makeupGainAttachment.reset();
    b3_thresholdAttachment.reset();
    b3_ratioAttachment.reset();
    b3_kneeAttachment.reset();
    b3_attackAttachment.reset();
    b3_releaseAttachment.reset();
    b3_dryWetAttachment.reset();
    b3_muteAttachment.reset();
    b3_bypassAttachment.reset();

    // multiband
    lowFreqAttachment.reset();
    highFreqAttachment.reset();
    inputGainAttachment.reset();
    outputGainAttachment.reset();

    this->setLookAndFeel(nullptr);

    //[/Destructor_pre]

    spectrumVisualizer = nullptr;
    b1_attack = nullptr;
    b1_release = nullptr;
    b1_threshold = nullptr;
    b1_ratio = nullptr;
    b1_inputGain = nullptr;
    b1_knee = nullptr;
    b1_makeupGain = nullptr;
    b1_dryWet = nullptr;
    b1_mute = nullptr;
    b1_bypass = nullptr;
    b2_attack = nullptr;
    b2_release = nullptr;
    b2_threshold = nullptr;
    b2_ratio = nullptr;
    b2_inputGain = nullptr;
    b2_knee = nullptr;
    b2_makeupGain = nullptr;
    b2_dryWet = nullptr;
    b2_mute = nullptr;
    b2_bypass = nullptr;
    b3_attack = nullptr;
    b3_release = nullptr;
    b3_threshold = nullptr;
    b3_ratio = nullptr;
    b3_inputGain = nullptr;
    b3_knee = nullptr;
    b3_makeupGain = nullptr;
    b3_dryWet = nullptr;
    b3_mute = nullptr;
    b3_bypass = nullptr;
    lowFreqSlider = nullptr;
    highFreqSlider = nullptr;
    inputGainSlider = nullptr;
    outputGainSlider = nullptr;
    currentPresetLabel = nullptr;
    savePresetBtn = nullptr;
    undoBtn = nullptr;
    redoBtn = nullptr;
    loadPresetBtn = nullptr;
    prevPresetBtn = nullptr;
    nextPresetBtn = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PluginEditor::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colour (0xff0d0d1b));

    {
        int x = 47, y = 344, width = 262, height = 246;
        juce::Colour fillColour1 = juce::Colour (0xff48468c), fillColour2 = juce::Colour (0xff0d0d1b);
        juce::Colour strokeColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             184.0f - 47.0f + x,
                                             472.0f - 344.0f + y,
                                             fillColour2,
                                             328.0f - 47.0f + x,
                                             344.0f - 344.0f + y,
                                             true));
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 49, y = 415, width = 90, height = 30;
        juce::String text (TRANS("THRESHOLD"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Microsoft YaHei", 17.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 139, y = 415, width = 80, height = 30;
        juce::String text (TRANS("RATIO"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Microsoft YaHei", 17.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 64, y = 487, width = 60, height = 30;
        juce::String text (TRANS("ATTACK"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Microsoft YaHei", 13.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 149, y = 487, width = 60, height = 30;
        juce::String text (TRANS("RELEASE"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Microsoft YaHei", 13.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 234, y = 487, width = 60, height = 30;
        juce::String text (TRANS("KNEE"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Microsoft YaHei", 13.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 64, y = 563, width = 60, height = 30;
        juce::String text (TRANS("GAIN"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Microsoft YaHei", 13.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 149, y = 563, width = 60, height = 30;
        juce::String text (TRANS("MAKEUP"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Microsoft YaHei", 13.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 234, y = 563, width = 60, height = 30;
        juce::String text (TRANS("DRY/WET"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Microsoft YaHei", 13.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 254, y = 360, width = 50, height = 30;
        juce::String text (TRANS("MUTE"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Microsoft YaHei", 13.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 254, y = 394, width = 50, height = 30;
        juce::String text (TRANS("BYPASS"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Microsoft YaHei", 13.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 319, y = 344, width = 262, height = 246;
        juce::Colour fillColour1 = juce::Colour (0xff48468c), fillColour2 = juce::Colour (0xff0d0d1b);
        juce::Colour strokeColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             456.0f - 319.0f + x,
                                             472.0f - 344.0f + y,
                                             fillColour2,
                                             592.0f - 319.0f + x,
                                             344.0f - 344.0f + y,
                                             true));
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 321, y = 415, width = 90, height = 30;
        juce::String text (TRANS("THRESHOLD"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Microsoft YaHei", 17.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 411, y = 415, width = 80, height = 30;
        juce::String text (TRANS("RATIO"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Microsoft YaHei", 17.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 336, y = 487, width = 60, height = 30;
        juce::String text (TRANS("ATTACK"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Microsoft YaHei", 13.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 421, y = 487, width = 60, height = 30;
        juce::String text (TRANS("RELEASE"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Microsoft YaHei", 13.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 506, y = 487, width = 60, height = 30;
        juce::String text (TRANS("KNEE"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Microsoft YaHei", 13.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 336, y = 563, width = 60, height = 30;
        juce::String text (TRANS("GAIN"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Microsoft YaHei", 13.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 421, y = 563, width = 60, height = 30;
        juce::String text (TRANS("MAKEUP"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Microsoft YaHei", 13.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 506, y = 563, width = 60, height = 30;
        juce::String text (TRANS("DRY/WET"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Microsoft YaHei", 13.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 526, y = 360, width = 50, height = 30;
        juce::String text (TRANS("MUTE"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Microsoft YaHei", 13.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 526, y = 394, width = 50, height = 30;
        juce::String text (TRANS("BYPASS"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Microsoft YaHei", 13.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 591, y = 344, width = 262, height = 246;
        juce::Colour fillColour1 = juce::Colour (0xff48468c), fillColour2 = juce::Colour (0xff0d0d0d);
        juce::Colour strokeColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             720.0f - 591.0f + x,
                                             472.0f - 344.0f + y,
                                             fillColour2,
                                             584.0f - 591.0f + x,
                                             312.0f - 344.0f + y,
                                             true));
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 593, y = 415, width = 90, height = 30;
        juce::String text (TRANS("THRESHOLD"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Microsoft YaHei", 17.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 683, y = 415, width = 80, height = 30;
        juce::String text (TRANS("RATIO"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Microsoft YaHei", 17.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 608, y = 487, width = 60, height = 30;
        juce::String text (TRANS("ATTACK"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Microsoft YaHei", 13.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 693, y = 487, width = 60, height = 30;
        juce::String text (TRANS("RELEASE"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Microsoft YaHei", 13.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 778, y = 487, width = 60, height = 30;
        juce::String text (TRANS("KNEE"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Microsoft YaHei", 13.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 608, y = 563, width = 60, height = 30;
        juce::String text (TRANS("GAIN"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Microsoft YaHei", 13.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 693, y = 563, width = 60, height = 30;
        juce::String text (TRANS("MAKEUP"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Microsoft YaHei", 13.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 778, y = 563, width = 60, height = 30;
        juce::String text (TRANS("DRY/WET"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Microsoft YaHei", 13.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 798, y = 360, width = 50, height = 30;
        juce::String text (TRANS("MUTE"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Microsoft YaHei", 13.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 798, y = 394, width = 50, height = 30;
        juce::String text (TRANS("BYPASS"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Microsoft YaHei", 13.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 47, y = 60, width = 133, height = 274;
        juce::Colour fillColour1 = juce::Colour (0xff48468c), fillColour2 = juce::Colour (0xff0d0d1b);
        juce::Colour strokeColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             120.0f - 47.0f + x,
                                             200.0f - 60.0f + y,
                                             fillColour2,
                                             184.0f - 47.0f + x,
                                             56.0f - 60.0f + y,
                                             true));
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 720, y = 60, width = 133, height = 274;
        juce::Colour fillColour1 = juce::Colour (0xff48468c), fillColour2 = juce::Colour (0xff0d0d1b);
        juce::Colour strokeColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             784.0f - 720.0f + x,
                                             192.0f - 60.0f + y,
                                             fillColour2,
                                             856.0f - 720.0f + x,
                                             48.0f - 60.0f + y,
                                             true));
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 720, y = 170, width = 133, height = 30;
        juce::String text (TRANS("INPUT GAIN"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Microsoft YaHei", 17.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 720, y = 287, width = 133, height = 30;
        juce::String text (TRANS("OUTPUT GAIN"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Microsoft YaHei", 17.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 47, y = 170, width = 133, height = 30;
        juce::String text (TRANS("LOW - MID"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Microsoft YaHei", 17.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 47, y = 287, width = 133, height = 30;
        juce::String text (TRANS("MID - HIGH"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Microsoft YaHei", 17.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 475, y = 10, width = 40, height = 40;
        juce::Colour fillColour1 = juce::Colour (0xff48468c), fillColour2 = juce::Colour (0xff252453);
        juce::Colour strokeColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             320.0f - 475.0f + x,
                                             32.0f - 10.0f + y,
                                             fillColour2,
                                             328.0f - 475.0f + x,
                                             16.0f - 10.0f + y,
                                             true));
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 190, y = 60, width = 520, height = 274;
        juce::Colour fillColour1 = juce::Colour (0xff0d0d1b), fillColour2 = juce::Colour (0xa9ffffff);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             450.0f - 190.0f + x,
                                             248.0f - 60.0f + y,
                                             fillColour2,
                                             450.0f - 190.0f + x,
                                             static_cast<float> (-200) - 60.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        int x = 423, y = 10, width = 40, height = 40;
        juce::Colour fillColour1 = juce::Colour (0xff48468c), fillColour2 = juce::Colour (0xff252453);
        juce::Colour strokeColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             267.0f - 423.0f + x,
                                             28.0f - 10.0f + y,
                                             fillColour2,
                                             277.0f - 423.0f + x,
                                             19.0f - 10.0f + y,
                                             true));
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 280, y = 10, width = 40, height = 40;
        juce::Colour fillColour1 = juce::Colour (0xff48468c), fillColour2 = juce::Colour (0xff252453);
        juce::Colour strokeColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             267.0f - 280.0f + x,
                                             28.0f - 10.0f + y,
                                             fillColour2,
                                             277.0f - 280.0f + x,
                                             19.0f - 10.0f + y,
                                             true));
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 336, y = 10, width = 40, height = 40;
        juce::Colour fillColour1 = juce::Colour (0xff48468c), fillColour2 = juce::Colour (0xff252453);
        juce::Colour strokeColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             267.0f - 336.0f + x,
                                             28.0f - 10.0f + y,
                                             fillColour2,
                                             277.0f - 336.0f + x,
                                             19.0f - 10.0f + y,
                                             true));
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 543, y = 10, width = 40, height = 40;
        juce::Colour fillColour1 = juce::Colour (0xff48468c), fillColour2 = juce::Colour (0xff252453);
        juce::Colour strokeColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             320.0f - 543.0f + x,
                                             32.0f - 10.0f + y,
                                             fillColour2,
                                             328.0f - 543.0f + x,
                                             16.0f - 10.0f + y,
                                             true));
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 799, y = 10, width = 40, height = 40;
        juce::Colour fillColour1 = juce::Colour (0xff48468c), fillColour2 = juce::Colour (0xff252453);
        juce::Colour strokeColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             320.0f - 799.0f + x,
                                             32.0f - 10.0f + y,
                                             fillColour2,
                                             328.0f - 799.0f + x,
                                             16.0f - 10.0f + y,
                                             true));
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 590, y = 10, width = 200, height = 40;
        juce::Colour fillColour1 = juce::Colour (0xff48468c), fillColour2 = juce::Colour (0xff171730);
        juce::Colour strokeColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             320.0f - 590.0f + x,
                                             32.0f - 10.0f + y,
                                             fillColour2,
                                             328.0f - 590.0f + x,
                                             16.0f - 10.0f + y,
                                             true));
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 40, y = 10, width = 232, height = 38;
        juce::String text (TRANS("DYNAMYTE"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Microsoft YaHei", 43.30f, juce::Font::plain).withTypefaceStyle ("Bold").withExtraKerningFactor (0.044f));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 48, y = 11, width = 216, height = 38;
        juce::Colour strokeColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 3);

    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void PluginEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void PluginEditor::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == b1_attack.get())
    {
        //[UserSliderCode_b1_attack] -- add your slider handling code here..
        //[/UserSliderCode_b1_attack]
    }
    else if (sliderThatWasMoved == b1_release.get())
    {
        //[UserSliderCode_b1_release] -- add your slider handling code here..
        //[/UserSliderCode_b1_release]
    }
    else if (sliderThatWasMoved == b1_threshold.get())
    {
        //[UserSliderCode_b1_threshold] -- add your slider handling code here..
        //[/UserSliderCode_b1_threshold]
    }
    else if (sliderThatWasMoved == b1_ratio.get())
    {
        //[UserSliderCode_b1_ratio] -- add your slider handling code here..
        //[/UserSliderCode_b1_ratio]
    }
    else if (sliderThatWasMoved == b1_inputGain.get())
    {
        //[UserSliderCode_b1_inputGain] -- add your slider handling code here..
        //[/UserSliderCode_b1_inputGain]
    }
    else if (sliderThatWasMoved == b1_knee.get())
    {
        //[UserSliderCode_b1_knee] -- add your slider handling code here..
        //[/UserSliderCode_b1_knee]
    }
    else if (sliderThatWasMoved == b1_makeupGain.get())
    {
        //[UserSliderCode_b1_makeupGain] -- add your slider handling code here..
        //[/UserSliderCode_b1_makeupGain]
    }
    else if (sliderThatWasMoved == b1_dryWet.get())
    {
        //[UserSliderCode_b1_dryWet] -- add your slider handling code here..
        //[/UserSliderCode_b1_dryWet]
    }
    else if (sliderThatWasMoved == b2_attack.get())
    {
        //[UserSliderCode_b2_attack] -- add your slider handling code here..
        //[/UserSliderCode_b2_attack]
    }
    else if (sliderThatWasMoved == b2_release.get())
    {
        //[UserSliderCode_b2_release] -- add your slider handling code here..
        //[/UserSliderCode_b2_release]
    }
    else if (sliderThatWasMoved == b2_threshold.get())
    {
        //[UserSliderCode_b2_threshold] -- add your slider handling code here..
        //[/UserSliderCode_b2_threshold]
    }
    else if (sliderThatWasMoved == b2_ratio.get())
    {
        //[UserSliderCode_b2_ratio] -- add your slider handling code here..
        //[/UserSliderCode_b2_ratio]
    }
    else if (sliderThatWasMoved == b2_inputGain.get())
    {
        //[UserSliderCode_b2_inputGain] -- add your slider handling code here..
        //[/UserSliderCode_b2_inputGain]
    }
    else if (sliderThatWasMoved == b2_knee.get())
    {
        //[UserSliderCode_b2_knee] -- add your slider handling code here..
        //[/UserSliderCode_b2_knee]
    }
    else if (sliderThatWasMoved == b2_makeupGain.get())
    {
        //[UserSliderCode_b2_makeupGain] -- add your slider handling code here..
        //[/UserSliderCode_b2_makeupGain]
    }
    else if (sliderThatWasMoved == b2_dryWet.get())
    {
        //[UserSliderCode_b2_dryWet] -- add your slider handling code here..
        //[/UserSliderCode_b2_dryWet]
    }
    else if (sliderThatWasMoved == b3_attack.get())
    {
        //[UserSliderCode_b3_attack] -- add your slider handling code here..
        //[/UserSliderCode_b3_attack]
    }
    else if (sliderThatWasMoved == b3_release.get())
    {
        //[UserSliderCode_b3_release] -- add your slider handling code here..
        //[/UserSliderCode_b3_release]
    }
    else if (sliderThatWasMoved == b3_threshold.get())
    {
        //[UserSliderCode_b3_threshold] -- add your slider handling code here..
        //[/UserSliderCode_b3_threshold]
    }
    else if (sliderThatWasMoved == b3_ratio.get())
    {
        //[UserSliderCode_b3_ratio] -- add your slider handling code here..
        //[/UserSliderCode_b3_ratio]
    }
    else if (sliderThatWasMoved == b3_inputGain.get())
    {
        //[UserSliderCode_b3_inputGain] -- add your slider handling code here..
        //[/UserSliderCode_b3_inputGain]
    }
    else if (sliderThatWasMoved == b3_knee.get())
    {
        //[UserSliderCode_b3_knee] -- add your slider handling code here..
        //[/UserSliderCode_b3_knee]
    }
    else if (sliderThatWasMoved == b3_makeupGain.get())
    {
        //[UserSliderCode_b3_makeupGain] -- add your slider handling code here..
        //[/UserSliderCode_b3_makeupGain]
    }
    else if (sliderThatWasMoved == b3_dryWet.get())
    {
        //[UserSliderCode_b3_dryWet] -- add your slider handling code here..
        //[/UserSliderCode_b3_dryWet]
    }
    else if (sliderThatWasMoved == lowFreqSlider.get())
    {
        //[UserSliderCode_lowFreqSlider] -- add your slider handling code here..
        //[/UserSliderCode_lowFreqSlider]
    }
    else if (sliderThatWasMoved == highFreqSlider.get())
    {
        //[UserSliderCode_highFreqSlider] -- add your slider handling code here..
        //[/UserSliderCode_highFreqSlider]
    }
    else if (sliderThatWasMoved == inputGainSlider.get())
    {
        //[UserSliderCode_inputGainSlider] -- add your slider handling code here..
        //[/UserSliderCode_inputGainSlider]
    }
    else if (sliderThatWasMoved == outputGainSlider.get())
    {
        //[UserSliderCode_outputGainSlider] -- add your slider handling code here..
        //[/UserSliderCode_outputGainSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void PluginEditor::buttonClicked (juce::Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == b1_mute.get())
    {
        //[UserButtonCode_b1_mute] -- add your button handler code here..
        //[/UserButtonCode_b1_mute]
    }
    else if (buttonThatWasClicked == b1_bypass.get())
    {
        //[UserButtonCode_b1_bypass] -- add your button handler code here..
        //[/UserButtonCode_b1_bypass]
    }
    else if (buttonThatWasClicked == b2_mute.get())
    {
        //[UserButtonCode_b2_mute] -- add your button handler code here..
        //[/UserButtonCode_b2_mute]
    }
    else if (buttonThatWasClicked == b2_bypass.get())
    {
        //[UserButtonCode_b2_bypass] -- add your button handler code here..
        //[/UserButtonCode_b2_bypass]
    }
    else if (buttonThatWasClicked == b3_mute.get())
    {
        //[UserButtonCode_b3_mute] -- add your button handler code here..
        //[/UserButtonCode_b3_mute]
    }
    else if (buttonThatWasClicked == b3_bypass.get())
    {
        //[UserButtonCode_b3_bypass] -- add your button handler code here..
        //[/UserButtonCode_b3_bypass]
    }

    //[UserbuttonClicked_Post]

    else if (buttonThatWasClicked == savePresetBtn.get())
    {
        //[UserButtonCode_saveButton] -- add your button handler code here..
        presetManager.savePreset();
        currentPresetLabel->setText(presetManager.getCurrentPreset());
        //[/UserButtonCode_saveButton]
    }
    else if (buttonThatWasClicked == loadPresetBtn.get())
    {
        //[UserButtonCode_loadPreset] -- add your button handler code here..
        presetManager.loadPreset();
        currentPresetLabel->setText(presetManager.getCurrentPreset());
        //[/UserButtonCode_loadPreset]
    }
    else if (buttonThatWasClicked == undoBtn.get())
    {
        //[UserButtonCode_saveButton] -- add your button handler code here..
        valueTreeState.undoManager->undo();
        //[/UserButtonCode_saveButton]
    }
    else if (buttonThatWasClicked == redoBtn.get())
    {
        //[UserButtonCode_saveButton] -- add your button handler code here..
        valueTreeState.undoManager->redo();
        //[/UserButtonCode_saveButton]
    }
    else if (buttonThatWasClicked == nextPresetBtn.get())
    {
        //[UserButtonCode_nextPresetBtn] -- add your button handler code here..
        presetManager.loadNextPreset();
        currentPresetLabel->setText(presetManager.getCurrentPreset());
        //[/UserButtonCode_nextPresetBtn]
    }
    else if (buttonThatWasClicked == prevPresetBtn.get())
    {
        //[UserButtonCode_prevPresetBtn] -- add your button handler code here..
        presetManager.loadPreviousPreset();
        currentPresetLabel->setText(presetManager.getCurrentPreset());
        //[/UserButtonCode_prevPresetBtn]
    }

    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PluginEditor" componentName=""
                 parentClasses="public juce::AudioProcessorEditor" constructorParams="DynamyteAudioProcessor&amp; p, AudioProcessorValueTreeState&amp; vts"
                 variableInitialisers="AudioProcessorEditor(&amp;p), processor(p), valueTreeState(vts),&#10;presetManager(vts, p)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="900" initialHeight="600">
  <BACKGROUND backgroundColour="ff0d0d1b">
    <RECT pos="47 344 262 246" fill=" radial: 184 472, 328 344, 0=ff48468c, 1=ff0d0d1b"
          hasStroke="1" stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
    <TEXT pos="49 415 90 30" fill="solid: ffffffff" hasStroke="0" text="THRESHOLD"
          fontname="Microsoft YaHei" fontsize="17.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="139 415 80 30" fill="solid: ffffffff" hasStroke="0" text="RATIO"
          fontname="Microsoft YaHei" fontsize="17.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="64 487 60 30" fill="solid: ffffffff" hasStroke="0" text="ATTACK"
          fontname="Microsoft YaHei" fontsize="13.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="149 487 60 30" fill="solid: ffffffff" hasStroke="0" text="RELEASE"
          fontname="Microsoft YaHei" fontsize="13.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="234 487 60 30" fill="solid: ffffffff" hasStroke="0" text="KNEE"
          fontname="Microsoft YaHei" fontsize="13.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="64 563 60 30" fill="solid: ffffffff" hasStroke="0" text="GAIN"
          fontname="Microsoft YaHei" fontsize="13.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="149 563 60 30" fill="solid: ffffffff" hasStroke="0" text="MAKEUP"
          fontname="Microsoft YaHei" fontsize="13.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="234 563 60 30" fill="solid: ffffffff" hasStroke="0" text="DRY/WET"
          fontname="Microsoft YaHei" fontsize="13.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="254 360 50 30" fill="solid: ffffffff" hasStroke="0" text="MUTE"
          fontname="Microsoft YaHei" fontsize="13.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="254 394 50 30" fill="solid: ffffffff" hasStroke="0" text="BYPASS"
          fontname="Microsoft YaHei" fontsize="13.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="319 344 262 246" fill=" radial: 456 472, 592 344, 0=ff48468c, 1=ff0d0d1b"
          hasStroke="1" stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
    <TEXT pos="321 415 90 30" fill="solid: ffffffff" hasStroke="0" text="THRESHOLD"
          fontname="Microsoft YaHei" fontsize="17.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="411 415 80 30" fill="solid: ffffffff" hasStroke="0" text="RATIO"
          fontname="Microsoft YaHei" fontsize="17.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="336 487 60 30" fill="solid: ffffffff" hasStroke="0" text="ATTACK"
          fontname="Microsoft YaHei" fontsize="13.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="421 487 60 30" fill="solid: ffffffff" hasStroke="0" text="RELEASE"
          fontname="Microsoft YaHei" fontsize="13.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="506 487 60 30" fill="solid: ffffffff" hasStroke="0" text="KNEE"
          fontname="Microsoft YaHei" fontsize="13.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="336 563 60 30" fill="solid: ffffffff" hasStroke="0" text="GAIN"
          fontname="Microsoft YaHei" fontsize="13.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="421 563 60 30" fill="solid: ffffffff" hasStroke="0" text="MAKEUP"
          fontname="Microsoft YaHei" fontsize="13.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="506 563 60 30" fill="solid: ffffffff" hasStroke="0" text="DRY/WET"
          fontname="Microsoft YaHei" fontsize="13.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="526 360 50 30" fill="solid: ffffffff" hasStroke="0" text="MUTE"
          fontname="Microsoft YaHei" fontsize="13.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="526 394 50 30" fill="solid: ffffffff" hasStroke="0" text="BYPASS"
          fontname="Microsoft YaHei" fontsize="13.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="591 344 262 246" fill=" radial: 720 472, 584 312, 0=ff48468c, 1=ff0d0d0d"
          hasStroke="1" stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
    <TEXT pos="593 415 90 30" fill="solid: ffffffff" hasStroke="0" text="THRESHOLD"
          fontname="Microsoft YaHei" fontsize="17.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="683 415 80 30" fill="solid: ffffffff" hasStroke="0" text="RATIO"
          fontname="Microsoft YaHei" fontsize="17.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="608 487 60 30" fill="solid: ffffffff" hasStroke="0" text="ATTACK"
          fontname="Microsoft YaHei" fontsize="13.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="693 487 60 30" fill="solid: ffffffff" hasStroke="0" text="RELEASE"
          fontname="Microsoft YaHei" fontsize="13.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="778 487 60 30" fill="solid: ffffffff" hasStroke="0" text="KNEE"
          fontname="Microsoft YaHei" fontsize="13.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="608 563 60 30" fill="solid: ffffffff" hasStroke="0" text="GAIN"
          fontname="Microsoft YaHei" fontsize="13.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="693 563 60 30" fill="solid: ffffffff" hasStroke="0" text="MAKEUP"
          fontname="Microsoft YaHei" fontsize="13.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="778 563 60 30" fill="solid: ffffffff" hasStroke="0" text="DRY/WET"
          fontname="Microsoft YaHei" fontsize="13.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="798 360 50 30" fill="solid: ffffffff" hasStroke="0" text="MUTE"
          fontname="Microsoft YaHei" fontsize="13.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="798 394 50 30" fill="solid: ffffffff" hasStroke="0" text="BYPASS"
          fontname="Microsoft YaHei" fontsize="13.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="47 60 133 274" fill=" radial: 120 200, 184 56, 0=ff48468c, 1=ff0d0d1b"
          hasStroke="1" stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
    <RECT pos="720 60 133 274" fill=" radial: 784 192, 856 48, 0=ff48468c, 1=ff0d0d1b"
          hasStroke="1" stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
    <TEXT pos="720 170 133 30" fill="solid: ffffffff" hasStroke="0" text="INPUT GAIN"
          fontname="Microsoft YaHei" fontsize="17.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="720 287 133 30" fill="solid: ffffffff" hasStroke="0" text="OUTPUT GAIN"
          fontname="Microsoft YaHei" fontsize="17.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="47 170 133 30" fill="solid: ffffffff" hasStroke="0" text="LOW - MID"
          fontname="Microsoft YaHei" fontsize="17.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="47 287 133 30" fill="solid: ffffffff" hasStroke="0" text="MID - HIGH"
          fontname="Microsoft YaHei" fontsize="17.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <RECT pos="475 10 40 40" fill=" radial: 320 32, 328 16, 0=ff48468c, 1=ff252453"
          hasStroke="1" stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
    <RECT pos="190 60 520 274" fill="linear: 450 248, 450 -200, 0=ff0d0d1b, 1=a9ffffff"
          hasStroke="0"/>
    <RECT pos="423 10 40 40" fill=" radial: 267 28, 277 19, 0=ff48468c, 1=ff252453"
          hasStroke="1" stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
    <RECT pos="280 10 40 40" fill=" radial: 267 28, 277 19, 0=ff48468c, 1=ff252453"
          hasStroke="1" stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
    <RECT pos="336 10 40 40" fill=" radial: 267 28, 277 19, 0=ff48468c, 1=ff252453"
          hasStroke="1" stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
    <RECT pos="543 10 40 40" fill=" radial: 320 32, 328 16, 0=ff48468c, 1=ff252453"
          hasStroke="1" stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
    <RECT pos="799 10 40 40" fill=" radial: 320 32, 328 16, 0=ff48468c, 1=ff252453"
          hasStroke="1" stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
    <RECT pos="590 10 200 40" fill=" radial: 320 32, 328 16, 0=ff48468c, 1=ff171730"
          hasStroke="1" stroke="1, mitered, butt" strokeColour="solid: ffffffff"/>
    <TEXT pos="40 10 232 38" fill="solid: ffffffff" hasStroke="0" text="DYNAMYTE"
          fontname="Microsoft YaHei" fontsize="43.3" kerning="0.044" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <RECT pos="48 11 216 38" fill="solid: ffffff" hasStroke="1" stroke="2.7, mitered, butt"
          strokeColour="solid: ffffffff"/>
  </BACKGROUND>
  <GENERICCOMPONENT name="spectrumVisualizer" id="5bdc961ddcccdcb1" memberName="spectrumVisualizer"
                    virtualName="" explicitFocusOrder="0" pos="190 60 520 274" class="FFTperformer"
                    params="p.getSampleRate()"/>
  <SLIDER name="b1_attack" id="4a45c8fdcf5d8073" memberName="b1_attack"
          virtualName="" explicitFocusOrder="0" pos="64 441 60 60" textboxoutline="8e989b"
          min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="13" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="b1_release" id="ff9a5511ead93a6e" memberName="b1_release"
          virtualName="" explicitFocusOrder="0" pos="149 441 60 60" textboxoutline="8e989b"
          min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="13" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="b1_threshold" id="9f4e0b7d80430453" memberName="b1_threshold"
          virtualName="" explicitFocusOrder="0" pos="54 350 80 80" textboxoutline="8e989b"
          min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="b1_ratio" id="4864fddaf98ac02e" memberName="b1_ratio" virtualName=""
          explicitFocusOrder="0" pos="139 350 80 80" textboxoutline="8e989b"
          min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="b1_inputGain" id="47dd92111241ed5f" memberName="b1_inputGain"
          virtualName="" explicitFocusOrder="0" pos="64 516 60 60" textboxoutline="8e989b"
          min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="13" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="b1_knee" id="96ec78512302af1c" memberName="b1_knee" virtualName=""
          explicitFocusOrder="0" pos="234 441 60 60" textboxoutline="8e989b"
          min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="13" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="b1_makeupGain" id="66f0c044a7598b95" memberName="b1_makeupGain"
          virtualName="" explicitFocusOrder="0" pos="149 516 60 60" textboxoutline="8e989b"
          min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="13" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="b1_dryWet" id="d1778d8276697958" memberName="b1_dryWet"
          virtualName="" explicitFocusOrder="0" pos="234 516 60 60" textboxoutline="8e989b"
          min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="13" skewFactor="1.0"
          needsCallback="1"/>
  <TOGGLEBUTTON name="b1_mute" id="3ce68044eb989809" memberName="b1_mute" virtualName=""
                explicitFocusOrder="0" pos="228 362 25 25" buttonText="" connectedEdges="0"
                needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="b1_bypass" id="84381f6f795c68e7" memberName="b1_bypass"
                virtualName="" explicitFocusOrder="0" pos="228 396 25 25" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <SLIDER name="b2_attack" id="fb67cfe464055ab5" memberName="b2_attack"
          virtualName="" explicitFocusOrder="0" pos="336 441 60 60" textboxoutline="8e989b"
          min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="13" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="b2_release" id="9ab9d780fce74932" memberName="b2_release"
          virtualName="" explicitFocusOrder="0" pos="421 441 60 60" textboxoutline="8e989b"
          min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="13" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="b2_threshold" id="3187aa0cda8ca971" memberName="b2_threshold"
          virtualName="" explicitFocusOrder="0" pos="326 350 80 80" textboxoutline="8e989b"
          min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="b2_ratio" id="e7d2b36804661ba5" memberName="b2_ratio" virtualName=""
          explicitFocusOrder="0" pos="411 350 80 80" textboxoutline="8e989b"
          min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="b2_inputGain" id="7e27db65ecad98e0" memberName="b2_inputGain"
          virtualName="" explicitFocusOrder="0" pos="336 516 60 60" textboxoutline="8e989b"
          min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="13" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="b2_knee" id="38e2d977ee0e91b6" memberName="b2_knee" virtualName=""
          explicitFocusOrder="0" pos="506 441 60 60" textboxoutline="8e989b"
          min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="13" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="b2_makeupGain" id="75ac4f24a2394689" memberName="b2_makeupGain"
          virtualName="" explicitFocusOrder="0" pos="421 516 60 60" textboxoutline="8e989b"
          min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="13" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="b2_dryWet" id="3e3744f5bd108fe1" memberName="b2_dryWet"
          virtualName="" explicitFocusOrder="0" pos="506 516 60 60" textboxoutline="8e989b"
          min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="13" skewFactor="1.0"
          needsCallback="1"/>
  <TOGGLEBUTTON name="b2_mute" id="923671afc270c4b4" memberName="b2_mute" virtualName=""
                explicitFocusOrder="0" pos="500 362 25 25" buttonText="" connectedEdges="0"
                needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="b2_bypass" id="7a7afa1a99ced594" memberName="b2_bypass"
                virtualName="" explicitFocusOrder="0" pos="500 396 25 25" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <SLIDER name="b3_attack" id="569afeb08a833302" memberName="b3_attack"
          virtualName="" explicitFocusOrder="0" pos="608 441 60 60" textboxoutline="8e989b"
          min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="13" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="b3_release" id="e0e7b128a641f6da" memberName="b3_release"
          virtualName="" explicitFocusOrder="0" pos="693 441 60 60" textboxoutline="8e989b"
          min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="13" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="b3_threshold" id="55eb8f6728fc836" memberName="b3_threshold"
          virtualName="" explicitFocusOrder="0" pos="598 350 80 80" textboxoutline="8e989b"
          min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="b3_ratio" id="337a7d4fa4eaa9b3" memberName="b3_ratio" virtualName=""
          explicitFocusOrder="0" pos="683 350 80 80" textboxoutline="8e989b"
          min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="b3_inputGain" id="76ecd8c750bca16a" memberName="b3_inputGain"
          virtualName="" explicitFocusOrder="0" pos="608 516 60 60" textboxoutline="8e989b"
          min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="13" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="b3_knee" id="eebd31fcbf873870" memberName="b3_knee" virtualName=""
          explicitFocusOrder="0" pos="778 441 60 60" textboxoutline="8e989b"
          min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="13" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="b3_makeupGain" id="a5532efb28c24498" memberName="b3_makeupGain"
          virtualName="" explicitFocusOrder="0" pos="693 516 60 60" textboxoutline="8e989b"
          min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="13" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="b3_dryWet" id="23f86bd8a009e09e" memberName="b3_dryWet"
          virtualName="" explicitFocusOrder="0" pos="778 516 60 60" textboxoutline="8e989b"
          min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="13" skewFactor="1.0"
          needsCallback="1"/>
  <TOGGLEBUTTON name="b3_mute" id="93aa170d11770451" memberName="b3_mute" virtualName=""
                explicitFocusOrder="0" pos="772 362 25 25" buttonText="" connectedEdges="0"
                needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="b3_bypass" id="1509fa999a939d85" memberName="b3_bypass"
                virtualName="" explicitFocusOrder="0" pos="772 396 25 25" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <SLIDER name="lowFreqSlider" id="d25531ef0bed6ef6" memberName="lowFreqSlider"
          virtualName="" explicitFocusOrder="0" pos="74 100 80 80" min="0.0"
          max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="highFreqSlider" id="a57000eba8ccc668" memberName="highFreqSlider"
          virtualName="" explicitFocusOrder="0" pos="74 217 80 80" min="0.0"
          max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="inputGainSlider" id="17ba4c1f3337bd0b" memberName="inputGainSlider"
          virtualName="" explicitFocusOrder="0" pos="746 100 80 80" textboxoutline="8e989b"
          min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="outputGainSlider" id="ca66be4fde161ab8" memberName="outputGainSlider"
          virtualName="" explicitFocusOrder="0" pos="746 217 80 80" textboxoutline="8e989b"
          min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <TEXTEDITOR name="currentPresetLabel" id="6b8516459c37fdfa" memberName="currentPresetLabel"
              virtualName="" explicitFocusOrder="0" pos="590 10 200 35" bkgcol="495358"
              outlinecol="ffffff" initialText="" multiline="0" retKeyStartsLine="0"
              readonly="1" scrollbars="1" caret="0" popupmenu="1"/>
  <GENERICCOMPONENT name="savePresetBtn" id="b52e5d83bea0c61c" memberName="savePresetBtn"
                    virtualName="" explicitFocusOrder="0" pos="424 11 38 38" class="IconButtons"
                    params="&quot;saveBTN&quot;, IconsPathData::saveIconPathData,sizeof(IconsPathData::saveIconPathData), 50,50&#10;"/>
  <GENERICCOMPONENT name="undoBtn" id="16dad68d7b3a4fc6" memberName="undoBtn" virtualName=""
                    explicitFocusOrder="0" pos="281 11 38 38" class="IconButtons"
                    params="&quot;undoBTN&quot;, IconsPathData::undoIconPathData, sizeof(IconsPathData::undoIconPathData) ,50, 50"/>
  <GENERICCOMPONENT name="redoBtn" id="36b84d8300cb08ff" memberName="redoBtn" virtualName=""
                    explicitFocusOrder="0" pos="337 11 38 38" class="IconButtons"
                    params="&quot;redoBTN&quot;, IconsPathData::redoIconPathData, sizeof(IconsPathData::redoIconPathData), 50, 50&#10;"/>
  <GENERICCOMPONENT name="loadPresetBtn" id="26eb954970370da9" memberName="loadPresetBtn"
                    virtualName="" explicitFocusOrder="0" pos="476 11 38 38" class="IconButtons"
                    params="&quot;loadBTN&quot;, IconsPathData::loadIconPathData,sizeof(IconsPathData::loadIconPathData), 50,50&#10;"/>
  <GENERICCOMPONENT name="prevPresetBtn" id="a902cafffce9e86d" memberName="prevPresetBtn"
                    virtualName="" explicitFocusOrder="0" pos="544 11 38 38" class="IconButtons"
                    params="&quot;prevPresetBTN&quot;, IconsPathData::prevIconPathData,sizeof(IconsPathData::prevIconPathData), 40,40&#10;"/>
  <GENERICCOMPONENT name="nextPresetBtn" id="8a7bbd96234b3cf0" memberName="nextPresetBtn"
                    virtualName="" explicitFocusOrder="0" pos="800 11 38 38" class="IconButtons"
                    params="&quot;nextPresetBTN&quot;, IconsPathData::nextIconPathData,sizeof(IconsPathData::nextIconPathData), 40,40&#10;"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

