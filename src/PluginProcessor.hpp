#pragma once

#include "JuceHeader.hpp"

#include <atomic>

class AudioPluginAudioProcessorEditor;

//==============================================================================
class AudioPluginAudioProcessor : public juce::AudioProcessor {
public:
  //==============================================================================
  AudioPluginAudioProcessor();
  ~AudioPluginAudioProcessor() override;

  //==============================================================================
  void prepareToPlay(double sampleRate, int samplesPerBlock) override;
  void releaseResources() override;

  bool isBusesLayoutSupported(const BusesLayout &layouts) const override;

  void processBlock(juce::AudioBuffer<float> &, juce::MidiBuffer &) override;
  using AudioProcessor::processBlock;

  //==============================================================================
  juce::AudioProcessorEditor *createEditor() override;

  bool hasEditor() const override { return true; }

  //==============================================================================
  const juce::String getName() const override { return "Hard Clip"; }

  bool acceptsMidi() const override { return false; }
  bool producesMidi() const override { return false; }
  bool isMidiEffect() const override { return false; }
  double getTailLengthSeconds() const override { return 0; }

  //==============================================================================
  int getNumPrograms() override { return 1; }
  int getCurrentProgram() override { return 0; }
  void setCurrentProgram(int) override {}
  const juce::String getProgramName(int) override { return {}; }
  void changeProgramName(int, juce::String const &) override {}

  //==============================================================================
  void getStateInformation(juce::MemoryBlock &destData) override;
  void setStateInformation(const void *data, int sizeInBytes) override;

private:
  friend class AudioPluginAudioProcessorEditor;

  juce::AudioProcessorValueTreeState m_state;
  std::reference_wrapper<std::atomic<float>> m_percentWet;
  std::reference_wrapper<std::atomic<float>> m_linearVolumeScale;

  void setWetMix(int percent);
  void setLinearVolumeScale(float value);

  //==============================================================================
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPluginAudioProcessor)
};
