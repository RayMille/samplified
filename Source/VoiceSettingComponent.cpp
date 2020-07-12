/*
  ==============================================================================

    VoiceSettingComponent.cpp
    Created: 6 May 2020 5:01:08pm
    Author:  Camille Koenders

  ==============================================================================
*/

#include <JuceHeader.h>
#include "VoiceSettingComponent.h"

//==============================================================================
VoiceSettingComponent::VoiceSettingComponent (SamplifiedAudioProcessor& p) : processor (p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addAndMakeVisible(fileLabel);
    addAndMakeVisible(voiceLabel);
    addAndMakeVisible(voiceInput);
    addAndMakeVisible(transpLabel);
    addAndMakeVisible(transpInput);
    addAndMakeVisible(fineLabel);
    addAndMakeVisible(fineInput);

}

VoiceSettingComponent::~VoiceSettingComponent()
{
}

static std::unique_ptr<Drawable> createDrawableFromSVG (const char* data)
{
    auto xml = parseXML (data);
    jassert (xml != nullptr);
    return Drawable::createFromSVG (*xml);
}

const Drawable* VoiceSettingComponent::getDefaultDocumentFileImage()
{
    if (documentImage == nullptr)
        documentImage = createDrawableFromSVG (R"svgdata(
                                               <svg id="Layer_1" data-name="Layer 1" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 105.81 85.88"><defs><style>.cls-1{fill:#ffa300;}</style></defs><path class="cls-1" d="M2.42,47c4,0,8.69.8,12.53-.23,2.56-.68,3.62-2.44,4.52-4.75.82-2.1,2.65-5.5,2.66-7.71,0-.24.4-.74.32-1-.29-.84-2.51-.83-2.85,0-.14.34.4,1.42.51,1.78l2.13,7.54L25.72,55c.64,2.28,4.29,2.49,4.82,0L38,19.72H33.19L44.22,68c.68,3,4.6,1.93,4.91-.67L56.92,2.43,52,3.1l11.1,81c.33,2.4,4.47,2.38,4.82,0l9.69-66.49H72.8L85.27,58.37c.57,1.87,3.64,2.67,4.57.6,1.39-3.1,2.48-6.8,4.32-9.63,2.09-3.2,5.7-2.28,9.24-2.28,3.22,0,3.22-5,0-5-4.4,0-10-1-12.75,3.18-2.21,3.32-3.49,7.56-5.13,11.2l4.57.6L77.62,16.27c-.66-2.15-4.45-2.59-4.82,0L63.11,82.76h4.82L56.83,1.81c-.42-3-4.61-1.86-4.91.66L44.13,67.4,49,66.74,38,18.39c-.54-2.36-4.32-2.41-4.83,0L25.72,53.71h4.82L26.79,40.45c-.78-2.73-1.38-9.81-4.7-11-4.88-1.68-6,7.53-7.1,10.24S12.82,42,10,42H2.42c-3.21,0-3.22,5,0,5Z" transform="translate(-0.01 -0.02)"/></svg>
                                               //<svg xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" xmlns:dc="http://purl.org/dc/elements/1.1/" xmlns:cc="http://web.resource.org/cc/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#" xmlns:sodipodi="http://sodipodi.sourceforge.net/DTD/sodipodi-0.dtd" xmlns:inkscape="http://www.inkscape.org/namespaces/inkscape" version="1.1" baseProfile="full" width="480px" height="360px" viewBox="0 0 480 360" preserveAspectRatio="xMidYMid meet" id="svg_document" style="zoom: 1;"><!-- Created with macSVG - https://macsvg.org/ - https://github.com/dsward2/macsvg/ --><title id="svg_document_title">Untitled.svg</title><defs id="svg_document_defs"></defs><g id="main_group"></g><path stroke="#a40006" id="path2" stroke-width="10px" d="M187,180 C187,58 204,321 207,204 C210,87 214,270 224,194 C234,118 240,150 240,205 C240,260 257,166 257,166 " fill="none" transform=""></path></svg>
                                               )svgdata");

    return documentImage.get();
}





