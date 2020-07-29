/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SamplifiedAudioProcessor::SamplifiedAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ), mAPVTS(*this, nullptr, "PARAMETERS", createParameters() )
#endif
{
    LookAndFeel::setDefaultLookAndFeel(&samplifiedLookAndFeel);
    LookAndFeel::getDefaultLookAndFeel().setDefaultSansSerifTypefaceName(SamplifiedLookAndFeel::getCoolvetica().getTypefaceName());
     
    mFormatManager.registerBasicFormats();
    mAPVTS.state.addListener (this);

    for (int i = 0; i < mNumVoices; i++)
    {
        mSampler.addVoice (new SamplerVoice());
    }
}

SamplifiedAudioProcessor::~SamplifiedAudioProcessor()
{
    mFormatReader = nullptr;
}

//==============================================================================
const String SamplifiedAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SamplifiedAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SamplifiedAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SamplifiedAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SamplifiedAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SamplifiedAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SamplifiedAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SamplifiedAudioProcessor::setCurrentProgram (int index)
{
}

const String SamplifiedAudioProcessor::getProgramName (int index)
{
    return {};
}

void SamplifiedAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void SamplifiedAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    updateVoices();
    mSampler.setCurrentPlaybackSampleRate (sampleRate);
    updateADSRV();
}

void SamplifiedAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SamplifiedAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SamplifiedAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    if (mSouldUpdateVoices)
    {
        updateVoices();
        mSouldUpdateVoices = false;
    }

    if (mShouldUpdate)
    {
       updateADSRV();
    }

    MidiMessage m;
    MidiBuffer::Iterator it { midiMessages };
    int sample;

    output.clear();

    while (it.getNextEvent(m, sample))
    {
        if (m.isNoteOn()){
            mIsNotePlayed = true;
            
            uint8 newVel = (uint8) volumeVal;
            m.setNoteNumber(m.getNoteNumber()+transpositionAmount);
            m = MidiMessage::noteOn(m.getChannel(), m.getNoteNumber(), newVel);

        }else if (m.isNoteOff()){
            m.setNoteNumber(m.getNoteNumber()+transpositionAmount);
            mIsNotePlayed = false;
        }
       
        if(m.isController()){
            if(m.getControllerValue() == 11)
            {
                panPosition = (int) m.getControllerValue();
            }
        }

        output.addEvent(m, sample);
    }

    if(output.isEmpty()){
          output = midiMessages;
    }
    
    

    mSampleCount = mIsNotePlayed ? mSampleCount += buffer.getNumSamples() : 0;

    mSampler.renderNextBlock (buffer, output, 0, buffer.getNumSamples());

}

//==============================================================================
bool SamplifiedAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SamplifiedAudioProcessor::createEditor()
{
    return new SamplifiedAudioProcessorEditor (*this);
}

//==============================================================================
void SamplifiedAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SamplifiedAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void SamplifiedAudioProcessor::LoadFile()
{
    mSampler.clearSounds();

    FileChooser chooser { "Please load file" };

    if (chooser.browseForFileToOpen())
    {
        auto file = chooser.getResult();
        mFormatReader = mFormatManager.createReaderFor (file);
    }

    BigInteger range;
    range.setRange(0, 128, true);

    mSampler.addSound (new SamplerSound ("Sample", *mFormatReader, range, 60, 0.1, 0.1, 10.0));

}

void SamplifiedAudioProcessor::LoadFile (const String& path)
{
    mSampler.clearSounds();
    
    
    auto file = File (path);
    mFormatReader = mFormatManager.createReaderFor (file);

    

    auto sampleLength = static_cast<int>(mFormatReader->lengthInSamples);

    mWaveForm.setSize(1, sampleLength);
    mDuration = (float) mFormatReader->lengthInSamples / mFormatReader->sampleRate;
    mFormatReader ->read (&mWaveForm, 0, sampleLength, 0, true, false);

    BigInteger range;
    range.setRange(0, 128, true);

    updateVoices();
    mSampler.addSound (new SamplerSound ("Sample", *mFormatReader, range, 60, 0.1, 0.1, 10.0));

    updateADSRV();
}


