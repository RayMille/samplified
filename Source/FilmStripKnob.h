/*
  ==============================================================================

    FilmStripKnob.h
    Created: 4 May 2020 9:23:16pm
    Author:  Johannes Koenders

  ==============================================================================
*/

#pragma once

class FilmStripKnob : public Slider
{
public:
    FilmStripKnob(Image image, const int numFrames, const bool stripIsHorizontal, int index)
    : Slider(juce::String(index)),
    filmStrip(Image = ImageCache::getFromMemory (BinaryData::2_png, (size_t) BinaryData::2_pngSize);),
    numFrames_(136),
    isVertical_(stripIsVertical)
    {
        setTextBoxStyle(NoTextBox, 0, 0, 0);
        setSliderStyle(RotaryVerticalDrag);
        frameHeight = filmStrip.getHeight() / numFrames_;
        frameWidth = filmStrip.getWidth();
        setRange(0.0f, 1.0f, 0.001f);
        
        getProperties().set(Identifier("index"), index);
    }
    
    void paint(Graphics& g) override
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
    
private:
    Image filmStrip;
    const int numFrames_;
    const bool isVertical_;
    int frameWidth, frameHeight;
};
