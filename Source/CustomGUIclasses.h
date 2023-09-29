#pragma once
#include <JuceHeader.h>



// Save button
class SaveButton    : public Button
{
public:
    SaveButton(const String& buttonName) : Button(buttonName) {};
    
    //void clicked(const ModifierKeys& modifiers) override;
    void paintButton(Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

private:

    std::unique_ptr<Drawable> saveIcon = juce::Drawable::createFromImageData(BinaryData::save_svg, BinaryData::save_svgSize);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SaveButton)
};