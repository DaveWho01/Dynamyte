#pragma once
#include <JuceHeader.h>

class IconButtons : public Button
{
public:
    IconButtons(const String& buttonName, const String& iconFilePath, const int sizeProportionW, const int sizeProportionH);

    void paintButton(Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

private:

    File svgFile;
    std::unique_ptr<Drawable> icon;
    String s;
    const int sizeW, sizeH;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IconButtons)
};









// spectrum grid
class SpectrumGrid : public Component
{
public:
    SpectrumGrid();
    ~SpectrumGrid();
    void paint(Graphics& g) override;

private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SpectrumGrid)
};