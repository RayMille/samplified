/*
  ==============================================================================

    OutComponent.h
    Created: 23 May 2020 4:29:12pm
    Author:  Camille Koenders

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class OutComponent    : public Component

{
public:
    OutComponent (SamplifiedAudioProcessor& p);
    ~OutComponent();

    void paint (Graphics&) override;
    void resized() override;
    
private:
    
    SamplifiedAudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OutComponent)
};
