/*
 ==============================================================================
 
 FileWindowComponent.h
 Created: 2 May 2020 8:55:13am
 Author:  Camille Koenders
 
 ==============================================================================
 */

#pragma once

//==============================================================================
class FileWindowComponent    : public Component
{
public:
    FileWindowComponent()
    {
        
    }
    
    void paint (Graphics& g) override
    {
        int w = getWidth();
        int h = getHeight();
        int x = 0;
        int y = 0;
        
        Rectangle<float> windowTop (x, y, w, h/2);
        ColourGradient cgTop = ColourGradient::vertical(Colours::black.withAlpha(1.0f), y, Colours::black.withAlpha(0.0f), y+(h/2-5) );
        g.setGradientFill(cgTop);
        g.fillRect(windowTop);
        
        Rectangle<float> windowBottom (x, y+h/2, w, h/2);
        ColourGradient cgBottom = ColourGradient::vertical(Colours::black.withAlpha(0.0f), y+(h/2+5), Colours::black.withAlpha(1.0f), y+h);
        g.setGradientFill(cgBottom);
        g.fillRect(windowBottom);
    }
    
    void resized() override
    {
    }
    
private:
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FileWindowComponent)
};
