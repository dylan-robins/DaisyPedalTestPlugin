/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include "daisysp.h"
using namespace daisysp;

//==============================================================================
DaisySeedEmuAudioProcessor::DaisySeedEmuAudioProcessor()
    : AudioProcessor(BusesProperties()
                         .withInput("Input", juce::AudioChannelSet::stereo(), true)
                         .withOutput("Output", juce::AudioChannelSet::stereo(), true)
      )
{
    for (int channel = 0; channel < getTotalNumInputChannels(); ++channel) {
        lp_filter[channel].Init(getSampleRate());
        lp_filter[channel].SetFreq(1000);
        lp_filter[channel].SetRes(0);
        lp_filter[channel].SetDrive(0);
    }
}

DaisySeedEmuAudioProcessor::~DaisySeedEmuAudioProcessor() {
}

//==============================================================================
const juce::String DaisySeedEmuAudioProcessor::getName() const {
    return "DaisySeedEmu";
}

bool DaisySeedEmuAudioProcessor::acceptsMidi() const {
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool DaisySeedEmuAudioProcessor::producesMidi() const {
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool DaisySeedEmuAudioProcessor::isMidiEffect() const {
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double DaisySeedEmuAudioProcessor::getTailLengthSeconds() const {
    return 0.0;
}

int DaisySeedEmuAudioProcessor::getNumPrograms() {
    return 1; // NB: some hosts don't cope very well if you tell them there are 0 programs,
              // so this should be at least 1, even if you're not really implementing programs.
}

int DaisySeedEmuAudioProcessor::getCurrentProgram() {
    return 0;
}

void DaisySeedEmuAudioProcessor::setCurrentProgram(int index) {
}

const juce::String DaisySeedEmuAudioProcessor::getProgramName(int index) {
    return {};
}

void DaisySeedEmuAudioProcessor::changeProgramName(int index, const juce::String &newName) {
}

//==============================================================================
void DaisySeedEmuAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    for (int channel = 0; channel < getTotalNumInputChannels(); ++channel) {
        lp_filter[channel].Init(sampleRate);
    }
}

void DaisySeedEmuAudioProcessor::releaseResources() {
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DaisySeedEmuAudioProcessor::isBusesLayoutSupported(const BusesLayout &layouts) const {
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused(layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono() && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

        // This checks if the input layout matches the output layout
#if !JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}
#endif

void DaisySeedEmuAudioProcessor::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages) {
    juce::ScopedNoDenormals noDenormals;

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < getTotalNumInputChannels(); ++channel) {
        float *channelData = buffer.getWritePointer(channel);
        for (int sample = 0; sample < buffer.getNumSamples(); sample++) {
            lp_filter[channel].Process(channelData[sample]);
            channelData[sample] = volume * lp_filter[channel].Low();
        }
    }
}

//==============================================================================
bool DaisySeedEmuAudioProcessor::hasEditor() const {
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor *DaisySeedEmuAudioProcessor::createEditor() {
    return new DaisySeedEmuAudioProcessorEditor(*this);
}

//==============================================================================
void DaisySeedEmuAudioProcessor::getStateInformation(juce::MemoryBlock &destData) {
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void DaisySeedEmuAudioProcessor::setStateInformation(const void *data, int sizeInBytes) {
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void DaisySeedEmuAudioProcessor::setParams(float vol, float freq, float drive, float res) {
    volume = vol;
    for (int channel = 0; channel < getTotalNumInputChannels(); ++channel) {
        lp_filter[channel].SetFreq(freq);
        lp_filter[channel].SetRes(res);
        lp_filter[channel].SetDrive(drive);
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter() {
    return new DaisySeedEmuAudioProcessor();
}
