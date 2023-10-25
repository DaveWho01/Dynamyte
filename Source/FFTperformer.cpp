#include "FFTperformer.h"

FFTperformer::FFTperformer(double sampleRate)
    : forwardFFTOut(fftOrder), forwardFFTIn(fftOrder), 
    windowOut(fftSize, dsp::WindowingFunction<float>::hann), windowIn(fftSize, dsp::WindowingFunction<float>::hann),
    sr(sampleRate)
{
    processorDataOut = nullptr;
    processorDataIn = nullptr;
    startTimerHz(FPS);
    fftDataOut.setSize(1, 2 * fftSize);
    fftDataIn.setSize(1, 2 * fftSize);
    fftDataOut.clear();
    fftDataIn.clear();

    thr1 = nullptr;
    thr2 = nullptr;
    thr3 = nullptr;    

    alpha = exp(-1.0f / (FPS * RELEASE_TIME));
}

FFTperformer::~FFTperformer()
{
    stopTimer();
}

void FFTperformer::drawNextFrameOfSpectrum()
{
    windowOut.multiplyWithWindowingTable(fftDataOut.getWritePointer(0), fftSize);
    windowIn.multiplyWithWindowingTable(fftDataIn.getWritePointer(0), fftSize);

    forwardFFTOut.performFrequencyOnlyForwardTransform(fftDataOut.getWritePointer(0));
    forwardFFTIn.performFrequencyOnlyForwardTransform(fftDataIn.getWritePointer(0));

    auto mindB = -100.0f;
    auto maxdB = 0.0f;

    for (int i = 0; i < scopeSize; ++i)
    {

        auto skewedProportionX = 1.0f - std::exp(std::log(1.0f - (float)i / (float)scopeSize) * 0.2f);
        auto fftDataIndex = jlimit(0, fftSize / 2, static_cast<int>(skewedProportionX * static_cast<float>(fftSize) * 0.5f));
        
        freqBinsOut[i] = fftDataIndex * sr / fftSize;
        freqBinsIn[i] = fftDataIndex * sr / fftSize;
        
        auto levelOut = jmap(jlimit(mindB, maxdB, Decibels::gainToDecibels(fftDataOut.getWritePointer(0)[fftDataIndex]) - Decibels::gainToDecibels(static_cast<float>(fftSize))), mindB, maxdB, 0.0f, 1.0f);
        auto levelIn = jmap(jlimit(mindB, maxdB, Decibels::gainToDecibels(fftDataIn.getWritePointer(0)[fftDataIndex]) - Decibels::gainToDecibels(static_cast<float>(fftSize))), mindB, maxdB, 0.0f, 1.0f);

        scopeDataOut[i] = levelOut;
        scopeDataIn[i] = levelIn;
    }
}

void FFTperformer::timerCallback()
{
        copyToFFTBuffer();
        drawNextFrameOfSpectrum();
        repaint();
}

void FFTperformer::connectToProcessor(CircularBuffer& bufferOut, Atomic<bool>& FFTmutexOut,
    CircularBuffer& bufferIn, Atomic<bool>& FFTmutexIn,
    float& lowCrossoverFreq, float& highCrossoverFreq, 
    float& band1Threshold, float& band2Threshold, float& band3Threshold)
{
    processorDataOut = &bufferOut;
    processorDataIn = &bufferIn;
    bufferCopiedOut = &FFTmutexOut;
    bufferCopiedIn = &FFTmutexIn;
    lowXoverFreq = &lowCrossoverFreq;
    highXoverFreq = &highCrossoverFreq;
    thr1 = &band1Threshold;
    thr2 = &band2Threshold;
    thr3 = &band3Threshold;
}

void FFTperformer::copyToFFTBuffer()
{
    if (bufferCopiedOut->get())
    {
        bufferCopiedOut->set(false);
        processorDataOut->getData(0, fftDataOut, 2048);
        bufferCopiedOut->set(true);
    }
    if (bufferCopiedIn->get())
    {
        bufferCopiedIn->set(false);
        processorDataIn->getData(0, fftDataIn, 2048);
        bufferCopiedIn->set(true);
    }
}

inline float FFTperformer::logTransformInRange0to1(const float between0and1)
{
    const float minimum = 1.0f;
    const float maximum = 1000.0f;
    return log10(minimum + ((maximum - minimum) * between0and1)) / log10(maximum);
}

