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
    
    ADSR::Parameters& getADSRParams() {return mADSRParams;}
    AudioProcessorValueTreeState& getAPVTS() { return mAPVTS; }
    
    //==============================================================================
    FileBrowserComponent* m_fileBrowser;

    //==============================================================================
    void loadNewSample(const File& sampleFile);

private:
    Synthesiser mSampler;
    const int mNumVoices { 32 };
    AudioBuffer<float> mWaveForm;
    
    ADSR::Parameters mADSRParams;
    
    AudioFormatManager mFormatManager;
    AudioFormatReader* mFormatReader { nullptr };
    
    AudioProcessorValueTreeState mAPVTS;
    AudioProcessorValueTreeState::ParameterLayout createParameters();
    void valueTreePropertyChanged (ValueTree& treeWhosePropertyHasChanged, const Identifier& property) override;
    
    std::atomic<bool> mShouldUpdate { false };
    
    //==========================Directory Component Stuff===========================
    OwnedArray<Synthesiser> synth;
    SynthesiserSound::Ptr sound;
    
    //==============================================================================
    File fileFolder;
    WildcardFileFilter* m_wcFileFilter;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SamplifiedAudioProcessor)
};
