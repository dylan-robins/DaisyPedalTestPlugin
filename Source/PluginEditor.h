/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "PluginProcessor.h"
#include <JuceHeader.h>

//==============================================================================
/**
*/
class DaisySeedEmuAudioProcessorEditor : public juce::AudioProcessorEditor,
                                         private juce::Slider::Listener {
  public:
    DaisySeedEmuAudioProcessorEditor(DaisySeedEmuAudioProcessor &);
    ~DaisySeedEmuAudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics &) override;
    void resized() override;

  private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DaisySeedEmuAudioProcessor &audioProcessor;
    juce::Slider audioVolume;
    juce::Slider lowPassFreq;
    juce::Slider lowPassDrive;
    juce::Slider lowPassRes;
    juce::Label  samplerate;
    void sliderValueChanged (juce::Slider* slider) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DaisySeedEmuAudioProcessorEditor)
};
