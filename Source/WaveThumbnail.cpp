/*
  ==============================================================================

    WaveThumbnail.cpp
    Created: 9 Apr 2020 2:20:48pm
    Author:  Johannes Koenders

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveThumbnail.h"

//==============================================================================
WaveThumbnail::WaveThumbnail (SamplifiedAudioProcessor& p) : processor (p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

WaveThumbnail::~WaveThumbnail()
{
}

// This function draws the wave in the screen
void WaveThumbnail::paint (Graphics& g)
{
    g.fillAll(Colours::black.brighter());
    
    auto waveform = processor.getWaveForm();
    
    if (waveform.getNumSamples() > 0)
    
    {
        Path p;
        mAudiopoints.clear();
        
        auto waveform = processor.getWaveForm();
        auto ratio = waveform.getNumSamples() / getWidth();
        auto buffer = waveform.getReadPointer (0);
        
        //scale x axis
        for (int sample = 0; sample < waveform.getNumSamples(); sample+=ratio)
        {
            mAudiopoints.push_back (buffer[sample]);
        }
        
        g.setColour(Colours::orange);
        p.startNewSubPath (0, getHeight() / 2);
        
        //scale y axis
        for (int sample = 0; sample < mAudiopoints.size(); ++sample)
        {
            auto point = jmap<float> (mAudiopoints[sample], -1.0f, 1.0f, getHeight(), 0);
            p.lineTo (sample, point);
        }
        
        g.strokePath(p, PathStrokeType(2));
        
        g.setColour(Colours::white);
        g.setFont(15.0f);
        auto textBounds = getLocalBounds().reduced (10, 10);
        g.drawFittedText(mFileName, textBounds, Justification::topRight, 1);
    }
    else
    {
        g.setColour(Colours::white);
        g.setFont(30.0f);
        g.drawFittedText("DROP FILE HERE", getLocalBounds(), Justification::centred, 1);
    }
}

void WaveThumbnail::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

bool WaveThumbnail::isInterestedInFileDrag (const StringArray& files)
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

void WaveThumbnail::filesDropped(const StringArray &files, int x, int y)
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

void WaveThumbnail::filesClicked(const File& file)
{
//    for (auto file : files)
//    {
//        if (isInterestedInFileDrag (file))
//        {
            auto myFile = std::make_unique<File>(file);
            mFileName = myFile->getFileNameWithoutExtension();
            processor.LoadFile (file);
        
//    }
    
    repaint();
}
