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
    : AudioProcessorEditor (&p), mDisplayComponent (p), mADSR (p), mVolume(p), processor (p),
      mDirectoryComponent(p), mVoiceSetting(p)
{
    addAndMakeVisible (mBackground);
    addAndMakeVisible(mDirectoryComponent);
    addAndMakeVisible (mDisplayComponent);
    addAndMakeVisible (mADSR);
    addAndMakeVisible (mVolume);
    
    mDirectoryComponent.m_fileBrowser->addListener(this);
    
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
    float diffFromTop = getHeight()/20;
    float diffFromSides = getWidth()/50;
    float gap = getWidth()/30;
    float widthDirectory = getWidth()/3.9;
    float heightWaveWindow = getHeight()/2;
    
    mDirectoryComponent.setBounds(diffFromSides+10, diffFromTop+10, widthDirectory-20, getHeight()-2*diffFromTop-40);
    mDisplayComponent.setBounds (widthDirectory + gap + diffFromSides+10, diffFromTop+10, getWidth()-2*diffFromSides-gap-widthDirectory, heightWaveWindow-10);
    float aSDRDiameter = 61;
    float sizeBetweenADSR = 50;
    mADSR.setBounds(1.8*getWidth()/3+2, getHeight()-aSDRDiameter-37, aSDRDiameter*4+3*sizeBetweenADSR, aSDRDiameter);
    mBackground.setBounds(0,0,getWidth(),getHeight());
    float volumeDiameter = 78;
    mVolume.setBounds(widthDirectory + gap + diffFromSides+4, getHeight()-volumeDiameter-28, volumeDiameter, volumeDiameter);
}

void SamplifiedAudioProcessorEditor::timerCallback()
{
    repaint();
}

bool SamplifiedAudioProcessorEditor::isInterestedInFileDrag (const StringArray& files)
{
    for (auto file : files)
    {
        if (file.contains(".wav") || file.contains(".mp3") || file.contains(".aif"))
        {
            return true;
        }
    }
    return false;
}

void SamplifiedAudioProcessorEditor::filesDropped(const StringArray &files, int x, int y)
{
    for (auto file : files)
    {
        if (isInterestedInFileDrag (file))
        {
            auto myFile = std::make_unique<File>(file);
            mFileName = myFile->getFileNameWithoutExtension();
            
            processor.LoadFile (file);
        }
    }
    
    repaint();
}

//==============================================================================
void SamplifiedAudioProcessorEditor::selectionChanged ()
{
}

void SamplifiedAudioProcessorEditor::fileClicked (const File& file, const MouseEvent& e)
{
    if(mDirectoryComponent.m_fileBrowser->currentFileIsValid() && file.existsAsFile()){
        auto myFile = std::make_unique<File>(file);
        mFileName = myFile->getFileNameWithoutExtension();
        processor.LoadFile (file);
        mDisplayComponent.mVoiceSetting.setFileName(mFileName);
    }
    
    repaint();
    
}

void SamplifiedAudioProcessorEditor::fileDoubleClicked (const File& file)
{
}

void SamplifiedAudioProcessorEditor::browserRootChanged (const File& newRoot)
{
}

