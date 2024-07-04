#include "PluginEditor.hpp"
#include "PluginProcessor.hpp"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(
    juce::AudioProcessor &processor, juce::AudioProcessorValueTreeState &state)
    : AudioProcessorEditor(processor), m_valueTreeState(state) {
  m_wetLabel.setText("Wet/Dry Mix", juce::dontSendNotification);
  m_wetLabel.attachToComponent(&m_wetSlider, juce::dontSendNotification);
  addAndMakeVisible(m_wetLabel);
  m_volumeLabel.setText("Volume", juce::dontSendNotification);
  m_volumeLabel.attachToComponent(&m_volumeSlider, juce::dontSendNotification);
  addAndMakeVisible(m_volumeLabel);

  m_wetSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
  m_wetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 75, 25);
  m_wetSlider.setTextValueSuffix("%");
  m_wetSlider.setBounds(0, 25, 200, 200);
  addAndMakeVisible(m_wetSlider);
  m_wetAttachment.reset(
      new SliderAttachment(m_valueTreeState, "wetMix", m_wetSlider));

  m_volumeSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
  m_volumeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 75, 25);
  m_volumeSlider.setTextValueSuffix("%");
  m_volumeSlider.setBounds(200, 25, 200, 200);
  addAndMakeVisible(m_volumeSlider);
  m_volumeAttachment.reset(
      new SliderAttachment(m_valueTreeState, "volume", m_volumeSlider));

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
