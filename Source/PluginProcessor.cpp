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

    updateParameters();


    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());


    const int bufferLength = buffer.getNumSamples();
    const int delayBufferLength = delayBuffer.getNumSamples();

    float gain = delayMix;

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

        const int readPosition = static_cast<int> (delayBufferLength + writePosition - (currentSampleRate * delayTime / 1000)) % delayBufferLength;
        
        if (delayBufferLength > bufferLength + readPosition)
        {
            buffer.addFromWithRamp(channel, 0, delayBufferData + readPosition, bufferLength, delayMix, delayMix);
        }
        else
        {
            const int bufferRemaining = delayBufferLength - readPosition;

            buffer.addFromWithRamp(channel, 0, delayBufferData + readPosition, bufferRemaining, delayMix, delayMix);
            buffer.addFromWithRamp(channel, bufferRemaining, delayBufferData, bufferLength - bufferRemaining, delayMix, delayMix);
        }

        
        // ----------------------------------

        if (delayBufferLength > bufferLength + writePosition)
        {
            delayBuffer.addFromWithRamp(channel, writePosition, dryBuffer, bufferLength, delayFeedback, delayFeedback);
        }
        else
        {
            const int bufferRemaining = delayBufferLength - writePosition;

            delayBuffer.addFromWithRamp(channel, bufferRemaining, dryBuffer, bufferRemaining, delayFeedback, delayFeedback);
            delayBuffer.addFromWithRamp(channel, 0, dryBuffer, bufferLength - bufferRemaining, delayFeedback, delayFeedback);
        }

        // ------------------------
        auto* channelData = buffer.getWritePointer(channel);

        for (int sample = 0; sample < bufferLength; sample++)
        {
            channelData[sample] *= Decibels::decibelsToGain(masterGain);
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
    auto savedState = apvst.copyState();
    std::unique_ptr<XmlElement> xmlInfo(savedState.createXml());
    copyXmlToBinary(*xmlInfo, destData);
}

void RecurrenceAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> xmlInfo(getXmlFromBinary(data, sizeInBytes));

    if (xmlInfo.get() != nullptr)
    {
        if (xmlInfo->hasTagName(apvst.state.getType()))
        {
            apvst.replaceState(ValueTree::fromXml(*xmlInfo));
        }
    }
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

    //==============================================================================

    auto delayTimeParam = std::make_unique<AudioParameterFloat>("delay time", "Delay Time", 1, 10000, 500.f);
    parameters.push_back(std::move(delayTimeParam));

    auto delayFeedbackParam = std::make_unique<AudioParameterFloat>("delay feedback", "Delay Feedback", 0, 1, .5f);
    parameters.push_back(std::move(delayFeedbackParam));

    auto delayMixParam = std::make_unique<AudioParameterFloat>("delay mix", "Delay Mix", 0.f, 1.f, 0.5f);
    parameters.push_back(std::move(delayMixParam));

    //==============================================================================

    StringArray saturationTypeChoices;
    saturationTypeChoices.add("Analog");
    saturationTypeChoices.add("Soft Clip");
    saturationTypeChoices.add("Hard Clip");

    auto saturationTypeParam = std::make_unique<AudioParameterChoice>("saturation type", "Saturation Type", saturationTypeChoices, 0, "Saturation Type", nullptr, nullptr);
    parameters.push_back(std::move(saturationTypeParam));

    auto saturationDriveParam = std::make_unique<AudioParameterFloat>("saturation drive", "Saturation Drive", 0.f, 100.f, 50.f);
    parameters.push_back(std::move(saturationDriveParam));

    auto saturationToneParam = std::make_unique<AudioParameterFloat>("saturation tone", "Saturation Tone", 0.f, 100.f, 50.f);
    parameters.push_back(std::move(saturationToneParam));

    auto saturationMixParam = std::make_unique<AudioParameterFloat>("saturation mix", "Saturation Mix", 0.f, 100.f, 50.f);
    parameters.push_back(std::move(saturationMixParam));

    return { parameters.begin(), parameters.end() };
}

void RecurrenceAudioProcessor::updateParameters() {
    masterGain = *(apvst.getRawParameterValue("master gain"));

    delayTime = *(apvst.getRawParameterValue("delay time"));
    delayFeedback = *(apvst.getRawParameterValue("delay feedback"));
    delayMix = *(apvst.getRawParameterValue("delay mix"));
}
