/*
  ==============================================================================

    VolumeComponent.h
    Created: 23 May 2020 1:07:56pm
    Author:  Camille Koenders

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "FilmStripKnob.h"


//==============================================================================
/*
*/
class VolumeComponent    : public Component
{
public:
    VolumeComponent (SamplifiedAudioProcessor& p);
    ~VolumeComponent();
    void paint (Graphics&) override;
    void resized() override;

private:
    
    SamplifiedAudioProcessor& processor;
    
    FilmStripKnob mVolumeSlider;
    Label mVolumeLabel;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mVolumeAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VolumeComponent)
};
