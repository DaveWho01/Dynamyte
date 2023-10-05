#include "CircularBuffer.h"

CircularBuffer::CircularBuffer()
{
    channels = 0;
}

CircularBuffer::~CircularBuffer()
{
}

void CircularBuffer::prepareToPlay(double _sampleRate, int _size, int numChannels)
{
    sampleRate = _sampleRate;
    size = _size;
    //data.reset(new juce::AudioBuffer<float>(numChannels, size));
    data.setSize(1, 2048);
    data.clear();
    cursor = 0;
    channels = numChannels;
}

void CircularBuffer::pushNextBlock(juce::AudioBuffer<float>& buffer)
{
    //jassert(size > 0);
    //jassert(buffer.getNumChannels() == data->getNumChannels());

    int numSamples = buffer.getNumSamples();
    int numChannels = buffer.getNumChannels();
    float gainToApply = (float)1 / (float)numChannels;

    for (int channel = 0; channel < numChannels; ++channel)
    {

        //const float* channelData = buffer.getReadPointer(channel);
        //float* bufferData = data->getWritePointer(channel);
        //auto dataPtr = data.getWritePointer(0);

        int end = cursor + numSamples;

        if (end < size) {
            // Copy the entire block in one go
            //std::memcpy(bufferData + cursor, channelData, numSamples * sizeof(float));
            data.addFrom(0, cursor, buffer, channel, 0, numSamples);
            data.applyGain(0, cursor, numSamples, gainToApply);
        }
        else 
        {
            // Wrap around to the beginning and copy in two blocks
            int firstBlockSize = size - cursor;
            int secondBlockSize = end - size;

            //std::memcpy(bufferData + cursor, channelData, firstBlockSize * sizeof(float));
            data.addFrom(0, cursor, buffer, channel, 0, firstBlockSize);
            data.applyGain(0, cursor, firstBlockSize, gainToApply);
            //std::memcpy(bufferData, channelData + firstBlockSize, secondBlockSize * sizeof(float));
            data.addFrom(0, 0, buffer, channel, firstBlockSize, secondBlockSize);
            data.applyGain(0, 0, secondBlockSize, gainToApply);
        }
    }
    cursor = (cursor + numSamples) % size;

    /*for (int i = 0; i < data.getNumSamples(); ++i)
    {
        data.getArrayOfWritePointers()[0][i] = i;
    }*/
}

void CircularBuffer::getData(int channel, AudioBuffer<float>& destBuffer, int numSamples)
{
    //jassert(destBuffer != nullptr);
    
    if (cursor - numSamples >= 0) {
        destBuffer.copyFrom(0, 0, data, 0, 0, numSamples);
        //const float* source = data->getReadPointer(channel) + firstSample;
        //std::memcpy(destBuffer, source, numSamples * sizeof(float));
    }
    else {
        int subBlockSize = size - cursor;

        /*const float* source1 = data->getReadPointer(channel) + firstSample;
        std::memcpy(destBuffer, source1, subBlockSize * sizeof(float));*/

        destBuffer.copyFrom(0, 0, data, 0, cursor, subBlockSize);

        /*const float* source2 = data->getReadPointer(channel);
        std::memcpy(destBuffer + subBlockSize, source2, (numSamples - subBlockSize) * sizeof(float));*/

        destBuffer.copyFrom(0, subBlockSize, data, 0, 0, numSamples - subBlockSize);
    }
}
