/*
  ==============================================================================

    DisplayComponent.h
    Created: 16 Apr 2020 6:57:07pm
    Author:  Camille Koenders

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "DirectoryComponent.h"
#include "WaveWindow.h"
#include "VoiceSettingComponent.h"

//==============================================================================
/*
*/
class DisplayComponent    : public Component


{
public:
    DisplayComponent (SamplifiedAudioProcessor& p);
    ~DisplayComponent();

    void paint (Graphics&) override;
    void resized() override;
    
    VoiceSettingComponent mVoiceSetting;

private:
    std::vector<float> mAudiopoints;
    bool mShouldBePainting { false };

    SamplifiedAudioProcessor& processor;

    WaveWindow mWaveWindow;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DisplayComponent)
};
