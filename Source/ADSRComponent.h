/*
  ==============================================================================

    ADSRComponent.h
    Created: 9 Apr 2020 4:32:46pm
    Author:  Johannes Koenders

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"


//==============================================================================
/*
*/
class ADSRComponent    : public Component
{
public:
    ADSRComponent (SamplifiedAudioProcessor& p);
    ~ADSRComponent();
    void paint (Graphics&) override;
    void resized() override;

private:
    Slider mAttackSlider, mDecaySlider, mSustainSlider, mReleaseSlider;
    //TextBox mAttackTextBox, mDecayTextBox, mSustainTextBox, mReleaseTextBox;
    Label mAttackLabel, mDecayLabel, mSustainLabel, mReleaseLabel;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mAttackAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mDecayAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mSustainAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mReleaseAttachment;
    
    SamplifiedAudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ADSRComponent)
};
