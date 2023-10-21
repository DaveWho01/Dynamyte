#include "FFTperformer.h"

FFTperformer::FFTperformer(double sampleRate)
    : forwardFFT(fftOrder), window(fftSize, dsp::WindowingFunction<float>::hann), sr(sampleRate)
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
    paintGrid(g);

    Path area, line;

    auto width = getWidth();
    auto height = getHeight() * 0.95f;
    auto labelsH = getHeight() * 0.05f;
    
    // draw outline
    g.setColour(Colours::white);
    g.drawRect(0.0f, 0.0f, (float)width, (float)height, 1.0f);

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

inline float FFTperformer::logTransformInRange0to1(const float between0and1)
{
    const float minimum = 1.0f;
    const float maximum = 1000.0f;
    return log10(minimum + ((maximum - minimum) * between0and1)) / log10(maximum);
}

void FFTperformer::paintGrid(Graphics& g)
{
    auto height = getHeight() * 0.95f;
    auto width = getWidth();
    float labelH = height * 0.05f;
    float labelW = 20.0f;

    g.setColour(Colours::white);

    // draw vertical freq lines
    g.setOpacity(0.5f);
    auto maxNofFrequencies = sizeof(frequenciesToPlot) / sizeof(frequenciesToPlot[0]);
    for (int i = 0; i < maxNofFrequencies; ++i)
    {
        const double proportion = frequenciesToPlot[i] / (sr * 0.5);
        int xPos = logTransformInRange0to1(proportion) * width;
        g.drawVerticalLine(xPos, 0.0f, height);
    }
    
    // draw freq text labels
    g.setOpacity(1.0f);
    for (int i = 0; i < frequenciesLabel.size(); ++i)
    {
        const double proportion = frequenciesLabel[i] / (sr * 0.5);
        int xPos = logTransformInRange0to1(proportion) * getWidth();
        g.drawFittedText(labels[i], xPos - (labelW * 0.5f), height + 1.0f, labelW, labelH, Justification::centred, 1);
    }
    
}

