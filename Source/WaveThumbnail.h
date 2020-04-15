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
class WaveThumbnail    : public Component,
                         public FileDragAndDropTarget

{
public:
    WaveThumbnail (SamplifiedAudioProcessor& p);
    ~WaveThumbnail();

    void paint (Graphics&) override;
    void resized() override;
    
    bool isInterestedInFileDrag (const StringArray& files) override;
    void filesDropped (const StringArray& files, int x, int y) override;
    void filesClicked (const File& file);

private:
    std::vector<float> mAudiopoints;
    bool mShouldBePainting { false };
    
    String mFileName { "" };
    
    SamplifiedAudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveThumbnail)
};
