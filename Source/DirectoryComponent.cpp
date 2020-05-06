/*
  ==============================================================================

    DirectoryComponent.cpp
    Created: 16 Apr 2020 6:57:28pm
    Author:  Camille Koenders

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DirectoryComponent.h"

//==============================================================================
DirectoryComponent::DirectoryComponent (SamplifiedAudioProcessor& p) : processor (p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

DirectoryComponent::~DirectoryComponent()
{
}

// This function draws the wave in the screen
void DirectoryComponent::paint (Graphics& g)
{
    addAndMakeVisible(processor.m_fileBrowser);
    processor.m_fileBrowser->setBounds(0,0,getWidth(), getHeight());
    
    addAndMakeVisible(m_FileWindow);
    m_FileWindow.setBounds(0, getHeight()/8, getWidth(), getHeight());
    m_FileWindow.setInterceptsMouseClicks(false, true);
}

void DirectoryComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    
}

