/*
  ==============================================================================

    FilmStripKnop.cpp
    Created: 10 Jun 2020 4:04:20pm
    Author:  Camille Koenders

  ==============================================================================
*/

#include "FilmStripKnob.h"

//==============================================================================
FilmStripKnob::FilmStripKnob (const void* knob_png, const int knob_pngSize, const int numFrames, const bool stripIsHorizontal, int index):
    Slider(juce::String(index)),
    filmStrip(ImageCache::getFromMemory (knob_png, knob_pngSize)),
    numFrames_(numFrames),
    isHorizontal_(stripIsHorizontal)
{
      if (isHorizontal_) {
            frameHeight = filmStrip.getHeight();
            frameWidth = filmStrip.getWidth() / numFrames_;
      }
      else {
            frameHeight = filmStrip.getHeight() / numFrames_;
            frameWidth = filmStrip.getWidth();
      }
}
      
void FilmStripKnob::paint(Graphics& g)
{
      int value = (int)((getValue() - getMinimum()) / (getMaximum() - getMinimum()) * (numFrames_ - 1));
      if(isHorizontal_)
      {
          g.drawImage(filmStrip, 0, 0, getWidth(), getHeight(),
                      value * frameWidth, 0, frameWidth, frameHeight);
      }
      else
      {
          g.drawImage(filmStrip, 0, 0, getWidth(), getHeight(),
                      0, value * frameHeight, frameWidth, frameHeight);
      }
}
  
int FilmStripKnob::getFrameWidth() { return frameWidth; }

int FilmStripKnob::getFrameHeight() { return frameHeight; }





