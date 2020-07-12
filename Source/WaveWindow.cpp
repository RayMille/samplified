/*
  ==============================================================================

    WaveWindow.cpp
    Created: 23 May 2020 4:01:18pm
    Author:  Camille Koenders

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveWindow.h"

//==============================================================================
WaveWindow::WaveWindow (SamplifiedAudioProcessor& p) : mWaveThumbnail (p),mInComponent(p), mOutComponent(p), processor (p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    addAndMakeVisible(mWaveThumbnail);
    addAndMakeVisible(mInComponent);
    addAndMakeVisible(mOutComponent);

}

WaveWindow::~WaveWindow()
{
}

// This function draws the wave in the screen
void WaveWindow::paint (Graphics& g)
{
    //-----------Nicht rauslöschen für Layouten -------///
    //g.fillAll(Colours::green.withAlpha(0.6f));

      auto waveform = processor.getWaveForm();

      if (waveform.getNumSamples() > 0)
      {
          mInComponent.setBounds(getWidth()/5, 0, 3*getWidth()/5, getHeight()/3);
          mWaveThumbnail.setBounds(getWidth()/5, getHeight()/3, 3*getWidth()/5, getHeight()/3);
          mOutComponent.setBounds(getWidth()/5, 2*(getHeight()/3), 3*getWidth()/5, getHeight()/3);
      }
      else
      {
          g.setColour(Colours::white);
          g.setFont(20.0f);
          g.drawFittedText("SELECT OR DROP FILE", getLocalBounds(), Justification::centred, 1);
      }
}

void WaveWindow::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
