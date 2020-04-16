/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
SamplifiedEditor::SamplifiedEditor (SamplifiedPluginProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(1200, 600);
}

SamplifiedEditor::~SamplifiedEditor()
{
    processor.m_fileBrowser->removeListener(this);
}

//==============================================================================
void SamplifiedEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    
    image.setBounds(0,0,getWidth(),getHeight());
    addAndMakeVisible(image);

    addAndMakeVisible(teapot);
    teapot.setSize(300, 300);
    teapot.setTopLeftPosition(500, 0);
    addAndMakeVisible(processor.m_fileBrowser);
    processor.m_fileBrowser->setSize(300, 300);
    processor.m_fileBrowser->setTopLeftPosition(0, 0);
    processor.m_fileBrowser->addListener(this);
}

void SamplifiedEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

//==============================================================================
void SamplifiedEditor::selectionChanged ()
{
}

void SamplifiedEditor::fileClicked (const File& file, const MouseEvent& e)
{
    if(processor.m_fileBrowser->currentFileIsValid()){
        processor.loadNewSample(processor.m_fileBrowser->getSelectedFile(0));
    }
          
    //    auto* reader = formatManager.createReaderFor (file);
    //
    //    if (reader != nullptr)
    //    {
    //        std::unique_ptr<AudioFormatReaderSource> newSource (new AudioFormatReaderSource (reader, true));
    //        transportSource.setSource (newSource.get(), 0, nullptr, reader->sampleRate);
    //        readerSource.reset (newSource.release());
    //    }
}

void SamplifiedEditor::fileDoubleClicked (const File& file)
{
}

void SamplifiedEditor::browserRootChanged (const File& newRoot)
{
}
