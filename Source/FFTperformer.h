#pragma once
#include <JuceHeader.h> 
#include "CircularBuffer.h"

#define fftOrder	    11
#define fftSize		    (1 << fftOrder)
#define scopeSize	    512
#define FPS			    25
#define RELEASE_TIME    1.0f

class FFTperformer : public Component, public Timer
{
public:
	
    FFTperformer(double sampleRate);
    ~FFTperformer();
    void drawNextFrameOfSpectrum();
    void timerCallback() override;
    void connectToBufferPointer(CircularBuffer& buffer, Atomic<bool>& FFTmutex);
    void copyToFFTBuffer();
    void paint(Graphics& g);
    inline float logTransformInRange0to1(const float between0and1);
    void paintGrid(Graphics& g);

private:

    juce::dsp::FFT forwardFFT;                      
    juce::dsp::WindowingFunction<float> window;     

    float fifo[fftSize];
    AudioBuffer<float> fftData;
    int fifoIndex = 0;
    bool nextFFTBlockReady = false;
    float scopeData[scopeSize];

    CircularBuffer* processorData;
    Atomic<bool>* bufferCopied;

    float alpha;
    float oldScopeData[scopeSize];

    // Grid

    double sr;
    int frequenciesToPlot[28] = { 20, 30, 40, 50, 60, 70, 80, 90, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 20000 };

    std::vector<int> frequenciesLabel = { 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000, 20000 };
    std::vector<String> labels = { "20", "50", "100", "200", "500", "1k", "2k", "5k", "10k", "20k" };

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FFTperformer)

};