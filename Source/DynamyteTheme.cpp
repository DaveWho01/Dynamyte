#include "DynamyteTheme.h"

DynamyteTheme::DynamyteTheme()
{
}

DynamyteTheme::~DynamyteTheme()
{
}

void DynamyteTheme::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider& s)
{

	const auto radius = jmin(width, height) * 0.5f * SCALE_TO_KNOB_RATIO * BORDER_WIDTH * 0.5f;
	const auto centreX = x + width * 0.5f;
	const auto centreY = y + height * 0.5f;
	const auto rx = centreX - radius;
	const auto ry = centreY - radius;
	const auto rw = radius * 2.0f;

	const Colour knobColour = Colour::fromRGBA(167, 166, 195, 255);
	const Colour borderKnobColour = Colour::fromRGBA(18, 17, 47, 255);

	g.setColour(knobColour);
	g.fillEllipse(rx, ry, rw, rw);

	g.setColour(borderKnobColour);
	g.drawEllipse(rx, ry, rw, rw, BORDER_WIDTH);

	// knob dot
	Path p;
	const auto pointerRadius = radius * 0.1f;
	p.addEllipse(radius * 0.4f, radius * 0.4f, pointerRadius * 2, pointerRadius * 2);

	const auto angle = jmap(sliderPosProportional, rotaryStartAngle + 10.6f, rotaryEndAngle + 9.8f);
	p.applyTransform(AffineTransform::rotation(angle).translated(centreX, centreY));
	g.fillPath(p);

	// ticks
	/*g.setColour(knobColour);
	
	Path minTick;
	minTick.addRectangle(centreX + radius + 1, centreY-1, radius * 0.18f, 2);
	minTick.applyTransform(AffineTransform::rotation(2.6f, centreX, centreY));
	g.fillPath(minTick);*/

	Path range;
	range.addPieSegment(rx, ry, rw, rw, -2.1f, 2.1f, 1.2);
	g.setColour(Colours::black);
	g.setOpacity(0.5f);
	g.fillPath(range);

	Path progress;
	auto progressAngle = jmap(sliderPosProportional, -2.1f, 2.1f);
	progress.addPieSegment(rx, ry, rw, rw, -2.1f, progressAngle, 1.2);
	g.setColour(knobColour);
	g.setOpacity(1.0f);
	g.fillPath(progress);

}

void DynamyteTheme::drawBubble(Graphics& g, BubbleComponent&, const Point<float>& tip, const Rectangle<float>& body)
{
	g.setColour(Colours::black);
	g.setOpacity(0.7f);
	g.fillRect(body);
}

void DynamyteTheme::drawTickBox(Graphics& g, Component&, float x, float y, float w, float h, bool ticked, bool isEnabled, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
	g.setColour(Colours::white);
	g.drawRoundedRectangle(x, y, w, h, 2.0f, 1.0f);
	if (ticked)
	{
		g.setColour(Colours::white);
		g.setOpacity(0.8f);
		g.fillRoundedRectangle(x + 2, y + 2, w - 4, h - 4, 2.0f);
	}
}

