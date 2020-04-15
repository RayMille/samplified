/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "WaveThumbnail.h"
#include "ADSRComponent.h"
#include "BackgroundComponent.h"
#include "DirectoryComponent.h"

//==============================================================================
/**
*/
class SamplifiedAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    SamplifiedAudioProcessorEditor (SamplifiedAudioProcessor&);
    ~SamplifiedAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
private:
    WaveThumbnail mWaveThumbnail;
    ADSRComponent mADSR;
    BackgroundComponent mBackground;
    DirectoryComponent mDirectory;
    
    SamplifiedAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SamplifiedAudioProcessorEditor)
};
