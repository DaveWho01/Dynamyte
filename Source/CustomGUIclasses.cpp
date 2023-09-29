#include "CustomGUIclasses.h"

// save button implementation
void SaveButton::paintButton(Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    auto w = static_cast<float>(getWidth());
    auto h = static_cast<float>(getHeight());

    saveIcon->setTransform(AffineTransform::scale(0.008f * w));
    saveIcon->drawAt(g, w*0.1f, w*0.1f, 1);
}
