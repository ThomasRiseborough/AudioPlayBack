
/*
 ==============================================================================
 
 FilePlayerGui.cpp
 Created: 22 Jan 2013 2:49:07pm
 Author:  tj3-mitchell
 
 ==============================================================================
 */

#include "FilePlayerGui.h"

FilePlayerGui::FilePlayerGui()
{
    /** Makes visible my Sliders and Buttons*/
    playButton.addListener (this);
    addAndMakeVisible (playButton);
    addAndMakeVisible(sVolume);
    addAndMakeVisible(LVolume);
    addAndMakeVisible(sPlayBackRate);
    addAndMakeVisible(lPlayBackRate);
    addAndMakeVisible(sPosition);
    addAndMakeVisible(lPosition);
    
    addAndMakeVisible(lWet);
    /** Sets Text style*/
    sWetMix.setTextBoxStyle(juce::Slider::TextBoxLeft,
                                                  false,
                                                  50,
                                                  sWetMix.getTextBoxHeight()
                                                  );
    /** Attatches text to Slider*/
    lWet.attachToComponent(&sWetMix, true);

    addAndMakeVisible(lDry);
                      sDryMix.setTextBoxStyle(juce::Slider::TextBoxLeft,
                                              false,
                                              50,
                                              sDryMix.getTextBoxHeight()
                                              );
                      lDry.attachToComponent(&sDryMix, true);
    addAndMakeVisible(lRoomSize);
    /** Sets Text style*/
                      sRoomSize.setTextBoxStyle(juce::Slider::TextBoxLeft,
                                              false,
                                              50,
                                              sRoomSize.getTextBoxHeight()
                                              );
                         /** Attatches text to Slider*/
                      lRoomSize.attachToComponent(&sRoomSize, true);
    
    /** Declares slider listeners*/
    sVolume.addListener(this);
    sPlayBackRate.addListener(this);
    sPosition.addListener(this);
    
    //configure Playback slider and label
    double playBackRateDefaultValue = 1.0;
    sPlayBackRate.setRange(0.25, 4.0); //Not allowed lower than 0.25 or above 4.0
    sPlayBackRate.setNumDecimalPlacesToDisplay(2); /** Number of decimal places*/
    sPlayBackRate.setTextBoxStyle(juce::Slider::TextBoxLeft,
                                false,
                                50,
                                sPlayBackRate.getTextBoxHeight()
                                );
    /** sets defalt playback value*/
    sPlayBackRate.setValue(playBackRateDefaultValue);
    /** skews midpoint for logarythmic sliding*/
    sPlayBackRate.setSkewFactorFromMidPoint(playBackRateDefaultValue);
    /** Adds text and attatches it to component*/
    lPlayBackRate.setText("PlayBackRate", juce::dontSendNotification);
    lPlayBackRate.attachToComponent(&sPlayBackRate, true);
    
    //configure position slider and label
    sPosition.setRange(0.0, 1.0);
    sPosition.setNumDecimalPlacesToDisplay(2);
    sPosition.setTextBoxStyle(juce::Slider::TextBoxLeft,
                              false,
                              50,
                              sPosition.getTextBoxHeight()
                              );
    lPosition.setText("Position", juce::dontSendNotification);
    lPosition.attachToComponent(&sPosition, true);
    
    /** sets default value*/
    double volumeDefaultValue = 0.5;
    sVolume.setRange(0.0, 2.0);
    sVolume.setNumDecimalPlacesToDisplay(2);
    sVolume.setTextBoxStyle(juce::Slider::TextBoxLeft,
                              false,
                              50,
                              sVolume.getTextBoxHeight()
                              );
    sVolume.setValue(volumeDefaultValue);
    sVolume.setSkewFactorFromMidPoint(volumeDefaultValue);
    LVolume.setText("Volume", juce::dontSendNotification);
    LVolume.attachToComponent(&sVolume, true);
    
    // Makes reverb sliders visible
    addAndMakeVisible(sDryMix);
    addAndMakeVisible(sWetMix);
    addAndMakeVisible(sRoomSize);
    //adds listeners to the reverb sliders
    sDryMix.addListener(this);
    sWetMix.addListener(this);
    sRoomSize.addListener(this);
    /** Sets number of decimal place to 2*/
    sDryMix.setNumDecimalPlacesToDisplay(2);
    sWetMix.setNumDecimalPlacesToDisplay(2);
    sRoomSize.setNumDecimalPlacesToDisplay(2);
    
    /** Makes the reverb siders a rotary slider**/
    sDryMix.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    sWetMix.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    sRoomSize.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    
    
    
    sDryMix.setRange(0.01, 4.0); //reaches breakpoint if sliderValue == 0.01
    sWetMix.setRange(0.01, 1.5); //reaches breakpoint if sliderValue == 0.01
    sRoomSize.setRange(0.01, 1.5); //reaches breakpoint if sliderValue == 0.01
    
    // Declares formatManager
    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();
    //** makes a unique component the file chooser */
    fileChooser = std::make_unique<juce::FilenameComponent> ("audiofile",
                                                             juce::File(),
                                                             true, false, false,
                                                             formatManager.getWildcardForAllFormats(),
                                                             juce::String(),
                                                             "(select an audio file)");
    /** gives the file chooser a listener*/
    fileChooser->addListener (this);
    addAndMakeVisible (fileChooser.get());
}

