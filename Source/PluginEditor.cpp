/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SamplifiedAudioProcessorEditor::SamplifiedAudioProcessorEditor (SamplifiedAudioProcessor& p)
    : AudioProcessorEditor (&p), mWaveThumbnail (p), mADSR (p), mDirectory(p), processor (p)
{
    addAndMakeVisible (mBackground);
    addAndMakeVisible (mWaveThumbnail);
    addAndMakeVisible (mADSR);
    addAndMakeVisible (mDirectory);
    setSize (600, 400);
}

SamplifiedAudioProcessorEditor::~SamplifiedAudioProcessorEditor()
{
}

//==============================================================================
void SamplifiedAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::black);
}

void SamplifiedAudioProcessorEditor::resized()
{
    mWaveThumbnail.setBoundsRelative (0.0f, 0.25f, 1.0f, 0.5);
    mADSR.setBoundsRelative (0.0f, 0.75f, 1.0f, 0.25f);
    mDirectory.setBounds(0, 0, 300, 300);
    mBackground.setBounds(0,0,getWidth(),getHeight());
}



