#include "PluginEditor.hpp"
#include "PluginProcessor.hpp"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(
    AudioPluginAudioProcessor &p)
    : AudioProcessorEditor(&p), m_processor(p), m_wetSlider("Wet Mix"),
      m_volumeSlider("Volume"), m_wetLabel("percent label", "Wet/Dry Mix"),
      m_volumeLabel("volume label", "Volume") {

  startTimer(20);

  m_wetSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
  m_wetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 75, 25);
  m_wetSlider.setTextValueSuffix("%");
  m_wetSlider.setRange(0, 100, 1);
  m_wetSlider.setValue(100);
  m_wetSlider.setBounds(0, 25, 200, 200);
  m_wetSlider.addListener(this);
  addAndMakeVisible(m_wetSlider);

  m_wetLabel.attachToComponent(&m_wetSlider, false);
  addAndMakeVisible(m_wetLabel);

  m_volumeSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
  m_volumeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 75, 25);
  m_volumeSlider.setBounds(200, 25, 200, 200);
  m_volumeSlider.addListener(this);
  addAndMakeVisible(m_volumeSlider);

  m_volumeLabel.attachToComponent(&m_volumeSlider, false);
  addAndMakeVisible(m_volumeLabel);

  // Make sure that before the constructor has finished, you've set the
  // editor's size to whatever you need it to be.
  setSize(400, 250);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor() {}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint(juce::Graphics &g) {
  // (Our component is opaque, so we must completely fill the background with a
  // solid colour)
  g.fillAll(
      getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

  g.setColour(juce::Colours::white);
  g.setFont(15.0f);
}

void AudioPluginAudioProcessorEditor::resized() {
  // This is generally where you'll want to lay out the positions of any
  // subcomponents in your editor..
}

void AudioPluginAudioProcessorEditor::sliderValueChanged(juce::Slider *slider) {
  if (slider == &m_wetSlider) {
    m_processor.get().setWetMix(m_wetSlider.getValue());
  } else if (slider == &m_volumeSlider) {
    m_processor.get().setLinearVolumeScale(m_volumeSlider.linearGain());
  }
}