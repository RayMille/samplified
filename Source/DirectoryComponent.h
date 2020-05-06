/*
  ==============================================================================

    DirectoryComponent.h
    Created: 16 Apr 2020 6:57:44pm
    Author:  Camille Koenders

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "FileGradientComponent.h"

//==============================================================================
/*
*/
class DirectoryComponent    : public Component

{
public:
    DirectoryComponent (SamplifiedAudioProcessor& p);
    ~DirectoryComponent();

    void paint (Graphics&) override;
    void resized() override;
    
    //==============================================================================
    FileBrowserComponent* m_fileBrowser;

private:
    SamplifiedAudioProcessor& processor;
    
    FileGradientComponent m_FileWindow;
    
    //==============================================================================
    File fileFolder;
    WildcardFileFilter* m_wcFileFilter;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DirectoryComponent)
};


