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

#pragma region Master_Controls

    masterGainValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.apvst, "master gain", masterGainSlider);

    masterGainSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    masterGainSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    masterGainSlider.setTextBoxIsEditable(true);
    masterGainSlider.setRange(-60.f, 0.f, 0.01f);
    addAndMakeVisible(&masterGainSlider);

#pragma endregion Master_Controls

    //==============================================================================

#pragma region Delay_Controls

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

#pragma endregion Delay_Controls

    //==============================================================================

#pragma region Saturation_Ctonrols

    saturationDriveValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.apvst, "saturation drive", saturationDriveSlider);

    saturationDriveSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    saturationDriveSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    saturationDriveSlider.setTextBoxIsEditable(true);
    saturationDriveSlider.setRange(0, 100, .1f);
    addAndMakeVisible(&saturationDriveSlider);


    saturationToneValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.apvst, "saturation tone", saturationToneSlider);

    saturationToneSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    saturationToneSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    saturationToneSlider.setTextBoxIsEditable(true);
    saturationToneSlider.setRange(0, 100, .1f);
    addAndMakeVisible(&saturationToneSlider);


    saturationMixValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.apvst, "saturation mix", saturationMixSlider);

    saturationMixSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    saturationMixSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    saturationMixSlider.setTextBoxIsEditable(true);
    saturationMixSlider.setRange(0, 100, .1f);
    addAndMakeVisible(&saturationMixSlider);


    saturationTypeValue = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(processor.apvst, "saturation type", saturationTypeMenu);

    saturationTypeMenu.addItem("Analog", 1);
    saturationTypeMenu.addItem("Soft Curve", 2);
    saturationTypeMenu.addItem("Hard Curve", 3);

    saturationTypeMenu.setSelectedId(1, true);
    saturationTypeMenu.setJustificationType(Justification::centred);
    addAndMakeVisible(&saturationTypeMenu);

#pragma endregion Saturation_Controls
}

RecurrenceAudioProcessorEditor::~RecurrenceAudioProcessorEditor()
{
}

//==============================================================================
void RecurrenceAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    masterGainSlider.setBounds(getWidth() / 4 - 75, getHeight() / 4, 100, 100);

    delayTimeSlider.setBounds(getWidth() / 4 + 75, getHeight() / 4, 100, 100);
    delayFeedbackSlider.setBounds(getWidth() * 3 / 4 - 75, getHeight() / 4, 100, 100);
    delayMixSlider.setBounds(getWidth() * 3 / 4 + 75, getHeight() / 4, 100, 100);

    saturationTypeMenu.setBounds(getWidth() / 4 - 75, getHeight() / 2, 150, 100);
    saturationDriveSlider.setBounds(getWidth() / 4 + 75, getHeight() / 2, 100, 100);
    saturationToneSlider.setBounds(getWidth() * 3 / 4 - 75, getHeight() / 2, 100, 100);
    saturationMixSlider.setBounds(getWidth() * 3 / 4 + 75, getHeight() / 2, 100, 100);
}

void RecurrenceAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
