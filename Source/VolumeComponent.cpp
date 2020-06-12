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
VolumeComponent::VolumeComponent (SamplifiedAudioProcessor& p) : processor (p),
mVolumeSlider (BinaryData::FILMSTRIP1_100FR_VERT_270DEG_png, (size_t) BinaryData::FILMSTRIP1_100FR_VERT_270DEG_pngSize, 100, true, 2)
{
    
    //AttackSlider
    mVolumeSlider.setSliderStyle (Slider::SliderStyle::RotaryVerticalDrag);

    mVolumeSlider.setTextBoxStyle (Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    addAndMakeVisible (mVolumeSlider);

    mVolumeAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "VOLUME", mVolumeSlider);

}

VolumeComponent::~VolumeComponent()
{
}

void VolumeComponent::paint (Graphics& g)
{
    g.fillAll(Colours::red.withAlpha(0.5f));

    mVolumeSlider.setBounds(0, 0, getWidth(), getHeight());
}

void VolumeComponent::resized()
{
    
}