// This function draws the wave in the screen
void VoiceSettingComponent::paint (Graphics& g)
{
    
    float widthIcon = getWidth()/8;
    float heightIcon = getWidth()/8;
    float fileLableTopMargin = getHeight()/12;
    float fileLableHeight = getHeight()/6;
    float otherLableSideMargin = getWidth()/5;
    float otherLableSideMarginLeft = getWidth()/4;
    float otherLableHeight = (getHeight()-fileLableTopMargin*3-fileLableHeight-heightIcon)/3;
    auto area = getLocalBounds();
    
    auto leftColoumn = getLocalBounds();
    leftColoumn.removeFromRight(getWidth()/2);
    leftColoumn.removeFromLeft(otherLableSideMarginLeft);
    leftColoumn.removeFromTop(fileLableHeight + 1.5*fileLableTopMargin);
    
    auto rightColoumn = getLocalBounds();
    rightColoumn.removeFromLeft(getWidth()/2);
    rightColoumn.removeFromRight(otherLableSideMargin);
    rightColoumn.removeFromTop(fileLableHeight + 1.5*fileLableTopMargin);
    
    //-----------Nicht rauslöschen für Layouten -------///
    //g.fillAll(Colours::red.withAlpha(0.2f));
    
    fileLabel.setColour (Label::textColourId, Colour (102,102,102));
    fileLabel.setJustificationType (Justification::centred);
    fileLabel.setText(this->fileName, dontSendNotification);

    
    voiceInput.setSliderStyle(juce::Slider::LinearBarVertical);
    voiceInput.setRange(1, 32,1);
    voiceInput.setTextBoxStyle (Slider::TextBoxLeft, false, 1, otherLableHeight);
    
    voiceLabel.setColour (Label::textColourId, Colour (102,102,102));
    voiceLabel.setJustificationType (Justification::left);
    voiceLabel.setText("Voices", dontSendNotification);
    
    mVoicesAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "VOICES", voiceInput);
    
    
    transpInput.setSliderStyle(juce::Slider::LinearBarVertical);
    transpInput.setRange(-24, 24, 0);
    transpInput.setTextBoxStyle (Slider::TextBoxLeft, false, 1, otherLableHeight);
    
    transpLabel.setColour (Label::textColourId, Colour (102,102,102));
    transpLabel.setJustificationType (Justification::left);
    transpLabel.setText("Transp", dontSendNotification);
    
    mTranspAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "TRANSP", transpInput);
    
    
    fineInput.setSliderStyle(juce::Slider::LinearBarVertical);
    fineInput.setRange(-0.50f, 0.50f, 0);
    fineInput.setTextValueSuffix("c");
    fineInput.setTextBoxStyle (Slider::TextBoxLeft, false, 1, otherLableHeight);
      
    fineLabel.setColour (Label::textColourId, Colour (102,102,102));
    fineLabel.setJustificationType (Justification::left);
    fineLabel.setText("Fine", dontSendNotification);
    
    mFineAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "FINE", fineInput);
    
    area.removeFromTop(fileLableTopMargin);
    fileLabel.setBounds(area.removeFromTop(fileLableHeight).reduced(20,0));
    
    voiceLabel.setBounds(leftColoumn.removeFromTop(otherLableHeight));
    ///.reduced(width reduction, height reduction)
    voiceInput.setBounds(rightColoumn.removeFromTop(otherLableHeight).reduced(7,4));
    
    transpLabel.setBounds(leftColoumn.removeFromTop(otherLableHeight));
    transpInput.setBounds(rightColoumn.removeFromTop(otherLableHeight).reduced(7,4));
    
    fineLabel.setBounds(leftColoumn.removeFromTop(otherLableHeight));
    fineInput.setBounds(rightColoumn.removeFromTop(otherLableHeight).reduced(7,4));
    
    
    auto* d = getDefaultDocumentFileImage();
    d->drawWithin (g, Rectangle<float> (getWidth()/2-widthIcon/2,getHeight()-fileLableTopMargin-heightIcon,widthIcon,heightIcon),
                       RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize, 1.0f);
    

    
}

void VoiceSettingComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void VoiceSettingComponent::setFileName(const String& name)
{
    fileName = name;
}

