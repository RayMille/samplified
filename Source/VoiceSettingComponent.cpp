/*
  ==============================================================================

    VoiceSettingComponent.cpp
    Created: 6 May 2020 5:01:08pm
    Author:  Camille Koenders

  ==============================================================================
*/

#include <JuceHeader.h>
#include "VoiceSettingComponent.h"

//==============================================================================
VoiceSettingComponent::VoiceSettingComponent (SamplifiedAudioProcessor& p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

VoiceSettingComponent::~VoiceSettingComponent()
{
}

// This function draws the wave in the screen
void VoiceSettingComponent::paint (Graphics& g)
{
    float lineThickness = 0.6f;
    float lineTopBottomMargin = 0.05f;
    float marginLeftRight = 3;
    
    g.fillAll(Colours::transparentBlack.darker());
    
    g.setColour (Colours::white);
    g.drawLine(marginLeftRight, getHeight()*lineTopBottomMargin, marginLeftRight, getHeight()-getHeight()*lineTopBottomMargin,lineThickness);
    g.drawLine(getWidth()-marginLeftRight, getHeight()*lineTopBottomMargin, getWidth()-marginLeftRight, getHeight()-getHeight()*lineTopBottomMargin,lineThickness);
    
}

void VoiceSettingComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

