/*
  ==============================================================================

    MusicRoomGUI.cpp
    Created: 9 Feb 2021 9:13:11pm
    Author:  Thomas Riseborough

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MusicRoomGUI.h"

//==============================================================================
MusicRoomGUI::MusicRoomGUI()
{
header.setColour (juce::TextButton::buttonColourId, juce::Colours::cornflowerblue);
    header.setText("MusicRoom", juce::dontSendNotification);
    addAndMakeVisible (header);

}

MusicRoomGUI::~MusicRoomGUI()
{
}

void MusicRoomGUI::paint (juce::Graphics& g)
{
}

void MusicRoomGUI::resized()
{
    {
        header.setBounds (340, 720, 90,90);
    }

}
