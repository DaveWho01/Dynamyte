#pragma once
#include <JuceHeader.h>

#define FPS				25
#define METER_LABEL_FPS	10
#define RELEASE_TIME	0.7f
#define DB_FLOOR		-48.0f

namespace Parameters
{
	static const float defaultAlphaAttack = 0.9132f;
	static const float defaultAlphaRelease = 0.9998f;
	static const float defaultInputGain = 1.0f; // Linear
	static const float defaultMakeupGain = 1.0f; // Linear
	static const float defaultThreshold = 0.0f; // dB
	static const float defaultRatio = 1.0f;
	static const float defaultKnee = 0.0f; // dB
	static const float defaultDWRatio = 1.0f;

	static const double initSampleRate = 0.0;
	static const float initSamplePeak = 0.0f;

	static const float defaultAlphaMeter = 0.0f;

	// General controls
	static const String nameBypass = "BP";
	static const String nameGeneralInputGain = "GIG";
	static const String nameGeneralOutputGain = "GOG";

	// first band compressor names
	static const String nameAttackTime_1 = "AT_1";
	static const String nameReleaseTime_1 = "RT_1";
	static const String nameInputGain_1 = "IG_1";
	static const String nameMakeupGain_1 = "MG_1";
	static const String nameThreshold_1 = "TS_1";
	static const String nameRatio_1 = "RA_1";
	static const String nameKnee_1 = "KN_1";
	static const String nameDryWetRatio_1 = "DW_1";

	// second band compressor names
	static const String nameAttackTime_2 = "AT_2";
	static const String nameReleaseTime_2 = "RT_2";
	static const String nameInputGain_2 = "IG_2";
	static const String nameMakeupGain_2 = "MG_2";
	static const String nameThreshold_2 = "TS_2";
	static const String nameRatio_2 = "RA_2";
	static const String nameKnee_2 = "KN_2";
	static const String nameDryWetRatio_2 = "DW_2";

	// third band compressor names
	static const String nameAttackTime_3 = "AT_3";
	static const String nameReleaseTime_3 = "RT_3";
	static const String nameInputGain_3 = "IG_3";
	static const String nameMakeupGain_3 = "MG_3";
	static const String nameThreshold_3 = "TS_3";
	static const String nameRatio_3 = "RA_3";
	static const String nameKnee_3 = "KN_3";
	static const String nameDryWetRatio_3 = "DW_3";

	// multiband
	static const float defaultLowCrossFreq = 150.0f;
	static const float defaultHighCrossFreq = 3000.0f;
	static const String nameLowCrossFreq = "LF";
	static const String nameHighCrossFreq = "HF";
	static const String nameBand1Muted = "B1M";
	static const String nameBand2Muted = "B2M";
	static const String nameBand3Muted = "B3M";
	static const String nameBypass1 = "BP1";
	static const String nameBypass2 = "BP2";
	static const String nameBypass3 = "BP3";

