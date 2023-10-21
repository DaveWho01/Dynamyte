#pragma once
#include <JuceHeader.h>

class IconButtons : public Button
{
public:
    IconButtons(const String& buttonName, const unsigned char pathData[], size_t dataSize, const int sizeProportionW, const int sizeProportionH);

    void paintButton(Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

private:

    Path p;
    String s;
    const int sizeW, sizeH;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IconButtons)
};