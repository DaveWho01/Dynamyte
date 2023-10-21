#include "CustomGUIclasses.h"

IconButtons::IconButtons(const String& buttonName, const unsigned char pathData[], size_t dataSize, const int sizeProportionW, const int sizeProportionH)
    : Button(buttonName), sizeW(sizeProportionW), sizeH(sizeProportionH)
{
    p.loadPathFromData(pathData, dataSize);
}

void IconButtons::paintButton(Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    auto h = getHeight();
    auto w = getWidth();
    g.setColour(Colours::white);

    auto rectWidth = w * (sizeW * 0.01f);
    auto rectX = (w - rectWidth) * 0.5f;
    auto rectHeight = h * (sizeH * 0.01f);
    auto rectY = (h - rectHeight) * 0.5f;
    p.scaleToFit(rectX, rectY, rectWidth, rectHeight, true);
    g.fillPath(p);

}

