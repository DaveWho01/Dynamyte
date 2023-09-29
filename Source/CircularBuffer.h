#pragma once
#include <JuceHeader.h>

class CircularBuffer
{
public:

    CircularBuffer();
    ~CircularBuffer();

    void prepareToPlay(double _sampleRate, int _size, int numChannels);
    void pushNextBlock(juce::AudioBuffer<float>& buffer);
    void getData(int channel, AudioBuffer<float>& destBuffer, int numSamples);

    int channels;

private:

    //std::unique_ptr<juce::AudioBuffer<float>> data;
    AudioBuffer<float> data;
    int size = 0;
    std::atomic<int> cursor;
    double sampleRate;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CircularBuffer)
};