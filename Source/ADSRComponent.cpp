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
ADSRComponent::ADSRComponent (SamplifiedAudioProcessor& p) :
mAttackSlider (BinaryData::FILMSTRIP1_100FR_VERT_270DEG_png, (size_t) BinaryData::FILMSTRIP1_100FR_VERT_270DEG_pngSize, 100, true, 2),
mDecaySlider (BinaryData::FILMSTRIP1_100FR_VERT_270DEG_png, (size_t) BinaryData::FILMSTRIP1_100FR_VERT_270DEG_pngSize, 100, true, 2),
mSustainSlider (BinaryData::FILMSTRIP1_100FR_VERT_270DEG_png, (size_t) BinaryData::FILMSTRIP1_100FR_VERT_270DEG_pngSize, 100, true, 2),
mReleaseSlider (BinaryData::FILMSTRIP1_100FR_VERT_270DEG_png, (size_t) BinaryData::FILMSTRIP1_100FR_VERT_270DEG_pngSize, 100, true, 2),
processor (p)
{
    ///-------------------------------------------- AttackSlider --------------------------------------------
    mAttackSlider.setSliderStyle (Slider::SliderStyle::RotaryVerticalDrag);
  
    mAttackSlider.setTextBoxStyle (Slider::NoTextBox, true, 50, 14);
    mAttackSlider.setColour (Slider::ColourIds::thumbColourId, Colours::dimgrey);
    mAttackSlider.setColour (Slider::ColourIds::rotarySliderOutlineColourId, Colours::transparentBlack);
    mAttackSlider.setColour (Slider::ColourIds::rotarySliderFillColourId, Colours::transparentBlack);
    addAndMakeVisible (mAttackSlider);

    mAttackLabel.setFont (14.0f);
    mAttackLabel.setColour (Label::textColourId, Colours::white);
    mAttackLabel.setJustificationType(Justification::centred);

    mAttackAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "ATTACK", mAttackSlider);

    ///--------------------------------------------DecaySlider--------------------------------------------
    mDecaySlider.setSliderStyle (Slider::SliderStyle::RotaryVerticalDrag);
    mDecaySlider.setTextBoxStyle (Slider::NoTextBox, true, 50, 14);
    mDecaySlider.setColour (Slider::ColourIds::thumbColourId, Colours::dimgrey);
    mDecaySlider.setColour (Slider::ColourIds::rotarySliderOutlineColourId, Colours::transparentBlack);
    mDecaySlider.setColour (Slider::ColourIds::rotarySliderFillColourId, Colours::transparentBlack);
    addAndMakeVisible (mDecaySlider);

    mDecayLabel.setFont (14.0f);
    mDecayLabel.setColour (Label::textColourId, Colours::white);
    mDecayLabel.setJustificationType(Justification::centred);

    mDecayAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "DECAY", mDecaySlider);


    ///--------------------------------------------SustainSlider--------------------------------------------
    mSustainSlider.setSliderStyle (Slider::SliderStyle::RotaryVerticalDrag);
    mSustainSlider.setTextBoxStyle (Slider::NoTextBox, true, 50, 14);
    mSustainSlider.setColour (Slider::ColourIds::thumbColourId, Colours::dimgrey);
    mSustainSlider.setColour (Slider::ColourIds::rotarySliderOutlineColourId, Colours::transparentBlack);
    mSustainSlider.setColour (Slider::ColourIds::rotarySliderFillColourId, Colours::transparentBlack);
    addAndMakeVisible (mSustainSlider);

    mSustainLabel.setFont (14.0f);
    mSustainLabel.setColour (Label::textColourId, Colours::white);
    mSustainLabel.setJustificationType(Justification::centred);

    mSustainAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "SUSTAIN", mSustainSlider);


    ///--------------------------------------------ReleaseSlider--------------------------------------------
    mReleaseSlider.setSliderStyle (Slider::SliderStyle::RotaryVerticalDrag);
    mReleaseSlider.setTextBoxStyle (Slider::NoTextBox, true, 50, 14);
    mReleaseSlider.setColour (Slider::ColourIds::thumbColourId, Colours::dimgrey);
    mReleaseSlider.setColour (Slider::ColourIds::rotarySliderOutlineColourId, Colours::transparentBlack);
    mReleaseSlider.setColour (Slider::ColourIds::rotarySliderFillColourId, Colours::transparentBlack);
    addAndMakeVisible (mReleaseSlider);

    mReleaseLabel.setFont (14.0f);
    mReleaseLabel.setColour (Label::textColourId, Colours::white);
    mReleaseLabel.setJustificationType(Justification::centred);

    mReleaseAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "RELEASE", mReleaseSlider);

}

ADSRComponent::~ADSRComponent()
{
}

void ADSRComponent::paint (Graphics& g)
{
    //g.fillAll(Colours::purple.withAlpha(0.1f));
}

void ADSRComponent::resized()
{
    const auto startX = 0;
    const auto startY = 0;
    const auto dialWidth = getHeight();
    const auto dialHeight = getHeight();
    const auto distance = getHeight()/1.8;//33.5

    mAttackSlider.setBounds(startX, startY, dialWidth, dialHeight);
    mDecaySlider.setBounds(startX + dialWidth+distance, startY, dialWidth, dialHeight);
    mSustainSlider.setBounds(startX + dialWidth * 2 + distance*2, startY, dialWidth, dialHeight);
    mReleaseSlider.setBounds(startX + dialWidth * 3 + distance *3, startY, dialWidth, dialHeight);
}
