/*
 ==============================================================================
 
 FileWindowComponent.h
 Created: 2 May 2020 8:55:13am
 Author:  Camille Koenders
 
 ==============================================================================
 */

#pragma once
#

//==============================================================================
class FileGradientComponent    : public Component
{
public:
    FileGradientComponent()
    {
        
    }
    
    void paint (Graphics& g) override
    {
        int w = getWidth();
        int h = getHeight();
        int x = 0;
        int y = 0;
        
        juce::Point<float> topLeft{0,0};
        juce::Point<float> topRight{static_cast<float>(getWidth()), 0};
        juce::Point<float> middle{static_cast<float>(getWidth()/2), static_cast<float> (getHeight()/2)};
        juce::Point<float> bottomLeft{0,static_cast<float>(getHeight())};
        juce::Point<float> bottomRight{static_cast<float>(getWidth()),static_cast<float>(getHeight())};
    
        
        Rectangle<float> windowTopLeft (x, y, w/2, h/2);
        ColourGradient cg1 = ColourGradient(Colour (21, 21, 21).withAlpha(1.0f),topLeft, Colour (28, 28, 28).withAlpha(0.0f),middle, false);
        g.setGradientFill(cg1);
        g.fillRect(windowTopLeft);
        
        Rectangle<float> windowTopRight (w/2, y, w/2, h/2);
        ColourGradient cg2 = ColourGradient(Colour (36, 36, 36).withAlpha(0.8f),topRight, Colour (28, 28, 28).withAlpha(0.0f), middle, false);
        g.setGradientFill(cg2);
        g.fillRect(windowTopRight);

        Rectangle<float> windowBottomLeft (x, h/2, w/2, h/2);
        ColourGradient cg3 = ColourGradient(Colour (17, 17, 17).withAlpha(0.0f),middle, Colour (22, 22, 22).withAlpha(1.0f), bottomLeft, false);
        g.setGradientFill(cg3);
        g.fillRect(windowBottomLeft);

        Rectangle<float> windowBottomRight (w/2, h/2, w/2, h/2);
        ColourGradient cg4 = ColourGradient(Colour (17, 17, 17).withAlpha(0.0f),middle, Colour (36, 36, 36).withAlpha(1.0f), bottomRight, false);
        g.setGradientFill(cg4);
        g.fillRect(windowBottomRight);
    }
    
    void resized() override
    {
    }
    
private:
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FileGradientComponent)
};
