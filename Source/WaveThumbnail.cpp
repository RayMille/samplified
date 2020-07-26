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

    g.strokePath(p, PathStrokeType(1));

    g.setColour(Colours::white);
    g.setFont(15.0f);
    auto textBounds = getLocalBounds().reduced (10, 10);
    g.drawFittedText(mFileName, textBounds, Justification::topRight, 1);

    auto playHeadPosition = jmap <int> (processor.getSampleCount(), 0,
                                        processor.getWaveForm().getNumSamples(), 0, getWidth());

    g.setColour(Colours::white);
    g.drawLine(playHeadPosition, 0, playHeadPosition, getHeight(), 2.0f);

    g.setColour(Colours::white.withAlpha(0.1f));
    g.fillRect(0, 0, playHeadPosition, getHeight());
    
    
    auto params = processor.getADSRParams();
    
    float duration = processor.getSampleDuration();
    auto lengthTimeRatio = getWidth()/duration; //weight per s
    
    auto attackWidth = params.attack*lengthTimeRatio;
    auto decayWidth = params.decay*lengthTimeRatio;
    auto sustainHeight = getHeight() - (getHeight()*params.sustain);
    auto releaseWidth = params.release*lengthTimeRatio;
    auto sustainWidth = calculateSustainWidth(decayWidth+attackWidth+releaseWidth);
    
    g.setColour(Colour (102,102,102));
    
    Path w;
    w.startNewSubPath(1, getHeight());
    w.lineTo(attackWidth, 0);
    w.lineTo(attackWidth + decayWidth, sustainHeight);
    w.lineTo(attackWidth + decayWidth + sustainWidth, sustainHeight);
    w.lineTo(getWidth()-1,getHeight());
    
    Path roundedPath = w.createPathWithRoundedCorners(10.0f);
    g.strokePath(roundedPath, PathStrokeType(1));
       
}

float WaveThumbnail::calculateSustainWidth(float sumOtherWidths){
    if(sumOtherWidths >= getWidth()) {
        return 0;
    }else{
        return getWidth()-sumOtherWidths;
    }
}

void WaveThumbnail::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
