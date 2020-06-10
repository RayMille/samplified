/*
  ==============================================================================

    VolumeComponent.cpp
    Created: 23 May 2020 1:07:50pm
    Author:  Camille Koenders

  ==============================================================================
*/

#include <JuceHeader.h>
#include "VolumeComponent.h"

//==============================================================================
VolumeComponent::VolumeComponent (SamplifiedAudioProcessor& p) : processor (p)
{
    //AttackSlider
    mVolumeSlider.setSliderStyle (Slider::SliderStyle::RotaryVerticalDrag);
  
    mVolumeSlider.setTextBoxStyle (Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mVolumeSlider.setColour (Slider::ColourIds::thumbColourId, Colours::dimgrey);
    mVolumeSlider.setColour (Slider::ColourIds::rotarySliderOutlineColourId, Colours::transparentBlack);
    mVolumeSlider.setColour (Slider::ColourIds::rotarySliderFillColourId, Colours::transparentBlack);
//    //mAttackSlider.setRange (0.0f, 5.0f, 0.01f);
    addAndMakeVisible (mVolumeSlider);
//
//    mVolumeLabel.setFont (14.0f);
//    //mAttackLabel.setText ("A", NotificationType::dontSendNotification);
//    mVolumeLabel.setColour (Label::textColourId, Colours::white);
//    mVolumeLabel.setJustificationType(Justification::centred);
//    mVolumeLabel.attachToComponent (&mVolumeSlider, false);

    mVolumeAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "VOLUME", mVolumeSlider);

}

VolumeComponent::~VolumeComponent()
{
}

void VolumeComponent::paint (Graphics& g)
{
    mVolumeSlider.setBounds(0, 0, getWidth(), getHeight());
}

void VolumeComponent::resized()
{
    
}

