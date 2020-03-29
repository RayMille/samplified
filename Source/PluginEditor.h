/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class GLComponent;

class PluginSynthWithFileUploadAudioProcessorEditor  : public AudioProcessorEditor, public FileBrowserListener
{
public:
    PluginSynthWithFileUploadAudioProcessorEditor (Samplified&);
    ~PluginSynthWithFileUploadAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    //==============================================================================
    void selectionChanged () override;
    void fileClicked (const File& file, const MouseEvent& e) override;
    void fileDoubleClicked (const File& file) override;
    void browserRootChanged (const File& newRoot) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Samplified& processor;
    
    //==============================================================================
    AudioFormatManager formatManager;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource;
    
    ScopedPointer<GLComponent> glComponent;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginSynthWithFileUploadAudioProcessorEditor)
};
