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
    //lalal
    mAttackSlider.setSliderStyle (Slider::SliderStyle::RotaryVerticalDrag);
  
    mAttackSlider.setTextBoxStyle (Slider::TextBoxBelow, true, 50, 14);
    mAttackSlider.setColour (Slider::ColourIds::thumbColourId, Colours::dimgrey);
    mAttackSlider.setColour (Slider::ColourIds::rotarySliderOutlineColourId, Colours::transparentBlack);
    mAttackSlider.setColour (Slider::ColourIds::rotarySliderFillColourId, Colours::transparentBlack);
    //mAttackSlider.setRange (0.0f, 5.0f, 0.01f);
    addAndMakeVisible (mAttackSlider);
    
    mAttackLabel.setFont (14.0f);
    //mAttackLabel.setText ("A", NotificationType::dontSendNotification);
    mAttackLabel.setColour (Label::textColourId, Colours::white);
    mAttackLabel.setJustificationType(Justification::centred);
    mAttackLabel.attachToComponent (&mAttackSlider, false);
    
    mAttackAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "ATTACK", mAttackSlider);
    
    //DecaySlider
    mDecaySlider.setSliderStyle (Slider::SliderStyle::RotaryVerticalDrag);
    mDecaySlider.setTextBoxStyle (Slider::TextBoxBelow, true, 50, 14);
    mDecaySlider.setColour (Slider::ColourIds::thumbColourId, Colours::dimgrey);
    mDecaySlider.setColour (Slider::ColourIds::rotarySliderOutlineColourId, Colours::transparentBlack);
    mDecaySlider.setColour (Slider::ColourIds::rotarySliderFillColourId, Colours::transparentBlack);
    //mDecaySlider.setRange (0.0f, 5.0f, 0.01f);
    addAndMakeVisible (mDecaySlider);
    
    mDecayLabel.setFont (14.0f);
    //mDecayLabel.setText ("D", NotificationType::dontSendNotification);
    mDecayLabel.setColour (Label::textColourId, Colours::white);
    mDecayLabel.setJustificationType(Justification::centred);
    mDecayLabel.attachToComponent (&mDecaySlider, false);
    
    mDecayAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "DECAY", mDecaySlider);
    
    
    //SustainSlider
    mSustainSlider.setSliderStyle (Slider::SliderStyle::RotaryVerticalDrag);
    mSustainSlider.setTextBoxStyle (Slider::TextBoxBelow, true, 50, 14);
    mSustainSlider.setColour (Slider::ColourIds::thumbColourId, Colours::dimgrey);
    mSustainSlider.setColour (Slider::ColourIds::rotarySliderOutlineColourId, Colours::transparentBlack);
    mSustainSlider.setColour (Slider::ColourIds::rotarySliderFillColourId, Colours::transparentBlack);
    //mSustainSlider.setRange (0.0f, 1.0f, 0.01f);
    addAndMakeVisible (mSustainSlider);
    
    mSustainLabel.setFont (14.0f);
    //mSustainLabel.setText ("S", NotificationType::dontSendNotification);
    mSustainLabel.setColour (Label::textColourId, Colours::white);
    mSustainLabel.setJustificationType(Justification::centred);
    mSustainLabel.attachToComponent (&mSustainSlider, false);
    
    mSustainAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "SUSTAIN", mSustainSlider);
    
    
    //ReleaseSlider
    mReleaseSlider.setSliderStyle (Slider::SliderStyle::RotaryVerticalDrag);
    mReleaseSlider.setTextBoxStyle (Slider::TextBoxBelow, true, 50, 14);
    mReleaseSlider.setColour (Slider::ColourIds::thumbColourId, Colours::dimgrey);
    mReleaseSlider.setColour (Slider::ColourIds::rotarySliderOutlineColourId, Colours::transparentBlack);
    mReleaseSlider.setColour (Slider::ColourIds::rotarySliderFillColourId, Colours::transparentBlack);
    //mReleaseSlider.setRange (0.0f, 5.0f, 0.01f);
    addAndMakeVisible (mReleaseSlider);
    
    mReleaseLabel.setFont (14.0f);
    //mReleaseLabel.setText ("R", NotificationType::dontSendNotification);
    mReleaseLabel.setColour (Label::textColourId, Colours::white);
    mReleaseLabel.setJustificationType(Justification::centred);
    mReleaseLabel.attachToComponent (&mReleaseSlider, false);
    
    mReleaseAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "RELEASE", mReleaseSlider);

}

ADSRComponent::~ADSRComponent()
{
}

void ADSRComponent::paint (Graphics& g)
{
}

void ADSRComponent::resized()
{
    const auto startX = 0.6053075f;
    const auto startY = 0.255f;
    const auto dialWidth = 0.0967f;
    const auto dialHeight = 0.64f;
    
    mAttackSlider.setBoundsRelative (startX, startY, dialWidth, dialHeight);
    mDecaySlider.setBoundsRelative (startX + dialWidth, startY, dialWidth, dialHeight);
    mSustainSlider.setBoundsRelative (startX + dialWidth * 2, startY, dialWidth, dialHeight);
    mReleaseSlider.setBoundsRelative (startX + dialWidth * 3, startY, dialWidth, dialHeight);
}
