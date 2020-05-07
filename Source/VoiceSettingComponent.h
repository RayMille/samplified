/*
  ==============================================================================

    VoiceSettingComponent.h
    Created: 6 May 2020 5:01:17pm
    Author:  Camille Koenders

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class VoiceSettingComponent    : public Component

{
public:
    VoiceSettingComponent (SamplifiedAudioProcessor& p);
    ~VoiceSettingComponent();

    void paint (Graphics&) override;
    void resized() override;
    
    void setFileName(const String& name);
    
    String fileName = "Hi";
    
private:
    Label fileLabel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VoiceSettingComponent)
};
