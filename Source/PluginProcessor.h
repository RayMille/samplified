/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SamplifiedLookAndFeel.h"

//==============================================================================
/**
*/
class SamplifiedAudioProcessor  : public AudioProcessor,
                               public ValueTree::Listener
{
public:
    //==============================================================================
    SamplifiedAudioProcessor();
    ~SamplifiedAudioProcessor();

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
    
    void LoadFile();
    void LoadFile (const String& path);
    void LoadFile (const File& file);
    
    int getNumSamplerSounds() {return mSampler.getNumSounds(); }
    AudioBuffer<float>& getWaveForm() {return mWaveForm; }
    
    void updateADSR();
    void updateWaveThumbnail();
    void updateVoices();
    
    ADSR::Parameters& getADSRParams() {return mADSRParams;}
    AudioProcessorValueTreeState& getAPVTS() { return mAPVTS; }
    std::atomic<bool>& isNotePlayed() { return mIsNotePlayed; }
    std::atomic<int>& getSampleCount() { return mSampleCount; }
    
    
   

    //==============================================================================
    void loadNewSample(const File& sampleFile);
    
    SamplifiedLookAndFeel samplifiedLookAndFeel;
    
    

private:
    Synthesiser mSampler;
    int mNumVoices { 1 };
    AudioBuffer<float> mWaveForm;
    
    ADSR::Parameters mADSRParams;
    
    AudioFormatManager mFormatManager;
    AudioFormatReader* mFormatReader { nullptr };
    
    AudioProcessorValueTreeState mAPVTS;
    AudioProcessorValueTreeState::ParameterLayout createParameters();
    void valueTreePropertyChanged (ValueTree& treeWhosePropertyHasChanged, const Identifier& property) override;
    
    std::atomic<bool> mShouldUpdate { false };
    std::atomic<bool> mSouldUpdateVoices { false };
    std::atomic<bool> mIsNotePlayed { false };
    std::atomic<int> mSampleCount { 0 };
    
    std::atomic<int> transpositionAmount { 0 };
    
    juce::MidiBuffer output;
    
    //==========================Directory Component Stuff===========================
    OwnedArray<Synthesiser> synth;
    SynthesiserSound::Ptr sound;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SamplifiedAudioProcessor)
};
