/*
  ==============================================================================

    DirectoryComponent.cpp
    Created: 9 Apr 2020 7:04:55pm
    Author:  Johannes Koenders

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DirectoryComponent.h"

//==============================================================================
DirectoryComponent::DirectoryComponent(SamplifiedAudioProcessor& p) : processor (p), mWaveThumbnail (p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

DirectoryComponent::~DirectoryComponent()
{
    processor.m_fileBrowser->removeListener(this);
}

void DirectoryComponent::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
    addAndMakeVisible(processor.m_fileBrowser);
    processor.m_fileBrowser->setSize(getWidth(), getHeight());
    processor.m_fileBrowser->setTopLeftPosition(0, 0);
    processor.m_fileBrowser->addListener(this);
}

void DirectoryComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

//==============================================================================
void DirectoryComponent::selectionChanged ()
{
}

void DirectoryComponent::fileClicked (const File& file, const MouseEvent& e)
{
    if(processor.m_fileBrowser->currentFileIsValid()){
        
//        auto myFile = std::make_unique<File>(processor.m_fileBrowser->getSelectedFile(0));
//        mFileName = myFile->getFileNameWithoutExtension();
        
        mWaveThumbnail.filesClicked(processor.m_fileBrowser->getSelectedFile(0));
        
        //processor.LoadFile (file);
        
        //processor.loadNewSample(processor.m_fileBrowser->getSelectedFile(0));
    }
}

void DirectoryComponent::fileDoubleClicked (const File& file)
{
}

void DirectoryComponent::browserRootChanged (const File& newRoot)
{
}

// String  "wjaskjabskxjabsk"
// String Array  ["wjaskjabskxjabsk", "hannes", "bier"]
// bool true/false
// int 1,2,3,4..
// void  nix
