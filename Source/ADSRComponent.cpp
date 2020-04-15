/*
  ==============================================================================

    ADSRComponent.cpp
    Created: 9 Apr 2020 4:32:46pm
    Author:  Johannes Koenders

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ADSRComponent.h"

//==============================================================================
ADSRComponent::ADSRComponent (SamplifiedAudioProcessor& p) : processor (p)
{
    //AttackSlider
    mAttackSlider.setSliderStyle (Slider::SliderStyle::RotaryVerticalDrag);
    mAttackSlider.setTextBoxStyle (Slider::TextBoxBelow, true, 40, 20);
    mAttackSlider.setColour (Slider::ColourIds::thumbColourId, Colours::orange);
    //mAttackSlider.setRange (0.0f, 5.0f, 0.01f);
    addAndMakeVisible (mAttackSlider);
    
    mAttackLabel.setFont (11.0f);
    mAttackLabel.setText ("Attack", NotificationType::dontSendNotification);
    mAttackLabel.setColour (Label::textColourId, Colours::white);
    mAttackLabel.setJustificationType(Justification::centredBottom);
    mAttackLabel.attachToComponent (&mAttackSlider, false);
    
    mAttackAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "ATTACK", mAttackSlider);
    
    //DecaySlider
    mDecaySlider.setSliderStyle (Slider::SliderStyle::RotaryVerticalDrag);
    mDecaySlider.setTextBoxStyle (Slider::TextBoxBelow, true, 40, 20);
    mDecaySlider.setColour (Slider::ColourIds::thumbColourId, Colours::orange);
    //mDecaySlider.setRange (0.0f, 5.0f, 0.01f);
    addAndMakeVisible (mDecaySlider);
    
    mDecayLabel.setFont (11.0f);
    mDecayLabel.setText ("Decay", NotificationType::dontSendNotification);
    mDecayLabel.setColour (Label::textColourId, Colours::white);
    mDecayLabel.setJustificationType(Justification::centredBottom);
    mDecayLabel.attachToComponent (&mDecaySlider, false);
    
    mDecayAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "DECAY", mDecaySlider);
    
    
    //SustainSlider
    mSustainSlider.setSliderStyle (Slider::SliderStyle::RotaryVerticalDrag);
    mSustainSlider.setTextBoxStyle (Slider::TextBoxBelow, true, 40, 20);
    mSustainSlider.setColour (Slider::ColourIds::thumbColourId, Colours::orange);
    //mSustainSlider.setRange (0.0f, 1.0f, 0.01f);
    addAndMakeVisible (mSustainSlider);
    
    mSustainLabel.setFont (11.0f);
    mSustainLabel.setText ("Sustain", NotificationType::dontSendNotification);
    mSustainLabel.setColour (Label::textColourId, Colours::white);
    mSustainLabel.setJustificationType(Justification::centredBottom);
    mSustainLabel.attachToComponent (&mSustainSlider, false);
    
    mSustainAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "SUSTAIN", mSustainSlider);
    
    
    //ReleaseSlider
    mReleaseSlider.setSliderStyle (Slider::SliderStyle::RotaryVerticalDrag);
    mReleaseSlider.setTextBoxStyle (Slider::TextBoxBelow, true, 40, 20);
    mReleaseSlider.setColour (Slider::ColourIds::thumbColourId, Colours::orange);
    //mReleaseSlider.setRange (0.0f, 5.0f, 0.01f);
    addAndMakeVisible (mReleaseSlider);
    
    mReleaseLabel.setFont (11.0f);
    mReleaseLabel.setText ("Release", NotificationType::dontSendNotification);
    mReleaseLabel.setColour (Label::textColourId, Colours::white);
    mReleaseLabel.setJustificationType(Justification::centredBottom);
    mReleaseLabel.attachToComponent (&mReleaseSlider, false);
    
    mReleaseAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "RELEASE", mReleaseSlider);

}

ADSRComponent::~ADSRComponent()
{
}

void ADSRComponent::paint (Graphics& g)
{
    g.fillAll (Colours::black);
}

void ADSRComponent::resized()
{
    const auto startX = 0.6f;
    const auto startY = 0.2f;
    const auto dialWidth = 0.1f;
    const auto dialHeight = 0.75f;
    
    mAttackSlider.setBoundsRelative (startX, startY, dialWidth, dialHeight);
    mDecaySlider.setBoundsRelative (startX + dialWidth, startY, dialWidth, dialHeight);
    mSustainSlider.setBoundsRelative (startX + dialWidth * 2, startY, dialWidth, dialHeight);
    mReleaseSlider.setBoundsRelative (startX + dialWidth * 3, startY, dialWidth, dialHeight);
}
