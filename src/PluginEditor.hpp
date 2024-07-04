#pragma once

#include "PluginProcessor.hpp"

#include <functional>

//==============================================================================
class AudioPluginAudioProcessorEditor : public juce::AudioProcessorEditor {
public:
  using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

  AudioPluginAudioProcessorEditor(juce::AudioProcessor &processor,
                                  juce::AudioProcessorValueTreeState &state);
  ~AudioPluginAudioProcessorEditor() override;

  //==============================================================================
  void paint(juce::Graphics &) override;
  void resized() override;

private:
  std::reference_wrapper<juce::AudioProcessorValueTreeState> m_valueTreeState;
  juce::Slider m_wetSlider;
  juce::Slider m_volumeSlider;
  juce::Label m_wetLabel;
  juce::Label m_volumeLabel;
  std::unique_ptr<SliderAttachment> m_wetAttachment;
  std::unique_ptr<SliderAttachment> m_volumeAttachment;
};
