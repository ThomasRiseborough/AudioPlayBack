
/*
 ==============================================================================
 FilePlayerGui.h
 ==============================================================================
 */

#pragma once

#include <JuceHeader.h>
#include "FilePlayer.h"

/** Gui for the FilePlayer class */
class FilePlayerGui :   public juce::Component,
private juce::Button::Listener,
private juce::FilenameComponentListener,
public juce::Slider::Listener

{
public:
    /** constructor - receives a reference to a FilePlayer object to control */
    FilePlayerGui();
    
    /** Destructor */
    ~FilePlayerGui();
    
    /** sets the file player that this gui controls
    @param fp referance to file player*/
    void setFilePlayer (FilePlayer* fp);
    
    //Component
    void resized() override;
    
    /**All slider value changes and assignmensts are done here
       @param slider referance to slider */
    void sliderValueChanged(juce::Slider* slider) override;
    
    
private:
    /**Button Listener
     @param button referance to Button clicked*/
    void buttonClicked (juce::Button* button) override;
    
    juce::Slider sVolume;  //volume slider
    juce::Label LVolume; //volume label
    juce::Slider sPlayBackRate; //volume slider
    juce::Label lPlayBackRate; //volume label
    juce::Slider sPosition; //volume slider
    juce::Label lPosition; //volume label
    juce::Slider sDryMix; //volume slider
    juce::Slider sWetMix; //volume slider
    juce::Slider sRoomSize; //volume slider
    juce::Label lWet; //volume label
    juce::Label lDry; //volume label
    juce::Label lRoomSize; //volume label
    
    
    
    
    /** FilenameComponentListener */
    void filenameComponentChanged (juce::FilenameComponent* fileComponentThatHasChanged) override;
    
    /** text button */
     
    juce::TextButton playButton   { ">" };
    /** unique pointer to choose file */
    std::unique_ptr<juce::FilenameComponent> fileChooser;
    
    /** pointer to empty file player */
    FilePlayer* filePlayer  { nullptr };
};


