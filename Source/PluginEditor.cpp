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
    : AudioProcessorEditor (&p), mDisplayComponent (p), mADSR (p), mVolume(p), processor (p)
{
    addAndMakeVisible (mBackground);
    addAndMakeVisible (mDisplayComponent);
    addAndMakeVisible (mADSR);
    addAndMakeVisible (mVolume);
    
    startTimerHz (30);
    setSize (960, 339);
}

SamplifiedAudioProcessorEditor::~SamplifiedAudioProcessorEditor()
{
    stopTimer();
}

//==============================================================================
void SamplifiedAudioProcessorEditor::paint (Graphics& g)
{
    //g.fillAll (Colours::black);
}

void SamplifiedAudioProcessorEditor::resized()
{
    //mDisplayComponent.setBoundsRelative (0.0f, 0.25f, 1.0f, 0.5);
    mDisplayComponent.setBounds (getWidth()/20, getHeight()/7.8, getWidth() -(getWidth()/10),getHeight()/2);
    mADSR.setBoundsRelative (-0.3f, 0.6f, 1.3f, 0.4f);
    mBackground.setBounds(0,0,getWidth(),getHeight());
    int mVolumeHeight = 110;
    mVolume.setBounds(16, getHeight()-mVolumeHeight-2, 110, mVolumeHeight);
}

void SamplifiedAudioProcessorEditor::timerCallback()
{
    repaint();
}

