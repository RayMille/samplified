/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "ADSRComponent.h"
#include "BackgroundComponent.h"
#include "DisplayComponent.h"

//==============================================================================
/**
*/
class SamplifiedAudioProcessorEditor  : public AudioProcessorEditor,
                                        public Timer
{
public:
    SamplifiedAudioProcessorEditor (SamplifiedAudioProcessor&);
    ~SamplifiedAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void timerCallback() override;
    
private:
    DisplayComponent mDisplayComponent;
    ADSRComponent mADSR;
    BackgroundComponent mBackground;
    
    SamplifiedAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SamplifiedAudioProcessorEditor)
};
