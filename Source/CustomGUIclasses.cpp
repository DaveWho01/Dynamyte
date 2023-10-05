#include "CustomGUIclasses.h"

IconButtons::IconButtons(const String& buttonName, const String& iconFilePath, const int sizeProportionW, const int sizeProportionH)
    : Button(buttonName), sizeW(sizeProportionW), sizeH(sizeProportionH), svgFile(iconFilePath)
{
    s = svgFile.loadFileAsString();
    std::unique_ptr<XmlElement> xml = parseXML(svgFile);
    icon = Drawable::createFromSVG(*xml);
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

    icon->drawWithin(g, Rectangle<float>(rectX, rectY, rectWidth, rectWidth), 256, 1.0f);
}




//// save button implementation
//void SaveButton::paintButton(Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
//{
//    auto w = static_cast<float>(getWidth());
//    auto h = static_cast<float>(getHeight());
//
//    //saveIcon->setTransform(AffineTransform::scale(0.008f * w));
//    //saveIcon->drawAt(g, w*0.1f, w*0.1f, 1);
//}



// spec grid implementation
SpectrumGrid::SpectrumGrid()
{
}

SpectrumGrid::~SpectrumGrid()
{
}

void SpectrumGrid::paint(Graphics& g)
{
    auto height = getHeight();
    auto width = getWidth();

    g.setColour(Colours::white);
    //g.drawVerticalLine(m_20map, 0, height);
}

