/*
  ==============================================================================

    WaveThumbnail.h
    Created: 9 Apr 2020 2:20:48pm
    Author:  Johannes Koenders

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class WaveThumbnail    : public Component

{
public:
    WaveThumbnail (SamplifiedAudioProcessor& p);
    ~WaveThumbnail();

    void paint (Graphics&) override;
    void resized() override;
    
    float calculateSustainWidth(float sumOtherWidths);
    
private:
    
    std::vector<float> mAudiopoints;
    
    String mFileName { "" };
    
    SamplifiedAudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveThumbnail)
};
