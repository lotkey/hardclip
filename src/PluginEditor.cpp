#include "PluginEditor.hpp"
#include "PluginProcessor.hpp"

HardClipEditor::HardClipEditor(juce::AudioProcessor &processor,
                               juce::AudioProcessorValueTreeState &state)
    : AudioProcessorEditor(processor), m_valueTreeState(state),
      m_wetSlider(juce::Slider::SliderStyle::Rotary,
                  juce::Slider::TextBoxBelow),
      m_volumeSlider(juce::Slider::SliderStyle::Rotary,
                     juce::Slider::TextBoxBelow),
      m_wetLabel("Wet/Dry Mix"), m_volumeLabel("Volume"),
      m_wetAttachment(m_valueTreeState, "wetMix", m_wetSlider),
      m_volumeAttachment(m_valueTreeState, "volume", m_volumeSlider) {

  m_wetLabel.attachToComponent(&m_wetSlider, juce::dontSendNotification);
  addAndMakeVisible(m_wetLabel);

  m_volumeLabel.attachToComponent(&m_volumeSlider, juce::dontSendNotification);
  addAndMakeVisible(m_volumeLabel);

  m_wetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 75, 25);
  m_wetSlider.setTextValueSuffix("%");
  m_wetSlider.setBounds(0, 25, 200, 200);
  addAndMakeVisible(m_wetSlider);

  m_volumeSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
  m_volumeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 75, 25);
  m_volumeSlider.setTextValueSuffix("%");
  m_volumeSlider.setBounds(200, 25, 200, 200);
  addAndMakeVisible(m_volumeSlider);

  setSize(400, 250);
}

HardClipEditor::~HardClipEditor() {}

void HardClipEditor::paint(juce::Graphics &g) {
  g.fillAll(
      getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

  g.setColour(juce::Colours::white);
  g.setFont(15.0f);
}

void HardClipEditor::resized() {}
