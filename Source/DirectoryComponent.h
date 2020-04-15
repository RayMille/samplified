/*
  ==============================================================================

    DirectoryComponent.h
    Created: 9 Apr 2020 7:04:55pm
    Author:  Johannes Koenders

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "WaveThumbnail.h"

//==============================================================================
/*
*/
class DirectoryComponent    : public Component, public FileBrowserListener
{
public:
    DirectoryComponent(SamplifiedAudioProcessor& p);
    ~DirectoryComponent();

    void paint (Graphics&) override;
    void resized() override;
    
    //==============================================================================
    void selectionChanged () override;
    void fileClicked (const File& file, const MouseEvent& e) override;
    void fileDoubleClicked (const File& file) override;
    void browserRootChanged (const File& newRoot) override;

private:
    SamplifiedAudioProcessor& processor;
    
    AudioFormatManager formatManager;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource;
    
    WaveThumbnail mWaveThumbnail;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DirectoryComponent)
};
