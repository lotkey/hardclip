#pragma once

#include "PluginProcessor.hpp"

#include <functional>

class HardClipEditor : public juce::AudioProcessorEditor {
public:
  using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

  HardClipEditor(juce::AudioProcessor &processor,
                 juce::AudioProcessorValueTreeState &state);
  ~HardClipEditor() override;

  void paint(juce::Graphics &) override;
  void resized() override;

private:
  std::reference_wrapper<juce::AudioProcessorValueTreeState> m_valueTreeState;
  juce::Slider m_wetSlider;
  juce::Slider m_volumeSlider;
  juce::Label m_wetLabel;
  juce::Label m_volumeLabel;
  SliderAttachment m_wetAttachment;
  SliderAttachment m_volumeAttachment;
};
