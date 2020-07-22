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
    : AudioProcessorEditor (&p), mVolume(p), mDisplayComponent (p),
      mDirectoryComponent(p), mADSR (p), mVoiceSetting(p), processor (p)
{
    double initialWidth = 960.0;
    double initialHeight = 339.0;

    startTimerHz (30);
   
    double ratio = initialWidth/initialHeight;
    m_constrainer.setSizeLimits(500, 500 / ratio, 2000, 2000 / ratio);
    m_constrainer.setFixedAspectRatio(ratio);

    setResizable(true, true);
    setConstrainer(&m_constrainer);
    //this->setResizable(true,true);
    
    addAndMakeVisible (mBackground);
    addAndMakeVisible(mDirectoryComponent);
    addAndMakeVisible (mDisplayComponent);
    addAndMakeVisible (mADSR);
    addAndMakeVisible (mVolume);
    
    mDirectoryComponent.m_fileBrowser->addListener(this);
    
    setSize (960, 960/ratio);
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
    float diffFromTopDirectory = getHeight()/21;
    float diffFromTopWaveWindow = getHeight()/15;
    float diffFromLeft = getWidth()/49;
    float diffFromRight = getWidth()/34;
    float gap = getWidth()/28;
    float widthDirectory = getWidth()/3.9;
    float heightWaveWindow = getHeight()/1.9;
    float volumeDiameter = getHeight()/4.3; //78
    float diffFromBottomVolume = getHeight()/12; //28
    float aSDRDiameter = getHeight()/5.5; //61
    float diffLeftADSR = 1.81*getWidth()/3;//578
    float diffBottomADSR = getHeight()/9.5; // 37
    float sizeBetweenADSR = getHeight()/10.4;
    
    mBackground.setBounds(0,0,getWidth(),getHeight());
    mDirectoryComponent.setBounds(diffFromLeft, diffFromTopDirectory, widthDirectory, getHeight()-2*diffFromTopDirectory);
    mDisplayComponent.setBounds (widthDirectory + gap + diffFromLeft, diffFromTopWaveWindow, getWidth()-diffFromLeft-gap-widthDirectory-diffFromRight, heightWaveWindow);
    mVolume.setBounds(widthDirectory + gap + diffFromLeft, getHeight()-volumeDiameter-diffFromBottomVolume, volumeDiameter, volumeDiameter);
    mADSR.setBounds(diffLeftADSR, getHeight()-aSDRDiameter-diffBottomADSR, aSDRDiameter*4+3*sizeBetweenADSR, aSDRDiameter);
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

