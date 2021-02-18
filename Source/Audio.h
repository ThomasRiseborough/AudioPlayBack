
#pragma once

#include <JuceHeader.h>
#include <array>
#include "FilePlayer.h"

/** Class containing all audio processes */

class Audio :   public juce::MidiInputCallback,
public juce::AudioIODeviceCallback
{
public:
    /** Constructor */
    Audio();
    
    /** Destructor */
    ~Audio();
    
    /** returns a pointer to the file player
     @see getFilePlayer*/
    FilePlayer* getFilePlayer();
    
    /** gets Audiodevice manager
     @return the audio device manager */
    juce::AudioDeviceManager& getAudioDeviceManager() { return audioDeviceManager;}
    
    /**Handle incomming midi messages*/
    
    void handleIncomingMidiMessage (juce::MidiInput* source, const juce::MidiMessage& message) override;
    
    /**Puts audio into audiodecive callback and is where processing is done*/
    void audioDeviceIOCallback (const float** inputChannelData,
                                int numInputChannels,
                                float** outputChannelData,
                                int numOutputChannels,
                                int numSamples) override;
    /**How to set up the audio
     @return devive*/
    void audioDeviceAboutToStart (juce::AudioIODevice* device) override;
    void audioDeviceStopped() override;
private:
    /**Audio device manager referance handels current audio*/
    juce::AudioDeviceManager audioDeviceManager;
    /**AudioSourcePlayer referance*/
    juce::AudioSourcePlayer audioSourcePlayer;
    /**File player referance
     @see FilePlayer*/
    FilePlayer filePlayer;
};



