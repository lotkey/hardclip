#pragma once

#include "PluginProcessor.hpp"

#include <functional>

//==============================================================================
class AudioPluginAudioProcessorEditor : public juce::AudioProcessorEditor,
                                        public juce::Timer {
public:
  explicit AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor &);
  ~AudioPluginAudioProcessorEditor() override;

  //==============================================================================
  void paint(juce::Graphics &) override;
  void resized() override;
  void timerCallback() override;

private:
  // This reference is provided as a quick way for your editor to
  // access the processor object that created it.
  std::reference_wrapper<AudioPluginAudioProcessor> m_processor;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPluginAudioProcessorEditor)
};
