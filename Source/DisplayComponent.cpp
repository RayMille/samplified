/*
  ==============================================================================

    DisplayComponent.cpp
    Created: 16 Apr 2020 6:56:51pm
    Author:  Camille Koenders

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DisplayComponent.h"

//==============================================================================
DisplayComponent::DisplayComponent (SamplifiedAudioProcessor& p) : processor (p),
mVoiceSetting(p), mWaveWindow(p)
{
    addAndMakeVisible(mVoiceSetting);

    addAndMakeVisible(mWaveWindow);
}

DisplayComponent::~DisplayComponent()
{
}

// This function draws the wave in the screen
void DisplayComponent::paint (Graphics& g)
{

    // Width of screen components in percentage
    // Adjust these values to change porpotions of elements
    // Should add up to 1.0f
    float wVoice = 0.315f;
    float wWave= 0.685f;
    
    mVoiceSetting.setBounds(0, 0, getWidth()*wVoice, getHeight());
    mWaveWindow.setBounds(getWidth()*wVoice, 0, getWidth()*wWave, getHeight());
}

void DisplayComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
