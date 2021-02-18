
/*
 ==============================================================================
 FilePlayer.cpp
 ==============================================================================
 */

#include "FilePlayer.h"

FilePlayer::FilePlayer() : thread ("FilePlayThread")
{
    thread.startThread();
    reverbAudioSource.setParameters(reverbAmount);
    
}

FilePlayer::~FilePlayer()
{
    audioTransportSource.setSource (nullptr);   //unload the current file
    thread.stopThread (100);
}

void FilePlayer::setPlaying (bool newState)
{
    if(newState == true)
    {
        audioTransportSource.setPosition (0.0);
        audioTransportSource.start();
    }
    else
    {
        audioTransportSource.stop();
    }
}

bool FilePlayer::isPlaying () const
{
    return audioTransportSource.isPlaying();
}

void FilePlayer::loadFile(const juce::File& newFile)
{
    // unload the previous file source and delete it..
    setPlaying (false);
    audioTransportSource.setSource (nullptr);
    
    // create a new file source from the file..
    // get a format manager and set it up with the basic types (wav, ogg and aiff).
    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();
    
    if (auto reader = formatManager.createReaderFor (newFile))
    {
        //currentFile = audioFile;
        currentAudioFileSource = std::make_unique<juce::AudioFormatReaderSource> (reader, true);
        
        // ..and plug it into our transport source
        audioTransportSource.setSource (currentAudioFileSource.get(),
                                        32768, // tells it to buffer this many samples ahead
                                        &thread,
                                        reader->sampleRate);
    }
}

//AudioSource
void FilePlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    audioTransportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    reverbAudioSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void FilePlayer::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    reverbAudioSource.getNextAudioBlock(bufferToFill);
}

void FilePlayer::releaseResources()
{
    audioTransportSource.releaseResources();
    resampleSource.releaseResources();
    reverbAudioSource.releaseResources();
}

void FilePlayer::play()
{
    audioTransportSource.start();
}

void FilePlayer::stop()
{
    audioTransportSource.stop();
}

void FilePlayer::setPosition(double posInSecs)
{
    audioTransportSource.setPosition(posInSecs);
}

void FilePlayer::setPlayheadPosition(double position)
{
    double posInSecs = audioTransportSource.getLengthInSeconds() * position;
    setPosition(posInSecs);
    
}

void FilePlayer::setGain(double gain)
{
    
    audioTransportSource.setGain(gain);
}


void FilePlayer::setPlayBackRate(double playbackRate)
{
    
    resampleSource.setResamplingRatio(playbackRate);
}


void FilePlayer::setAmountRoomSize(float size)
{
    reverbAmount.roomSize = size;
    reverbAudioSource.setParameters(reverbAmount);
}



void FilePlayer::setAmountWet(float wetLevel)
{
    reverbAmount.wetLevel = wetLevel;
    reverbAudioSource.setParameters(reverbAmount);
}


void FilePlayer::setAmountDry(float dryLevel)
{
    reverbAmount.dryLevel = dryLevel;
    reverbAudioSource.setParameters(reverbAmount);
}


double FilePlayer::getPlayheadPosition()
{
    return audioTransportSource.getCurrentPosition() / audioTransportSource.getLengthInSeconds();
}

double FilePlayer::getLengthInSeconds()
{
    return audioTransportSource.getLengthInSeconds();
}


