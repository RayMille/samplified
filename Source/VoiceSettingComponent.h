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
    
    String fileName = "";
    
    const Drawable* getDefaultDocumentFileImage();
    
private:
    Label fileLabel;
    
    Label voiceLabel;
    Slider voiceInput;
    
    Label transpLabel;
    Slider transpInput;
    
    Label fineLabel;
    Slider fineInput;
    
    std::unique_ptr<Drawable> documentImage;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VoiceSettingComponent)
};
