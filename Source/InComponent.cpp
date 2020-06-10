/*
  ==============================================================================

    InComponent.cpp
    Created: 23 May 2020 4:28:34pm
    Author:  Camille Koenders

  ==============================================================================
*/

#include <JuceHeader.h>
#include "InComponent.h"

//==============================================================================
InComponent::InComponent (SamplifiedAudioProcessor& p) :  processor (p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addAndMakeVisible(label);

}

InComponent::~InComponent()
{
}

// This function draws the wave in the screen
void InComponent::paint (Graphics& g)
{
    float labelY = 3*(getHeight()/7);
    label.setColour (Label::textColourId, Colours::white);
    label.setText("In", dontSendNotification);
    label.setBounds(0, labelY, getWidth()/10, getHeight()/7);
    
    g.setColour (Colours::orange);
    
    float lineHeight = getHeight()/17;
    
    float widthRight = getWidth()-label.getWidth(); //* somefactor for amount
    
    float widthLeft = getWidth()-label.getWidth(); //*somefactorforamount
 
    g.fillRect ((float) label.getWidth(), (float) labelY, widthRight, (float) lineHeight);
    
    g.fillRect ((float) label.getWidth(), (float) labelY + label.getHeight() - lineHeight, widthLeft, (float) lineHeight);
}

void InComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

