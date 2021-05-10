/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include <sstream>
#include "PluginEditor.h"
#include "PluginProcessor.h"

//==============================================================================
DaisySeedEmuAudioProcessorEditor::DaisySeedEmuAudioProcessorEditor(DaisySeedEmuAudioProcessor &p)
    : AudioProcessorEditor(&p), audioProcessor(p) {
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(400, 300);

    // these define the parameters of our slider object
    audioVolume.setSliderStyle(juce::Slider::LinearBarVertical);
    audioVolume.setRange(0.0, 1.5, 0.01);
    audioVolume.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    audioVolume.setPopupDisplayEnabled(true, false, this);
    audioVolume.setTextValueSuffix(" Volume");
    audioVolume.setValue(1.0);
    // add the listener to the slider
    audioVolume.addListener(this);

    // these define the parameters of our slider object
    lowPassFreq.setSliderStyle(juce::Slider::LinearBarVertical);
    lowPassFreq.setRange(10, 22000, 1);
    lowPassFreq.setSkewFactorFromMidPoint(500);
    lowPassFreq.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    lowPassFreq.setPopupDisplayEnabled(true, false, this);
    lowPassFreq.setTextValueSuffix(" LP Freq");
    lowPassFreq.setValue(1000);
    // add the listener to the slider
    lowPassFreq.addListener(this);

    // these define the parameters of our slider object
    lowPassDrive.setSliderStyle(juce::Slider::LinearBarVertical);
    lowPassDrive.setRange(0, 10, 0.1);
    lowPassDrive.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    lowPassDrive.setPopupDisplayEnabled(true, false, this);
    lowPassDrive.setTextValueSuffix(" LP Drive");
    lowPassDrive.setValue(0);
    // add the listener to the slider
    lowPassDrive.addListener(this);

    // these define the parameters of our slider object
    lowPassRes.setSliderStyle(juce::Slider::LinearBarVertical);
    lowPassRes.setRange(0, 1, 0.01);
    lowPassRes.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    lowPassRes.setPopupDisplayEnabled(true, false, this);
    lowPassRes.setTextValueSuffix(" LP Res");
    lowPassRes.setValue(0);
    // add the listener to the slider
    lowPassRes.addListener(this);

    // this function adds the slider to the editor
    addAndMakeVisible(&audioVolume);
    addAndMakeVisible(&lowPassFreq);
    addAndMakeVisible(&lowPassDrive);
    addAndMakeVisible(&lowPassRes);
}

DaisySeedEmuAudioProcessorEditor::~DaisySeedEmuAudioProcessorEditor() {
}

//==============================================================================
void DaisySeedEmuAudioProcessorEditor::paint(juce::Graphics &g) {
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
    std::stringstream sr_txt;
    sr_txt << "sample rate: " << audioProcessor.getSampleRate();
    g.drawFittedText(sr_txt.str(), getLocalBounds(), juce::Justification::centred, 1);
}

void DaisySeedEmuAudioProcessorEditor::resized() {
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    // sets the position and size of the slider with arguments (x, y, width, height)
    audioVolume.setBounds(40, 30, 20, getHeight() - 60);
    lowPassFreq.setBounds(80, 30, 20, getHeight() - 60);
    lowPassDrive.setBounds(120, 30, 20, getHeight() - 60);
    lowPassRes.setBounds(160, 30, 20, getHeight() - 60);
}

void DaisySeedEmuAudioProcessorEditor::sliderValueChanged(juce::Slider *slider) {
    audioProcessor.setParams(
        audioVolume.getValue(),
        lowPassFreq.getValue(),
        lowPassDrive.getValue(),
        lowPassRes.getValue()
    );
}