#pragma once

#include "DecibelSlider.hpp"
#include "PluginProcessor.hpp"

#include <functional>

//==============================================================================
class AudioPluginAudioProcessorEditor : public juce::AudioProcessorEditor,
                                        public juce::Timer,
                                        public juce::Slider::Listener {
public:
  explicit AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor &);
  ~AudioPluginAudioProcessorEditor() override;

  //==============================================================================
  void paint(juce::Graphics &) override;
  void resized() override;
  void timerCallback() override {}
  void sliderValueChanged(juce::Slider *slider) override;

private:
  // This reference is provided as a quick way for your editor to
  // access the processor object that created it.
  std::reference_wrapper<AudioPluginAudioProcessor> m_processor;
  juce::Slider m_wetSlider;
  juce::Slider m_volumeSlider;
  juce::Label m_wetLabel;
  juce::Label m_volumeLabel;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPluginAudioProcessorEditor)
};
