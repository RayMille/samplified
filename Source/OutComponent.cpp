/*
  ==============================================================================

    OutComponent.cpp
    Created: 23 May 2020 4:29:00pm
    Author:  Camille Koenders

  ==============================================================================
*/
#include <JuceHeader.h>
#include "OutComponent.h"

//==============================================================================
OutComponent::OutComponent (SamplifiedAudioProcessor& p) : processor (p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

OutComponent::~OutComponent()
{
}

// This function draws the wave in the screen
void OutComponent::paint (Graphics& g)
{
  
}

void OutComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
