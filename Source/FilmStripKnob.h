/*
  ==============================================================================

    FilmStripKnob.h
    Created: 4 May 2020 9:23:16pm
    Author:  Johannes Koenders

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class FilmStripKnob : public Slider
{
public:
    FilmStripKnob(const void* knob_png, const int knob_pngSize, const int numFrames, const bool stripIsHorizontal, int index);
        
    void paint(Graphics& g) override;
    
    int getFrameWidth();
    
    int getFrameHeight();
    
private:
    Image filmStrip;
    const int numFrames_;
    const bool isHorizontal_;
    int frameWidth, frameHeight;
};
