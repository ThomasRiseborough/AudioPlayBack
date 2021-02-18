


/*
 ==============================================================================
 FilePlayer.h
 ==============================================================================
 */

#pragma once

#include <JuceHeader.h>

/** Simple FilePlayer class - strams audio from a file. */
class FilePlayer :  public juce::AudioSource
{
public:
    /** Constructor */
    FilePlayer();
    
    /** Destructor */
    ~FilePlayer();
    
    /** Starts or stops playback of the looper
     @param newState*/
    void setPlaying (bool newState);
    
    /** Gets the current playback state of the looper*/
    bool isPlaying() const;
    
    /** Loads the specified file into the transport source
     @return new selected file*/
    void loadFile (const juce::File& newFile);
    
    //AudioSource
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void releaseResources() override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
     /**plays audio file*/
    void play();
    /**Stops playing audio file*/
    void stop();
    /**Sets position of audio file
     @param position of playhead*/
    void setPlayheadPosition(double position);
    /**Sets the volume
     @param gain*/
    void setGain(double gain);
    /**Sets the PlayBackRate
     @param ratio*/
    void setPlayBackRate(double ratio);
    /**Gets position of playhead*/
    double getPlayheadPosition();
    /**Gets the length of transport source in seconds*/
    double getLengthInSeconds();
    /**Sets the amount of reverb
     @param size of room*/
    void setAmountRoomSize(float size);
    /**Sets the amount of reverb
     @param wetness level*/
    void setAmountWet(float wetLevel);
    /**Sets the amount of reverb
     @param dryLevel*/
    void setAmountDry(float dryLevel);
    /**sets position
     @param position in seconds*/
    void  setPosition(double posInSecs);
    
    
private:
    /** Unique pointer that produces current audio file source*/
    std::unique_ptr<juce::AudioFormatReaderSource> currentAudioFileSource;
    /**Reverb audio source uses resample source for playback rate*/
    juce::ReverbAudioSource reverbAudioSource{ &resampleSource, false };
    /**Resample source and takes current audioTransportSource
     @see setPlayBackRate()*/
    juce::ResamplingAudioSource resampleSource{ &audioTransportSource, false, 1 };
    juce::AudioTransportSource audioTransportSource;
    juce::TimeSliceThread thread;                             //thread for the transport source
    /**Referance for Amount of reverb being taken
     @see setAmountWet
     @see setAmountRoomSize
     @see setAmountDry*/
    juce::Reverb::Parameters reverbAmount;
};


