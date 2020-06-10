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
#include "VolumeComponent.h"

//==============================================================================
/**
*/
class SamplifiedAudioProcessorEditor  : public AudioProcessorEditor,
                                        public Timer,
                                        public FileDragAndDropTarget,
                                        public FileBrowserListener
{
public:
    SamplifiedAudioProcessorEditor (SamplifiedAudioProcessor&);
    ~SamplifiedAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void timerCallback() override;
    
    //========================Functions from Drag and Drop==========================
    bool isInterestedInFileDrag (const StringArray& files) override;
    void filesDropped (const StringArray& files, int x, int y) override;
    
    //=========================Functions from File Browser==========================
    void selectionChanged () override;
    void fileClicked (const File& file, const MouseEvent& e) override;
    void fileDoubleClicked (const File& file) override;
    void browserRootChanged (const File& newRoot) override;
    
private:
    DisplayComponent mDisplayComponent;
    DirectoryComponent mDirectoryComponent;
    ADSRComponent mADSR;
    BackgroundComponent mBackground;
    VolumeComponent mVolume;
    
    String mFileName { "" };
    
    VoiceSettingComponent mVoiceSetting;

    SamplifiedAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SamplifiedAudioProcessorEditor)
};
