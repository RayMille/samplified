/*
  ==============================================================================

    InComponent.h
    Created: 23 May 2020 4:28:41pm
    Author:  Camille Koenders

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class InComponent    : public Component

{
public:
    InComponent (SamplifiedAudioProcessor& p);
    ~InComponent();
    
    Label label;

    void paint (Graphics&) override;
    void resized() override;
    
private:
    
    SamplifiedAudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InComponent)
};

