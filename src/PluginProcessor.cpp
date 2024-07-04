#include "PluginProcessor.hpp"
#include "PluginEditor.hpp"

//==============================================================================
AudioPluginAudioProcessor::AudioPluginAudioProcessor()
    : AudioProcessor(
          BusesProperties()
              .withInput("Input", juce::AudioChannelSet::stereo(), true)
              .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
      m_state(*this, nullptr, juce::Identifier("Hard Clip"),
              {std::make_unique<juce::AudioParameterFloat>(
                   "wetMix", "Wet Mix",
                   juce::NormalisableRange<float>(0, 100, 1), 100),
               std::make_unique<juce::AudioParameterFloat>(
                   "volume", "Volume",
                   juce::NormalisableRange<float>(0, 100, 1), 15)}),
      m_percentWet(*m_state.getRawParameterValue("wetMix")),
      m_linearVolumeScale(*m_state.getRawParameterValue("volume")) {
  m_percentWet.get().store(100);
  m_linearVolumeScale.get().store(15);
}

AudioPluginAudioProcessor::~AudioPluginAudioProcessor() {}

void AudioPluginAudioProcessor::prepareToPlay(double sampleRate,
                                              int samplesPerBlock) {}

void AudioPluginAudioProcessor::releaseResources() {
  // When playback stops, you can use this as an opportunity to free up any
  // spare memory, etc.
}

bool AudioPluginAudioProcessor::isBusesLayoutSupported(
    const BusesLayout &layouts) const {
  // This is the place where you check if the layout is supported.
  // In this template code we only support mono or stereo.
  // Some plugin hosts, such as certain GarageBand versions, will only
  // load plugins that support stereo bus layouts.
  if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono() &&
      layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo()) {
    return false;
  }

  if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet()) {
    return false;
  }

  return true;
}

void AudioPluginAudioProcessor::processBlock(juce::AudioBuffer<float> &buffer,
                                             juce::MidiBuffer &) {
  auto percentWet = m_percentWet.get().load();
  auto linearVolumeScale = m_linearVolumeScale.get().load() / 100;

  for (int i = 0; i < buffer.getNumChannels(); i++) {
    auto *channelRead = buffer.getReadPointer(i);
    auto *channelWrite = buffer.getWritePointer(i);

    for (int j = 0; j < buffer.getNumSamples(); j++) {
      auto value = channelRead[j];
      channelWrite[j] = value == 0  ? 0
                        : value > 0 ? (percentWet / 100.f)
                                    : -(percentWet / 100.f);
      channelWrite[j] += value * (1.0 - (percentWet / 100.f));
      channelWrite[j] *= linearVolumeScale;
    }
  }
}

juce::AudioProcessorEditor *AudioPluginAudioProcessor::createEditor() {
  return new AudioPluginAudioProcessorEditor(*this, m_state);
}

void AudioPluginAudioProcessor::getStateInformation(
    juce::MemoryBlock &destData) {
  auto state = m_state.copyState();
  auto xml = state.createXml();
  copyXmlToBinary(*xml, destData);
}

void AudioPluginAudioProcessor::setStateInformation(const void *data,
                                                    int sizeInBytes) {
  auto xmlState = getXmlFromBinary(data, sizeInBytes);

  if (xmlState.get() != nullptr) {
    if (xmlState->hasTagName(m_state.state.getType())) {
      m_state.replaceState(juce::ValueTree::fromXml(*xmlState));
    }
  }
  // You should use this method to restore your parameters from this memory
  // block, whose contents will have been created by the getStateInformation()
  // call.
  juce::ignoreUnused(data, sizeInBytes);
}

void AudioPluginAudioProcessor::setWetMix(int percent) {
  // m_percentWet = percent;
}

void AudioPluginAudioProcessor::setLinearVolumeScale(float value) {
  // m_linearVolumeScale = value;
}

// This creates new instances of the plugin.
juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter() {
  return new AudioPluginAudioProcessor();
}
