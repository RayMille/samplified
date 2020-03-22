/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PluginSynthWithFileUploadAudioProcessorEditor::PluginSynthWithFileUploadAudioProcessorEditor (PluginSynthWithFileUploadAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 600);
}

PluginSynthWithFileUploadAudioProcessorEditor::~PluginSynthWithFileUploadAudioProcessorEditor()
{
    processor.m_fileBrowser->removeListener(this);
}

//==============================================================================
void PluginSynthWithFileUploadAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    
    addAndMakeVisible(processor.m_fileBrowser);
    processor.m_fileBrowser->setTopLeftPosition(150, 150);
    processor.m_fileBrowser->setSize(300, 300);
    processor.m_fileBrowser->addListener(this);
}

void PluginSynthWithFileUploadAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

//==============================================================================
void PluginSynthWithFileUploadAudioProcessorEditor::selectionChanged ()
{
}

void PluginSynthWithFileUploadAudioProcessorEditor::fileClicked (const File& file, const MouseEvent& e)
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

void PluginSynthWithFileUploadAudioProcessorEditor::fileDoubleClicked (const File& file)
{
}

void PluginSynthWithFileUploadAudioProcessorEditor::browserRootChanged (const File& newRoot)
{
}