	static AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
	{
		std::vector<std::unique_ptr<RangedAudioParameter>> params;

		// General controls
		params.push_back(std::make_unique<AudioParameterBool>(nameBypass, "General bypass", false));
		params.push_back(std::make_unique<AudioParameterFloat>(nameGeneralInputGain, "General Input Gain", NormalisableRange<float>(-48.0f, 6.0f, 0.1f, 1.5f), 0.0f));
		params.push_back(std::make_unique<AudioParameterFloat>(nameGeneralOutputGain, "General Output Gain", NormalisableRange<float>(-48.0f, 6.0f, 0.1f, 1.5f), 0.0f));

		// band 1 compressor
		params.push_back(std::make_unique<AudioParameterFloat>(nameAttackTime_1, "First Band Attack Time (ms)", NormalisableRange<float>(0.05f, 250.0f, 0.01f, 0.35f), 0.05f));
		params.push_back(std::make_unique<AudioParameterFloat>(nameReleaseTime_1, "First Band Release Time (ms)", NormalisableRange<float>(10.0f, 3000.0f, 0.1f, 0.3f), 150.0f));
		params.push_back(std::make_unique<AudioParameterFloat>(nameInputGain_1, "First Band Input Gain", NormalisableRange<float>(-48.0f, 6.0f, 0.1f, 1.5f), 0.0f));
		params.push_back(std::make_unique<AudioParameterFloat>(nameThreshold_1, "First Band Threshold (dB)", NormalisableRange<float>(-60.0f, 0.0f, 0.1f, 2.0f), 0.0f));
		params.push_back(std::make_unique<AudioParameterFloat>(nameRatio_1, "First Band Ratio", NormalisableRange<float>(1.0f, 30.0f, 0.01f, 0.5f), 1.0f));
		params.push_back(std::make_unique<AudioParameterFloat>(nameKnee_1, "First Band Knee (dB)", NormalisableRange<float>(0.0f, 50.0f, 0.01f, 0.5f), 0.0f));
		params.push_back(std::make_unique<AudioParameterFloat>(nameMakeupGain_1, "First Band Makeup Gain (dB)", NormalisableRange<float>(0.0f, 15.0f, 0.1f, 0.8f), 0.0f));
		params.push_back(std::make_unique<AudioParameterFloat>(nameDryWetRatio_1, "First Band Dry/Wet", 0.0f, 100.0f, 100.0f));

		// band 2 compressor
		params.push_back(std::make_unique<AudioParameterFloat>(nameAttackTime_2, "Second Band Attack Time (ms)", NormalisableRange<float>(0.05f, 250.0f, 0.01f, 0.35f), 0.05f));
		params.push_back(std::make_unique<AudioParameterFloat>(nameReleaseTime_2, "Second Band Release Time (ms)", NormalisableRange<float>(10.0f, 3000.0f, 0.1f, 0.3f), 150.0f));
		params.push_back(std::make_unique<AudioParameterFloat>(nameInputGain_2, "Second Band Input Gain", NormalisableRange<float>(-48.0f, 6.0f, 0.1f, 1.5f), 0.0f));
		params.push_back(std::make_unique<AudioParameterFloat>(nameThreshold_2, "Second Band Threshold (dB)", NormalisableRange<float>(-60.0f, 0.0f, 0.1f, 2.0f), 0.0f));
		params.push_back(std::make_unique<AudioParameterFloat>(nameRatio_2, "Second Band Ratio", NormalisableRange<float>(1.0f, 30.0f, 0.01f, 0.5f), 1.0f));
		params.push_back(std::make_unique<AudioParameterFloat>(nameKnee_2, "Second Band Knee (dB)", NormalisableRange<float>(0.0f, 50.0f, 0.01f, 0.5f), 0.0f));
		params.push_back(std::make_unique<AudioParameterFloat>(nameMakeupGain_2, "Second Band Makeup Gain (dB)", NormalisableRange<float>(0.0f, 15.0f, 0.1f, 0.8f), 0.0f));
		params.push_back(std::make_unique<AudioParameterFloat>(nameDryWetRatio_2, "Second Band Dry/Wet", 0.0f, 100.0f, 100.0f));

		// band 3 compressor
		params.push_back(std::make_unique<AudioParameterFloat>(nameAttackTime_3, "Third Band Attack Time (ms)", NormalisableRange<float>(0.05f, 250.0f, 0.01f, 0.35f), 0.05f));
		params.push_back(std::make_unique<AudioParameterFloat>(nameReleaseTime_3, "Third Band Release Time (ms)", NormalisableRange<float>(10.0f, 3000.0f, 0.1f, 0.3f), 150.0f));
		params.push_back(std::make_unique<AudioParameterFloat>(nameInputGain_3, "Third Band Input Gain", NormalisableRange<float>(-48.0f, 6.0f, 0.1f, 1.5f), 0.0f));
		params.push_back(std::make_unique<AudioParameterFloat>(nameThreshold_3, "Third Band Threshold (dB)", NormalisableRange<float>(-60.0f, 0.0f, 0.1f, 2.0f), 0.0f));
		params.push_back(std::make_unique<AudioParameterFloat>(nameRatio_3, "Third Band Ratio", NormalisableRange<float>(1.0f, 30.0f, 0.01f, 0.5f), 1.0f));
		params.push_back(std::make_unique<AudioParameterFloat>(nameKnee_3, "Third Band Knee (dB)", NormalisableRange<float>(0.0f, 50.0f, 0.01f, 0.5f), 0.0f));
		params.push_back(std::make_unique<AudioParameterFloat>(nameMakeupGain_3, "Third Band Makeup Gain (dB)", NormalisableRange<float>(0.0f, 15.0f, 0.1f, 0.8f), 0.0f));
		params.push_back(std::make_unique<AudioParameterFloat>(nameDryWetRatio_3, "Third Band Dry/Wet", 0.0f, 100.0f, 100.0f));

		// multibanda
		params.push_back(std::make_unique<AudioParameterFloat>(nameLowCrossFreq, "Low Crossover Frequency", 20.0f, 2500.0f, defaultLowCrossFreq));
		params.push_back(std::make_unique<AudioParameterFloat>(nameHighCrossFreq, "High Crossover Frequency", 3000.0f, 19000.0f, defaultHighCrossFreq));
		params.push_back(std::make_unique<AudioParameterBool>(nameBand1Muted, "Band 1 Mute", false));
		params.push_back(std::make_unique<AudioParameterBool>(nameBand2Muted, "Band 2 Mute", false));
		params.push_back(std::make_unique<AudioParameterBool>(nameBand3Muted, "Band 3 Mute", false));
		params.push_back(std::make_unique<AudioParameterBool>(nameBypass1, "Band 1 Bypass", false));
		params.push_back(std::make_unique<AudioParameterBool>(nameBypass2, "Band 2 Bypass", false));
		params.push_back(std::make_unique<AudioParameterBool>(nameBypass3, "Band 3 Bypass", false));

		return { params.begin(), params.end() };
	}

	static void addListenerToAllParameters(AudioProcessorValueTreeState& valueTreeState, AudioProcessorValueTreeState::Listener* listener)
	{
		std::unique_ptr<XmlElement> xml(valueTreeState.copyState().createXml());

		for (auto element : xml->getChildWithTagNameIterator("PARAM"))
		{
			const String& id = element->getStringAttribute("id");
			valueTreeState.addParameterListener(id, listener);
		}
	}
}