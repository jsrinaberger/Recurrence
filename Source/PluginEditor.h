/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class RecurrenceAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    RecurrenceAudioProcessorEditor (RecurrenceAudioProcessor&);
    ~RecurrenceAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    RecurrenceAudioProcessor& processor;

    Slider masterGainSlider;

    Slider delayTimeSlider;
    Slider delayFeedbackSlider;
    Slider delayMixSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RecurrenceAudioProcessorEditor)

public:

    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> masterGainValue;

    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> delayTimeValue;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> delayFeedbackValue;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> delayMixValue;
};
