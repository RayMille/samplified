/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PluginSynthWithFileUploadAudioProcessor::PluginSynthWithFileUploadAudioProcessor()
//#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                    // #if ! JucePlugin_IsMidiEffect
                    //  #if ! JucePlugin_IsSynth
                     //  .withInput  ("Input",  AudioChannelSet::stereo(), true)
                    //  #endif
                        .withOutput ("Output #1",  AudioChannelSet::stereo(), true)
                        .withOutput ("Output #2",  AudioChannelSet::stereo(), false)
                        .withOutput ("Output #3",  AudioChannelSet::stereo(), false)
                        .withOutput ("Output #4",  AudioChannelSet::stereo(), false)
                        .withOutput ("Output #5",  AudioChannelSet::stereo(), false)
                        .withOutput ("Output #6",  AudioChannelSet::stereo(), false)
                        .withOutput ("Output #7",  AudioChannelSet::stereo(), false)
                        .withOutput ("Output #8",  AudioChannelSet::stereo(), false)
                        .withOutput ("Output #9",  AudioChannelSet::stereo(), false)
                        .withOutput ("Output #10", AudioChannelSet::stereo(), false)
                        .withOutput ("Output #11", AudioChannelSet::stereo(), false)
                        .withOutput ("Output #12", AudioChannelSet::stereo(), false)
                        .withOutput ("Output #13", AudioChannelSet::stereo(), false)
                        .withOutput ("Output #14", AudioChannelSet::stereo(), false)
                        .withOutput ("Output #15", AudioChannelSet::stereo(), false)
                        .withOutput ("Output #16", AudioChannelSet::stereo(), false)
                  //   #endif
                       )
//#endif
{
    
       // initialize other stuff (not related to buses)
       formatManager.registerBasicFormats();
    
       fileFolder = File::getSpecialLocation(File::userHomeDirectory);
       int flags = FileBrowserComponent::openMode |
              FileBrowserComponent::canSelectFiles | FileBrowserComponent::filenameBoxIsReadOnly;
       m_wcFileFilter = new WildcardFileFilter("*.wav", "*", "Wav files");
       m_fileBrowser = new FileBrowserComponent(flags,fileFolder,m_wcFileFilter, NULL);

       for (auto midiChannel = 0; midiChannel < maxMidiChannel; ++midiChannel)
       {
           synth.add (new Synthesiser());

           for (auto i = 0; i < maxNumberOfVoices; ++i)
               synth[midiChannel]->addVoice (new SamplerVoice());
       }
    

       auto dir = File::getSpecialLocation(File::SpecialLocationType::userHomeDirectory);

       int numTries = 0;

       while (! dir.getChildFile ("Resources").exists() && numTries++ < 15)
           dir = dir.getParentDirectory();
    
       loadNewSample (dir.getChildFile ("Resources").getChildFile ("singing.ogg"));
    
    
    
}

PluginSynthWithFileUploadAudioProcessor::~PluginSynthWithFileUploadAudioProcessor()
{
    m_fileBrowser->~FileBrowserComponent();
    delete (m_wcFileFilter);
}

//==============================================================================
const String PluginSynthWithFileUploadAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PluginSynthWithFileUploadAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PluginSynthWithFileUploadAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PluginSynthWithFileUploadAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PluginSynthWithFileUploadAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PluginSynthWithFileUploadAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PluginSynthWithFileUploadAudioProcessor::getCurrentProgram()
{
    return 0;
}

void PluginSynthWithFileUploadAudioProcessor::setCurrentProgram (int index)
{
}

const String PluginSynthWithFileUploadAudioProcessor::getProgramName (int index)
{
    return {};
}

void PluginSynthWithFileUploadAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void PluginSynthWithFileUploadAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    ignoreUnused (samplesPerBlock);

    for (auto midiChannel = 0; midiChannel < maxMidiChannel; ++midiChannel)
        synth[midiChannel]->setCurrentPlaybackSampleRate (sampleRate);
}

void PluginSynthWithFileUploadAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PluginSynthWithFileUploadAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void PluginSynthWithFileUploadAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
//    ScopedNoDenormals noDenormals;
//    auto totalNumInputChannels  = getTotalNumInputChannels();
//    auto totalNumOutputChannels = getTotalNumOutputChannels();
//
//    // In case we have more outputs than inputs, this code clears any output
//    // channels that didn't contain input data, (because these aren't
//    // guaranteed to be empty - they may contain garbage).
//    // This is here to avoid people getting screaming feedback
//    // when they first compile a plugin, but obviously you don't need to keep
//    // this code if your algorithm always overwrites all the output channels.
//    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
//        buffer.clear (i, 0, buffer.getNumSamples());
//
//    // This is the place where you'd normally do the guts of your plugin's
//    // audio processing...
//    // Make sure to reset the state if your inner loop is processing
//    // the samples and the outer loop is handling the channels.
//    // Alternatively, you can process the samples with the channels
//    // interleaved by keeping the same state.
//    for (int channel = 0; channel < totalNumInputChannels; ++channel)
//    {
//        auto* channelData = buffer.getWritePointer (channel);
//
//        // ..do something to the data...
//    }
    
    
    
    auto busCount = getBusCount (false);

    for (auto busNr = 0; busNr < busCount; ++busNr)
    {
        auto midiChannelBuffer = filterMidiMessagesForChannel (midiMessages, busNr + 1);
        auto audioBusBuffer = getBusBuffer (buffer, false, busNr);

        synth [busNr]->renderNextBlock (audioBusBuffer, midiChannelBuffer, 0, audioBusBuffer.getNumSamples());
    }
}

//==============================================================================
bool PluginSynthWithFileUploadAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* PluginSynthWithFileUploadAudioProcessor::createEditor()
{
    return new PluginSynthWithFileUploadAudioProcessorEditor (*this);
}

//==============================================================================
void PluginSynthWithFileUploadAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void PluginSynthWithFileUploadAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginSynthWithFileUploadAudioProcessor();
}

//==============================================================================
MidiBuffer PluginSynthWithFileUploadAudioProcessor::filterMidiMessagesForChannel (const MidiBuffer& input, int channel)
{
    MidiMessage msg;
    int samplePosition;
    MidiBuffer output;

    for (MidiBuffer::Iterator it (input); it.getNextEvent (msg, samplePosition);)
        if (msg.getChannel() == channel) output.addEvent (msg, samplePosition);

    return output;
}

void PluginSynthWithFileUploadAudioProcessor::loadNewSample (const File& sampleFile)
   {
       auto* soundBuffer = sampleFile.createInputStream();
       String format = sampleFile.getFileExtension();
       std::unique_ptr<AudioFormatReader> formatReader (formatManager.findFormatForFileExtension (format )->createReaderFor (soundBuffer, true));

       BigInteger midiNotes;
       midiNotes.setRange (0, 126, true);
       SynthesiserSound::Ptr newSound = new SamplerSound ("Voice", *formatReader, midiNotes, 0x40, 0.0, 0.0, 10.0);

       for (auto channel = 0; channel < maxMidiChannel; ++channel)
           synth[channel]->removeSound (0);

       sound = newSound;

       for (auto channel = 0; channel < maxMidiChannel; ++channel)
           synth[channel]->addSound (sound);
   }
