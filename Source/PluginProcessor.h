/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/


class SamplifiedPluginProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    SamplifiedPluginProcessor();
    ~SamplifiedPluginProcessor();
    
    //==============================================================================
    enum
    {
        maxMidiChannel = 16,
        maxNumberOfVoices = 5
    };

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    //==============================================================================
    void loadNewSample(const File& sampleFile);
    
    //==============================================================================
    FileBrowserComponent* m_fileBrowser;

private:
    //==============================================================================
    AudioFormatManager formatManager;
    OwnedArray<Synthesiser> synth;
    SynthesiserSound::Ptr sound;
    
    static MidiBuffer filterMidiMessagesForChannel (const MidiBuffer& input, int channel);
    
    //==============================================================================
    File fileFolder;
    WildcardFileFilter* m_wcFileFilter;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SamplifiedPluginProcessor)
};
