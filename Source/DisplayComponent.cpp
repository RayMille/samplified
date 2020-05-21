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
mWaveThumbnail(p),mDirectoryComponent(p)
{
     addAndMakeVisible(mDirectoryComponent);
     processor.m_fileBrowser->addListener(this);
     
     addAndMakeVisible(mWaveThumbnail);
}

DisplayComponent::~DisplayComponent()
{
}

// This function draws the wave in the screen
void DisplayComponent::paint (Graphics& g)
{
    mDirectoryComponent.setBounds(0, 0, getWidth()/3, getHeight());
    mWaveThumbnail.setBounds(getWidth()/3, 0, getWidth()-(getWidth()/3), getHeight());
}

void DisplayComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

bool DisplayComponent::isInterestedInFileDrag (const StringArray& files)
{
    for (auto file : files)
    {
        if (file.contains(".wav") || file.contains(".mp3") || file.contains(".aif"))
        {
            return true;
        }
    }
    return false;
}

void DisplayComponent::filesDropped(const StringArray &files, int x, int y)
{
    for (auto file : files)
    {
        if (isInterestedInFileDrag (file))
        {
            auto myFile = std::make_unique<File>(file);
            mFileName = myFile->getFileNameWithoutExtension();
            
            processor.LoadFile (file);
        }
    }
    
    repaint();
}

//==============================================================================
void DisplayComponent::selectionChanged ()
{
}

void DisplayComponent::fileClicked (const File& file, const MouseEvent& e)
{
    if(processor.m_fileBrowser->currentFileIsValid()){
        
  
        auto myFile = std::make_unique<File>(file);
        mFileName = myFile->getFileNameWithoutExtension();
        processor.LoadFile (file);
    }

    repaint();

}

void DisplayComponent::fileDoubleClicked (const File& file)
{
}

void DisplayComponent::browserRootChanged (const File& newRoot)
{
}

