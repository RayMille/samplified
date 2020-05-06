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
#include "FileWindowComponent.h"

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

private:
//    std::vector<float> mAudiopoints;
//    bool mShouldBePainting { false };
//
//    String mFileName { "" };
//
    SamplifiedAudioProcessor& processor;
    
    FileWindowComponent m_FileWindow;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DirectoryComponent)
};


