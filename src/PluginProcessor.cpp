#include "PluginProcessor.hpp"
#include "PluginEditor.hpp"

//==============================================================================
HardClipProcessor::HardClipProcessor()
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

bool HardClipProcessor::isBusesLayoutSupported(
    const BusesLayout &layouts) const {
  return layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet();
}

void HardClipProcessor::processBlock(juce::AudioBuffer<float> &buffer,
                                     juce::MidiBuffer &) {
  auto percentWet = m_percentWet.get().load() / 100;
  auto linearVolumeScale = m_linearVolumeScale.get().load() / 100;

  for (int i = 0; i < buffer.getNumChannels(); i++) {
    auto *channelRead = buffer.getReadPointer(i);
    auto *channelWrite = buffer.getWritePointer(i);

    for (int j = 0; j < buffer.getNumSamples(); j++) {
      auto value = channelRead[j];
      channelWrite[j] = value == 0 ? 0 : value > 0 ? percentWet : -percentWet;
      channelWrite[j] += value * (1.f - percentWet);
      channelWrite[j] *= linearVolumeScale;
    }
  }
}

juce::AudioProcessorEditor *HardClipProcessor::createEditor() {
  return new HardClipEditor(*this, m_state);
}

void HardClipProcessor::getStateInformation(juce::MemoryBlock &destData) {
  auto state = m_state.copyState();
  auto xml = state.createXml();
  copyXmlToBinary(*xml, destData);
}

void HardClipProcessor::setStateInformation(const void *data, int sizeInBytes) {
  auto xmlState = getXmlFromBinary(data, sizeInBytes);

  if (xmlState.get() != nullptr &&
      xmlState->hasTagName(m_state.state.getType())) {
    m_state.replaceState(juce::ValueTree::fromXml(*xmlState));
  }
}

juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter() {
  return new HardClipProcessor();
}