FilePlayerGui::~FilePlayerGui()
{
    
}

//Component
void FilePlayerGui::resized()
{
   //Positions my components in the GUI
    auto r = getLocalBounds();
    juce::Rectangle<int> (700, 20, 300, 50);
    playButton.setBounds (200, 10, 200, 50);
    fileChooser->setBounds (400, 10, 200, 50);
    sVolume.setBounds(40, 90, 650, 50);
    sPlayBackRate.setBounds(40, 150, 650, 50);
    sPosition.setBounds(40, 210, 650, 50);
    sRoomSize.setBounds(600, 300, 150, 150);
    sWetMix.setBounds(20, 300, 150, 150);
    sDryMix.setBounds(300, 300, 150, 150);
    
    
}

//Button Listener
void FilePlayerGui::buttonClicked (juce::Button* button)
{
    if (filePlayer != nullptr && button == &playButton)
    {
        filePlayer->setPlaying( ! filePlayer->isPlaying());
    }
}

//Pointer to file player
void FilePlayerGui::setFilePlayer (FilePlayer* fp)
{
    filePlayer = fp;
}

//FilenameComponentListener
void FilePlayerGui::filenameComponentChanged (juce::FilenameComponent* fileComponentThatHasChanged)
{
    if (fileComponentThatHasChanged == fileChooser.get())
    {
        //Makes audioFile get path name chosen
        juce::File audioFile (fileChooser->getCurrentFile().getFullPathName());
        
        //loads file if non is present already
        if(filePlayer != nullptr && audioFile.existsAsFile())
        {
            filePlayer->loadFile(audioFile);
        }
        else   //Gives an error
        {
            juce::AlertWindow::showMessageBox (juce::AlertWindow::WarningIcon,
                                               "sdaTransport",
                                               "Couldn't open file!\n\n");
        }
    }
}

void FilePlayerGui::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &sVolume)  /** if volume slider is selected the value is taken */
    {
        DBG("Volume slider moved " << slider->getValue()); //Give an statement that slider has been moved 
        filePlayer->setGain(slider->getValue());
    }
    if (slider == &sPlayBackRate) /** if volume slider is selected the value is taken */
    {
        DBG("Play back rate slider moved " << slider->getValue()); //Give an statement that slider has been moved
        filePlayer->setPlayBackRate(slider->getValue());
    }
    if (slider == &sPosition) /** if volume slider is selected the value is taken */
    {
        DBG("Position slider moved " << slider->getValue()); //Give an statement that slider has been moved
        filePlayer->setPlayheadPosition(slider->getValue());
    }
    
    if (slider == &sRoomSize) /** if volume slider is selected the value is taken */
    {
         DBG("slider moved " << slider->getValue()); //Give an statement that slider has been moved
        filePlayer->setAmountRoomSize(slider->getValue());
    }
    if (slider == &sDryMix) /** if volume slider is selected the value is taken */
    {
         DBG("slider moved " << slider->getValue()); //Give an statement that slider has been moved
        filePlayer->setAmountDry(slider->getValue());
    }
    if (slider == &sWetMix) /** if volume slider is selected the value is taken */
    {
        DBG("slider moved " << slider->getValue());  //Give an statement that slider has been moved
        filePlayer->setAmountWet(slider->getValue());
    }
}
