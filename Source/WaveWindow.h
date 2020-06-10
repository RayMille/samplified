/*
  ==============================================================================

    WaveWindow.h
    Created: 23 May 2020 4:01:25pm
    Author:  Camille Koenders

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "WaveThumbnail.h"
#include "InComponent.h"

//==============================================================================
/*
*/
class WaveWindow    : public Component

{
public:
    WaveWindow (SamplifiedAudioProcessor& p);
    ~WaveWindow();

    void paint (Graphics&) override;
    void resized() override;
    
private:
    
    WaveThumbnail mWaveThumbnail;
    
    InComponent mInComponent;
    
    InComponent mOutComponent;
    
    SamplifiedAudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveWindow)
};

