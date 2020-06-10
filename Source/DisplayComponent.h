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
#include "WaveThumbnail.h"
#include "VoiceSettingComponent.h"

//==============================================================================
/*
*/
class DisplayComponent    : public Component,
                         public FileDragAndDropTarget,
                         public FileBrowserListener


{
public:
    DisplayComponent (SamplifiedAudioProcessor& p);
    ~DisplayComponent();

    void paint (Graphics&) override;
    void resized() override;

    //========================Functions from Drag and Drop==========================
    bool isInterestedInFileDrag (const StringArray& files) override;
    void filesDropped (const StringArray& files, int x, int y) override;

    //=========================Functions from File Browser==========================
    void selectionChanged () override;
    void fileClicked (const File& file, const MouseEvent& e) override;
    void fileDoubleClicked (const File& file) override;
    void browserRootChanged (const File& newRoot) override;

private:
    std::vector<float> mAudiopoints;
    bool mShouldBePainting { false };

    String mFileName { "" };

    SamplifiedAudioProcessor& processor;

    WaveThumbnail mWaveThumbnail;
    DirectoryComponent mDirectoryComponent;
    
    VoiceSettingComponent mVoiceSetting;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DisplayComponent)
};