void FFTperformer::paint(Graphics& g)
{
    paintGrid(g);

    Path areaIn, areaOut, line;

    auto width = getWidth() * 0.95f;
    auto height = getHeight() * 0.95f;
    auto labelsH = getHeight() * 0.05f;
    
    // draw outline
    g.setColour(Colours::white);
    g.drawRect(0.0f, 0.0f, (float)getWidth(), height, 1.0f);

    for (int i = 0; i < scopeSize; ++i)
    {
        oldScopeDataOut[i] *= alpha;
        scopeDataOut[i] = jmax(scopeDataOut[i],oldScopeDataOut[i]);
        oldScopeDataOut[i] = scopeDataOut[i];

        oldScopeDataIn[i] *= alpha;
        scopeDataIn[i] = jmax(scopeDataIn[i], oldScopeDataIn[i]);
        oldScopeDataIn[i] = scopeDataIn[i];
    }

    Point<float> initP(0, height);
    areaOut.startNewSubPath(initP);
    areaOut.lineTo(0, height);
    areaIn.startNewSubPath(initP);
    areaIn.lineTo(0, height);
    for (int i = 4; i < scopeSize; i += 6)
    {
        areaOut.cubicTo(
            logTransformInRange0to1(freqBinsOut[i - 4] / (sr * 0.5)) * width, jmap(scopeDataOut[i - 4], 0.0f, 1.0f, (float)height, 0.0f),
            logTransformInRange0to1(freqBinsOut[i - 2] / (sr * 0.5)) * width, jmap(scopeDataOut[i - 2], 0.0f, 1.0f, (float)height, 0.0f),
            logTransformInRange0to1(freqBinsOut[i] / (sr * 0.5)) * width, jmap(scopeDataOut[i], 0.0f, 1.0f, (float)height, 0.0f)
        );
        areaIn.cubicTo(
            logTransformInRange0to1(freqBinsIn[i - 4] / (sr * 0.5)) * width, jmap(scopeDataIn[i - 4], 0.0f, 1.0f, (float)height, 0.0f),
            logTransformInRange0to1(freqBinsIn[i - 2] / (sr * 0.5)) * width, jmap(scopeDataIn[i - 2], 0.0f, 1.0f, (float)height, 0.0f),
            logTransformInRange0to1(freqBinsIn[i] / (sr * 0.5)) * width, jmap(scopeDataIn[i], 0.0f, 1.0f, (float)height, 0.0f)
        );
    }
    areaOut.lineTo(width, height);
    areaIn.lineTo(width, height);
    line = areaOut;
    areaOut.lineTo(0, height);
    areaIn.lineTo(0, height);
    g.setColour(Colour::fromRGBA(167, 166, 195, 255));
    g.setOpacity(0.4f);
    g.fillPath(areaOut);
    g.setOpacity(0.3f);
    g.fillPath(areaIn);
    g.setColour(Colours::white);
    g.setOpacity(1.0f);
    g.strokePath(line, PathStrokeType(1.0f));
}


void FFTperformer::paintGrid(Graphics& g)
{
    auto height = getHeight() * 0.95f;
    auto width = getWidth() * 0.95f;
    float labelH = getHeight() * 0.05f;
    float labelW = getWidth() * 0.045f;
    float lineOpacity = 0.3f;

    g.setFont(11.0f);

    g.setColour(Colours::white);

    // draw vertical freq lines
    g.setOpacity(lineOpacity);
    auto maxNofFrequencies = sizeof(frequenciesToPlot) / sizeof(frequenciesToPlot[0]);
    for (int i = 0; i < maxNofFrequencies; ++i)
    {
        const double proportion = frequenciesToPlot[i] / (sr * 0.5);
        int xPos = logTransformInRange0to1(proportion) * width;
        g.drawVerticalLine(xPos, 0.0f, height);
    }
    
    // draw horizontal dB lines & labels
    auto space = height * 0.1f;
    for (int i = 1; i <= 10; ++i)
    {
        g.setOpacity(lineOpacity);
        g.drawHorizontalLine(space * i, 0, getWidth());
        g.setOpacity(1.0f);
        g.drawFittedText(String(-i * 10), width, space * i - labelH, labelW, labelH, Justification::right, 1);
    }

    // draw freq text labels
    g.setOpacity(1.0f);
    for (int i = 0; i < frequenciesLabel.size(); ++i)
    {
        const double proportion = frequenciesLabel[i] / (sr * 0.5);
        int xPos = logTransformInRange0to1(proportion) * width;
        g.drawFittedText(labels[i], xPos - (labelW * 0.5f), height + 1.0f, labelW, labelH, Justification::centred, 1);
    }

    // draw xover freqs
    double proportion = *lowXoverFreq / (sr * 0.5);
    int xPos_LowMid = logTransformInRange0to1(proportion) * width;
    g.drawLine(xPos_LowMid, 0.0f, xPos_LowMid, height, 2.0f);

    proportion = *highXoverFreq / (sr * 0.5);
    int xPos_MidHigh = logTransformInRange0to1(proportion) * width;
    g.drawLine(xPos_MidHigh, 0.0f, xPos_MidHigh, height, 2.0f);

    //draw thresholds
    auto yThreshold = jmap(*thr1, -60.0f, 0.0f, height * 0.6f, 0.0f);
    g.drawHorizontalLine(yThreshold, 0, xPos_LowMid);

    yThreshold = jmap(*thr2, -60.0f, 0.0f, height * 0.6f, 0.0f);
    g.drawHorizontalLine(yThreshold, xPos_LowMid, xPos_MidHigh);

    yThreshold = jmap(*thr3, -60.0f, 0.0f, height * 0.6f, 0.0f);
    g.drawHorizontalLine(yThreshold, xPos_MidHigh, getWidth());

}