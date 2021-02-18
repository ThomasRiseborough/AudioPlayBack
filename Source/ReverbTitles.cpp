/*
  ==============================================================================

    MusicRoomGUI.cpp
    Created: 9 Feb 2021 9:13:11pm
    Author:  Thomas Riseborough

  ==============================================================================
*/

#include <JuceHeader.h>
#include "/Volumes/SEAGATE POR/SDA/PlayBack 1.3/Source/ReverbTitles.h"

//==============================================================================
ReverbTitles::ReverbTitles()
{
Dry.setColour (juce::TextButton::buttonColourId, juce::Colours::cornflowerblue);
    Wet.setText("Dry Input", juce::dontSendNotification);
    addAndMakeVisible (Wet);
Wet.setColour (juce::TextButton::buttonColourId, juce::Colours::cornflowerblue);
    Dry.setText("Wet Input", juce::dontSendNotification);
    addAndMakeVisible (Dry);
RoomSize.setColour (juce::TextButton::buttonColourId, juce::Colours::cornflowerblue);
    RoomSize.setText("Room Size", juce::dontSendNotification);
    addAndMakeVisible (RoomSize);



}

ReverbTitles::~ReverbTitles()
{
}

void ReverbTitles::paint (juce::Graphics& g)
{
}

void ReverbTitles::resized()
{
    {
        Wet.setBounds (295, 340, 60, 30);
        Dry.setBounds (15, 340, 60, 30);
        RoomSize.setBounds (595, 340, 60, 30);
    }

}
