/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "WavefrontObjFile.h"
#include "TeapotComponent.h"


//class OtherLookAndFeel : public LookAndFeel_V4
//{
//public:
//    OtherLookAndFeel()
//    {
//        setColour (Slider::thumbColourId, Colours::red);
//    }
//
//    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
//                       const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
//    {
//        teapotComponent.render();
        
//        auto radius = jmin (width / 2, height / 2) - 4.0f;
//        auto centreX = x + width  * 0.5f;
//        auto centreY = y + height * 0.5f;
//        auto rx = centreX - radius;
//        auto ry = centreY - radius;
//        auto rw = radius * 2.0f;
//        auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
//
//        // fill
//        g.setColour (Colours::orange);
//        g.fillEllipse (rx, ry, rw, rw);
//
//        // outline
//        g.setColour (Colours::red);
//        g.drawEllipse (rx, ry, rw, rw, 1.0f);
//
//        Path p;
//        auto pointerLength = radius * 0.33f;
//        auto pointerThickness = 2.0f;
//        p.addRectangle (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
//        p.applyTransform (AffineTransform::rotation (angle).translated (centreX, centreY));
//
//        // pointer
//        g.setColour (Colours::yellow);
//        g.fillPath (p);
//    }
//private:
//    TeapotComponent teapotComponent;
//};

class GlSlider  : public Slider
{
   void paint (Graphics& g, LookAndFeel& lf)
    {
        addAndMakeVisible (teapotComponent);
    }
    
private:
    TeapotComponent teapotComponent;
};

//==============================================================================
class TeapotWrapperComponent    : public Component
{
public:
    TeapotWrapperComponent()
    {
        dial1.GlSlider::setSliderStyle (GlSlider::Rotary);
        dial1.GlSlider::setTextBoxStyle (GlSlider ::NoTextBox, false, 0, 0);
        addAndMakeVisible (dial1);
        
        
    
        
    }

    void paint (Graphics& g) override
    {
    }

    void resized() override
    {
        //teapotComponent.setBounds(0,0,getWidth(),getHeight());
        dial1.setBounds(0,0,getWidth(),getHeight());
    }

private:
    //OtherLookAndFeel otherLookAndFeel;
    GlSlider dial1;
    TeapotComponent teapotComponent;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TeapotWrapperComponent)
};

//==============================================================================
class ImageBackgroundComponent    : public Component
{
public:
    ImageBackgroundComponent()
    {
        
    }

    void paint (Graphics& g) override
    {
        Image background = ImageCache::getFromMemory (BinaryData::SimplifierBackground_jpeg, (size_t) BinaryData::SimplifierBackground_jpegSize);
        g.drawImageWithin (background, 0, 0, getWidth(),getHeight(),RectanglePlacement::onlyReduceInSize,false);
    }

    void resized() override
    {
    }

private:

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ImageBackgroundComponent)
};

class SamplifiedEditor  : public AudioProcessorEditor, public FileBrowserListener
{
public:
    SamplifiedEditor (SamplifiedPluginProcessor&);
    ~SamplifiedEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    //==============================================================================
    void selectionChanged () override;
    void fileClicked (const File& file, const MouseEvent& e) override;
    void fileDoubleClicked (const File& file) override;
    void browserRootChanged (const File& newRoot) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SamplifiedPluginProcessor& processor;
    
    //==============================================================================
    AudioFormatManager formatManager;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource;
    
    ScopedPointer<TeapotComponent> glComponent;
    TeapotWrapperComponent teapot;
    ImageBackgroundComponent image;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SamplifiedEditor)
};
