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
mWaveThumbnail(p),mDirectoryComponent(p), mVoiceSetting(p)
{
    addAndMakeVisible(mDirectoryComponent);
    mDirectoryComponent.m_fileBrowser->addListener(this);

    addAndMakeVisible(mVoiceSetting);

    addAndMakeVisible(mWaveThumbnail);
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
    float wDir = 0.34f;
    float wVoice = 0.17f;
    float wWave= 0.49f;

    mDirectoryComponent.setBounds(0, 0, getWidth()*wDir, getHeight());
    mVoiceSetting.setBounds(getWidth()*wDir, 0, getWidth()*wVoice, getHeight());
    mWaveThumbnail.setBounds(getWidth()-getWidth()*wWave, 0, getWidth()*wWave, getHeight());
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
    if(mDirectoryComponent.m_fileBrowser->currentFileIsValid() && file.existsAsFile()){
        auto myFile = std::make_unique<File>(file);
        mFileName = myFile->getFileNameWithoutExtension();
        processor.LoadFile (file);
        mVoiceSetting.setFileName(mFileName);
    }

    repaint();

}

void DisplayComponent::fileDoubleClicked (const File& file)
{
}

void DisplayComponent::browserRootChanged (const File& newRoot)
{
}
