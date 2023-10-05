#include "FFTperformer.h"

FFTperformer::FFTperformer()
    : forwardFFT(fftOrder), window(fftSize, dsp::WindowingFunction<float>::hann)
{
    processorData = nullptr;
    startTimerHz(FPS);
    fftData.setSize(1, 2 * fftSize);
    fftData.clear();

    alpha = exp(-1.0f / (FPS * RELEASE_TIME));
}

FFTperformer::~FFTperformer()
{
    stopTimer();
}

void FFTperformer::drawNextFrameOfSpectrum()
{
    window.multiplyWithWindowingTable(fftData.getWritePointer(0), fftSize);

    forwardFFT.performFrequencyOnlyForwardTransform(fftData.getWritePointer(0));

    auto mindB = -100.0f;
    auto maxdB = 0.0f;

    for (int i = 0; i < scopeSize; ++i)
    {
        auto skewedProportionX = 1.0f - std::exp(std::log(1.0f - (float)i / (float)scopeSize) * 0.2f);
        auto fftDataIndex = jlimit(0, fftSize / 2, static_cast<int>(skewedProportionX * static_cast<float>(fftSize) * 0.5f));
        auto level = jmap(jlimit(mindB, maxdB, Decibels::gainToDecibels(fftData.getWritePointer(0)[fftDataIndex]) - Decibels::gainToDecibels(static_cast<float>(fftSize))), mindB, maxdB, 0.0f, 1.0f);

        scopeData[i] = level;
    }
}

void FFTperformer::timerCallback()
{
        copyToFFTBuffer();
        drawNextFrameOfSpectrum();
        repaint();
}

void FFTperformer::connectToBufferPointer(CircularBuffer& buffer, Atomic<bool>& FFTmutex)
{
    processorData = &buffer;
    bufferCopied = &FFTmutex;
}

void FFTperformer::copyToFFTBuffer()
{
    if (bufferCopied->get())
    {
        bufferCopied->set(false);
        processorData->getData(0, fftData, 2048);
        bufferCopied->set(true);
    }
}

void FFTperformer::paint(Graphics& g)
{
    Path area, line;

    auto width = getLocalBounds().getWidth();
    auto height = getLocalBounds().getHeight();

    for (int i = 0; i < scopeSize; ++i)
    {
        oldScopeData[i] *= alpha;
        scopeData[i] = jmax(scopeData[i],oldScopeData[i]);
        oldScopeData[i] = scopeData[i];
    }

    Point<float> initP(0, height);
    area.startNewSubPath(initP);
    area.lineTo(0, height);
    for (int i = 4; i < scopeSize; i+=6)
    {            
        area.cubicTo(
            (float)jmap(i - 4, 0, scopeSize - 1, 0, width), jmap(scopeData[i - 4], 0.0f, 1.0f, (float)height, 0.0f),
            (float)jmap(i - 2, 0, scopeSize - 1, 0, width), jmap(scopeData[i - 2], 0.0f, 1.0f, (float)height, 0.0f),
            (float)jmap(i, 0, scopeSize - 1, 0, width), jmap(scopeData[i], 0.0f, 1.0f, (float)height, 0.0f)
        );
    }
    area.lineTo(width, height);
    line = area;
    area.lineTo(0, height);
    g.setColour(Colour::fromRGBA(167, 166, 195, 255));
    g.setOpacity(0.3f);
    g.fillPath(area);
    g.setColour(Colours::white);
    g.setOpacity(1.0f);
    g.strokePath(line, PathStrokeType(2.0f));
}

