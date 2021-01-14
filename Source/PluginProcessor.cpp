/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
RecurrenceAudioProcessor::RecurrenceAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
    :apvst(*this, nullptr, "PARAMETER", createParameterLayout())
{
}

RecurrenceAudioProcessor::~RecurrenceAudioProcessor()
{
}

//==============================================================================
const String RecurrenceAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool RecurrenceAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool RecurrenceAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool RecurrenceAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double RecurrenceAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int RecurrenceAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int RecurrenceAudioProcessor::getCurrentProgram()
{
    return 0;
}

void RecurrenceAudioProcessor::setCurrentProgram (int index)
{
}

const String RecurrenceAudioProcessor::getProgramName (int index)
{
    return {};
}

void RecurrenceAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void RecurrenceAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    const int numInputChannels = getTotalNumInputChannels();
    const int delayBufferSize = (sampleRate + samplesPerBlock) * 2;
    currentSampleRate = sampleRate;

    delayBuffer.clear();
    delayBuffer.setSize(numInputChannels, delayBufferSize);
}

void RecurrenceAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool RecurrenceAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void RecurrenceAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();


    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());


    const int bufferLength = buffer.getNumSamples();
    const int delayBufferLength = delayBuffer.getNumSamples();

    float gain = 0.3;

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        const float* bufferData = buffer.getReadPointer(channel);
        const float* delayBufferData = delayBuffer.getReadPointer(channel);
        const float* dryBuffer = buffer.getWritePointer(channel);

        // copy data from main buffer to the delay buffer
        if (delayBufferLength > bufferLength + writePosition)
        {
            delayBuffer.copyFromWithRamp(channel, writePosition, bufferData, bufferLength, gain, gain);
        }
        else
        {
            const int bufferRemaining = delayBufferLength - writePosition;
            
            delayBuffer.copyFromWithRamp(channel, writePosition, bufferData, bufferRemaining, gain, gain);
            delayBuffer.copyFromWithRamp(channel, 0, bufferData, bufferLength - bufferRemaining, gain, gain);
        }

        

        // ----------------------------------

        int delayTime = 500; // miliseconds
        const int readPosition = static_cast<int> (delayBufferLength + writePosition - (currentSampleRate * delayTime / 1000)) % delayBufferLength;
        
        if (delayBufferLength > bufferLength + readPosition)
        {
            buffer.addFrom(channel, 0, delayBufferData + readPosition, bufferLength);
        }
        else
        {
            const int bufferRemaining = delayBufferLength - readPosition;

            buffer.addFrom(channel, 0, delayBufferData + readPosition, bufferRemaining);
            buffer.addFrom(channel, bufferRemaining, delayBufferData, bufferLength - bufferRemaining);
        }

        
        // ----------------------------------

        if (delayBufferLength > bufferLength + writePosition)
        {
            delayBuffer.addFromWithRamp(channel, writePosition, dryBuffer, bufferLength, 0.8, 0.8);
        }
        else
        {
            const int bufferRemaining = delayBufferLength - writePosition;

            delayBuffer.addFromWithRamp(channel, bufferRemaining, dryBuffer, bufferRemaining, 0.8, 0.8);
            delayBuffer.addFromWithRamp(channel, 0, dryBuffer, bufferLength - bufferRemaining, 0.8, 0.8);
        }
    }

    writePosition += bufferLength;
    writePosition %= delayBufferLength;
}

//==============================================================================
bool RecurrenceAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* RecurrenceAudioProcessor::createEditor()
{
    return new RecurrenceAudioProcessorEditor (*this);
}

//==============================================================================
void RecurrenceAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void RecurrenceAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new RecurrenceAudioProcessor();
}

AudioProcessorValueTreeState::ParameterLayout RecurrenceAudioProcessor::createParameterLayout()
{
    std::vector <std::unique_ptr<RangedAudioParameter>> parameters;

    auto masterGainParam = std::make_unique<AudioParameterFloat>("master gain", "Master Gain", -60.f, 0.f, -6.f);
    parameters.push_back(std::move(masterGainParam));

    auto delayTimeParam = std::make_unique<AudioParameterFloat>("delay time", "Delay Time", 1, 10000, 500.f);
    parameters.push_back(std::move(delayTimeParam));

    auto delayFeedbackParam = std::make_unique<AudioParameterFloat>("delay feedback", "Delay Feedback", 0, 1, .5f);
    parameters.push_back(std::move(delayFeedbackParam));

    auto delayMixParam = std::make_unique<AudioParameterFloat>("delay mix", "Deleay Mix", 0.f, 100.f, 50.f);
    parameters.push_back(std::move(delayMixParam));

    return { parameters.begin(), parameters.end() };
}
