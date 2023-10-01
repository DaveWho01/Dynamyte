#pragma once
#include <JuceHeader.h> 
#include "CircularBuffer.h"
#include "spline.h"

#define fftOrder	11
#define fftSize		(1 << fftOrder)
#define scopeSize	512
#define FPS			25

class FFTperformer : public Component, public Timer
{
public:
	
    FFTperformer();
    ~FFTperformer();
    void drawNextFrameOfSpectrum();
    void timerCallback() override;
    void connectToBufferPointer(CircularBuffer& buffer, Atomic<bool>& FFTmutex);
    void copyToFFTBuffer();
    void paint(Graphics& g);

private:

    juce::dsp::FFT forwardFFT;                      
    juce::dsp::WindowingFunction<float> window;     

    float fifo[fftSize];
    //float fftData[2 * fftSize];
    //float fftTemp[2 * fftSize];
    AudioBuffer<float> fftData;
    int fifoIndex = 0;
    bool nextFFTBlockReady = false;
    float scopeData[scopeSize];

    CircularBuffer* processorData;
    //AudioBuffer<float> fftBuffer;
    Atomic<bool>* bufferCopied;


    std::vector<double> X, Y;


	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FFTperformer)

};