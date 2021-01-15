/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
RecurrenceAudioProcessorEditor::RecurrenceAudioProcessorEditor (RecurrenceAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 600);

    masterGainValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.apvst, "master gain", masterGainSlider);

    masterGainSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    masterGainSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    masterGainSlider.setTextBoxIsEditable(true);
    masterGainSlider.setRange(-60.f, 0.f, 0.01f);
    addAndMakeVisible(&masterGainSlider);


    delayTimeValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.apvst, "delay time", delayTimeSlider);

    delayTimeSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    delayTimeSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    delayTimeSlider.setTextBoxIsEditable(true);
    delayTimeSlider.setRange(1, 10000, 1.f);
    addAndMakeVisible(&delayTimeSlider);


    delayFeedbackValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.apvst, "delay feedback", delayFeedbackSlider);

    delayFeedbackSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    delayFeedbackSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    delayFeedbackSlider.setTextBoxIsEditable(true);
    delayFeedbackSlider.setRange(0, 1, 0.01f);
    addAndMakeVisible(&delayFeedbackSlider);


    delayMixValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.apvst, "delay mix", delayMixSlider);

    delayMixSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    delayMixSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    delayMixSlider.setTextBoxIsEditable(true);
    delayMixSlider.setRange(0, 1, .01f);
    addAndMakeVisible(&delayMixSlider);
}

RecurrenceAudioProcessorEditor::~RecurrenceAudioProcessorEditor()
{
}

//==============================================================================
void RecurrenceAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    masterGainSlider.setBounds(getWidth() / 4 - 75, getHeight() / 2, 100, 100);

    delayTimeSlider.setBounds(getWidth() / 4 + 75, getHeight() / 2, 100, 100);
    delayFeedbackSlider.setBounds(getWidth() * 3 / 4 - 75, getHeight() / 2, 100, 100);
    delayMixSlider.setBounds(getWidth() * 3 / 4 + 75, getHeight() / 2, 100, 100);
}

void RecurrenceAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