void SamplifiedAudioProcessor::LoadFile (const File& file)
{
    mSampler.clearSounds();
    updateVoices();
    
    
    mFormatReader = mFormatManager.createReaderFor (file);

    auto sampleLength = static_cast<int>(mFormatReader->lengthInSamples);

    mWaveForm.setSize(1, sampleLength);
    mFormatReader ->read (&mWaveForm, 0, sampleLength, 0, true, false);
    mDuration = (float) mFormatReader->lengthInSamples / mFormatReader->sampleRate;

    BigInteger range;
    range.setRange(0, 128, true);

    mSampler.addSound (new SamplerSound ("Sample", *mFormatReader, range, 60, 0.1, 0.1, 10.0));


    updateWaveThumbnail();
    updateADSRV();
}

void SamplifiedAudioProcessor::updateADSRV()
{
    mADSRParams.attack = mAPVTS.getRawParameterValue ("ATTACK")->load();
    mADSRParams.decay = mAPVTS.getRawParameterValue ("DECAY")->load();
    mADSRParams.sustain = mAPVTS.getRawParameterValue ("SUSTAIN")->load();
    mADSRParams.release = mAPVTS.getRawParameterValue ("RELEASE")->load();
    volumeVal = mAPVTS.getRawParameterValue ("VOLUME")->load();

    for (int i = 0; i < mSampler.getNumSounds(); ++i)
    {
        if (auto sound = dynamic_cast<SamplerSound*>(mSampler.getSound(i).get()))
        {
            sound->setEnvelopeParameters(mADSRParams);
        }
    }
}

void SamplifiedAudioProcessor::updateVoices()
{
    auto slicerVoiceValue = mAPVTS.getRawParameterValue ("VOICES")->load();
    auto slicerTranspValue = mAPVTS.getRawParameterValue ("TRANSP")->load();
    auto slicerFineValue = mAPVTS.getRawParameterValue ("FINE")->load();

    transpositionAmount = slicerTranspValue + slicerFineValue;

    mSampler.clearVoices();
    for (int i = 0; i < slicerVoiceValue; i++)
    {
        mSampler.addVoice (new SamplerVoice());
    }

}

void SamplifiedAudioProcessor::updateWaveThumbnail()
{
}

AudioProcessorValueTreeState::ParameterLayout SamplifiedAudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<RangedAudioParameter>> parameters;

    parameters.push_back (std::make_unique<AudioParameterFloat>("ATTACK", "Attack", 0.0f, 5.0f, 0.8f));
    parameters.push_back (std::make_unique<AudioParameterFloat>("DECAY", "Decay", 0.0f, 3.0f, 0.5f));
    parameters.push_back (std::make_unique<AudioParameterFloat>("SUSTAIN", "Sustain", 0.0f, 1.0f, 0.7f));
    parameters.push_back (std::make_unique<AudioParameterFloat>("RELEASE", "Release", 0.0f, 5.0f, 0.5f));
    parameters.push_back(std::make_unique<AudioParameterInt>("VOICES", "Voices", 1, 32, 1));
    parameters.push_back(std::make_unique<AudioParameterInt>("TRANSP", "Transp", -24, 24, 0));
    parameters.push_back(std::make_unique<AudioParameterFloat>("FINE", "Fine", -0.50f, 0.50f, 0));
    parameters.push_back(std::make_unique<AudioParameterFloat>("VOLUME", "Volume", 0.0, 127.0, 60.0));

    return { parameters.begin(), parameters.end() };
}

void SamplifiedAudioProcessor::valueTreePropertyChanged (ValueTree& treeWhosePropertyHasChanged, const Identifier& property)
{
    mShouldUpdate = true;
    mSouldUpdateVoices = true;
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SamplifiedAudioProcessor();
}


//==============================================================================
// Loads new Sample after File Click
void SamplifiedAudioProcessor::loadNewSample (const File& sampleFile)
{
    String format = sampleFile.getFileExtension();
    mFormatReader = mFormatManager.createReaderFor (sampleFile);

    BigInteger range;
    range.setRange(0, 128, true);

    SynthesiserSound::Ptr newSound = new SamplerSound ("Voice", *mFormatReader, range, 0x40, 0.0, 0.0, 10.0);

    sound = newSound;

    mSampler.addSound (sound);

}
