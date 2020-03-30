/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "WavefrontObjFile.h"
#include "TeapotComponent.h"



//==============================================================================
class TeapotWrapperComponent    : public Component
{
public:
    TeapotWrapperComponent()
    {
       addAndMakeVisible (teapotComponent);
    }

    void paint (Graphics& g) override
    {
    }

    void resized() override
    {
        teapotComponent.setBounds(0,0,getWidth(),getHeight());
    }

private:
    TeapotComponent teapotComponent;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TeapotWrapperComponent)
};


class SamplifiedEditor  : public AudioProcessorEditor, public FileBrowserListener
{
public:
    SamplifiedEditor (SamplifiedPluginProcessor&);
    ~SamplifiedEditor();

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
    SamplifiedPluginProcessor& processor;
    
    //==============================================================================
    AudioFormatManager formatManager;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource;
    
    ScopedPointer<TeapotComponent> glComponent;
    TeapotWrapperComponent teapot;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SamplifiedEditor)
};
