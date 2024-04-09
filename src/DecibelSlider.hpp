#pragma once

#include "JuceHeader.hpp"

namespace lk {
class DecibelSlider : public juce::Slider {
public:
  template <typename... Args>
  DecibelSlider(Args &&...args) : juce::Slider(std::forward<Args>(args)...) {
    setRange(-100, 0);
    setValue(-20);
  }

  juce::String getTextFromValue(double value) override {
    return juce::Decibels::toString(value);
  }

  double getValueFromText(juce::String const &text) override {
    auto decibelText = text.upToFirstOccurrenceOf("dB", false, false).trim();
    return decibelText.equalsIgnoreCase("-inf") ? MinusInfinityDB
                                                : decibelText.getDoubleValue();
  }

  float linearGain() const {
    return juce::Decibels::decibelsToGain(static_cast<float>(getValue()));
  }

private:
  static constexpr auto MinusInfinityDB = -100;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DecibelSlider)
};
} // namespace lk