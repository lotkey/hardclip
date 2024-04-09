cmake_minimum_required(VERSION 3.25)
project(pseudomin VERSION 2.0.0)
set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(BUILD ${CMAKE_CURRENT_BINARY_DIR})
set(JUCE ${CMAKE_CURRENT_SOURCE_DIR}/JUCE)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(${JUCE})

juce_add_plugin(hardclip
    FORMATS Standalone VST3
    PRODUCT_NAME "Hard Clip"
    COMPANY_NAME Lotkey                         # The name of this target's author. The value is inherited from JUCE_COMPANY_NAME.
    COMPANY_WEBSITE "https://www.synthchris.com/" # The address of a website related to this target in some way.
                                                # The value is inherited from JUCE_COMPANY_WEBSITE.
    COMPANY_EMAIL "synthchrismusic@gmail.com"   # An email address for this target's author. The value is inherited from JUCE_COMPANY_EMAIL.
    PLUGIN_MANUFACTURER_CODE Ltky               # A four-character manufacturer id with at least one upper-case character.
                                                # GarageBand 10.3 requires the first letter to be upper-case, and the remaining letters to be lower-case.
    PLUGIN_CODE Hdcl                            # A unique four-character plugin id with exactly one upper-case character.
                                                # GarageBand 10.3 requires the first letter to be upper-case, and the remaining letters to be lower-case.

    IS_SYNTH FALSE                              # Is this a synth or an effect?
    NEEDS_MIDI_INPUT FALSE                      # Does the plugin need midi input?
    NEEDS_MIDI_OUTPUT FALSE                     # Does the plugin need midi output?
    IS_MIDI_EFFECT FALSE                        # Is this plugin a MIDI effect?
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE           # Does the editor need keyboard focus?

    VST3_CATEGORIES Fx                          # Should be one or more, separated by spaces, of the following:
                                                # Fx, Instrument, Analyzer, Delay, Distortion, Drum, Dynamics, EQ, External,
                                                # Filter, Generator, Mastering, Modulation, Mono, Network, NoOfflineProcess,
                                                # OnlyOfflineProcess, OnlyRT, Pitch Shift, Restoration, Reverb, Sampler, Spatial,
                                                # Stereo, Surround, Synth, Tools, Up-Downmix
)

target_include_directories(hardclip PUBLIC
    ${JUCE}/modules
)

target_sources(hardclip
    PRIVATE
        ${SRC}/PluginEditor.cpp
        ${SRC}/PluginProcessor.cpp
)

target_compile_definitions(hardclip
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
        JUCE_DISPLAY_SPLASH_SCREEN=0 # since we're licensed under GPLv3 we can remove the splash screen!
)

target_link_libraries(hardclip
    PRIVATE
        juce::juce_audio_utils
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)
