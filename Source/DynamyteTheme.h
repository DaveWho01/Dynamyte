#pragma once
#include <JuceHeader.h>

#define BORDER_WIDTH 1.5f
#define SCALE_TO_KNOB_RATIO 0.85f

class DynamyteTheme : public LookAndFeel_V4
{
public:

	DynamyteTheme();
	~DynamyteTheme();
	void drawRotarySlider(Graphics& g, int x, int y, int width, int height,
		float sliderPosProportional, float rotaryStartAngle,
		float rotaryEndAngle, Slider& s) override;

	void drawBubble(Graphics&, BubbleComponent&, const Point< float >& tip,
		const Rectangle< float >& body) override;

	void drawTickBox(Graphics& g, Component&, float x, float y, float w, float h,
		bool ticked, bool isEnabled, bool shouldDrawButtonAsHighlighted,
		bool shouldDrawButtonAsDown) override;

private:

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DynamyteTheme)
};