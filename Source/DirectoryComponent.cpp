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
    fileFolder = File::getSpecialLocation(File::userHomeDirectory);
    int flags = FileBrowserComponent::openMode |
    FileBrowserComponent::canSelectFiles | FileBrowserComponent::useTreeView;
    m_wcFileFilter = new WildcardFileFilter("*.wav", "*", "Wav files");
    m_fileBrowser = new FileBrowserComponent(flags,fileFolder,m_wcFileFilter, NULL);

}

DirectoryComponent::~DirectoryComponent()
{
    m_fileBrowser->~FileBrowserComponent();
    delete (m_wcFileFilter);
}

// This function draws the wave in the screen
void DirectoryComponent::paint (Graphics& g)
{
    //-----------Nicht rauslöschen für Layouten -------///
    //g.fillAll(Colours::yellow);
    addAndMakeVisible(m_fileBrowser);
    m_fileBrowser->setBounds(0,0,getWidth(), getHeight());

    addAndMakeVisible(m_FileWindow);
    m_FileWindow.setBounds(0.0f, getHeight()/11, getWidth(), getHeight()-getHeight()/11+2.0f);
    m_FileWindow.setInterceptsMouseClicks(false, true);
    
}

void DirectoryComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
