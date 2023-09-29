#include "FFTperformer.h"

FFTperformer::FFTperformer()
    : forwardFFT(fftOrder), window(fftSize, dsp::WindowingFunction<float>::hann)
{
    processorData = nullptr;
    startTimerHz(FPS);
    fftData.setSize(1, 2 * fftSize);
    fftData.clear();
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
        //if (processorData->channels == 2)
        //{
        //    processorData->getData(1, fftTemp, 2048);
        //    for (int smp = 0; smp < 2048; ++smp)
        //    {
        //        fftData[smp] = (fftData[smp] + fftTemp[smp]) * 0.5f;
        //    }
        //}
        bufferCopied->set(true);
    }
}

void FFTperformer::paint(Graphics& g)
{
    for (int i = 1; i < scopeSize; ++i)
    {
        auto width = getLocalBounds().getWidth();
        auto height = getLocalBounds().getHeight();

        g.drawLine({ (float)juce::jmap(i - 1, 0, scopeSize - 1, 0, width),
                              juce::jmap(scopeData[i - 1], 0.0f, 1.0f, (float)height, 0.0f),
                      (float)juce::jmap(i,     0, scopeSize - 1, 0, width),
                              juce::jmap(scopeData[i],     0.0f, 1.0f, (float)height, 0.0f) });
    }
}

