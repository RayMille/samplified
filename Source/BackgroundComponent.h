/*
  ==============================================================================

    BackgroundComponent.h
    Created: 9 Apr 2020 7:09:00pm
    Author:  Johannes Koenders

  ==============================================================================
*/

#pragma once

//==============================================================================
class BackgroundComponent    : public Component
{
public:
    BackgroundComponent()
    {

    }

    void paint (Graphics& g) override
    {
        Image background = ImageCache::getFromMemory (BinaryData::BACKGROUND15_png, (size_t) BinaryData::BACKGROUND15_pngSize);
        g.drawImageWithin (background, 0, 0, getWidth(),getHeight(),RectanglePlacement::onlyReduceInSize,false);
    }

    void resized() override
    {
    }

private:

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BackgroundComponent)
};
