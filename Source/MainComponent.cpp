/*
 ==============================================================================
 
 This file was auto-generated!
 
 ==============================================================================
 */

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent (Audio& a) :   audio (a)  //Inherits audio
{
    filePlayerGui.setFilePlayer (audio.getFilePlayer()); //*file player gets set file player which in turn gets getFilePlayer() in audio
    addAndMakeVisible (filePlayerGui);
    filePlayerGui.setAlwaysOnTop(true);//* makes components visible
     addAndMakeVisible (reverbTitles);
     addAndMakeVisible (musicRoom);
    setSize (800, 800); //* sets gui window size
}

MainComponent::~MainComponent()
{
    
}

//==============================================================================
void MainComponent::resized()
{
    auto r = getLocalBounds(); //* makes localbounds r
    filePlayerGui.setBounds (r); // sets components as r
    reverbTitles.setBounds(getLocalBounds());
    musicRoom.setBounds(getLocalBounds());
    

    
}
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId)); //fills the Gui with colour
}

//MenuBarCallbacks==============================================================
juce::StringArray MainComponent::getMenuBarNames()
{
    auto names = { "File" };        // Menu bar names
    return juce::StringArray (names);
}

juce::PopupMenu MainComponent::getMenuForIndex (int topLevelMenuIndex, const juce::String& menuName)
{
    juce::PopupMenu menu;
    if (topLevelMenuIndex == 0)
        menu.addItem(AudioPrefs, "Audio Prefrences", true, false);
    return menu;  //Allows audio prefrences access
}

void MainComponent::menuItemSelected (int menuItemID, int topLevelMenuIndex) //allows and setting to be chosen
{
    if (topLevelMenuIndex == FileMenu)
    {
        if (menuItemID == AudioPrefs)
        {
            juce::DialogWindow::LaunchOptions la;
            la.dialogTitle = "Audio Settings";
            juce::OptionalScopedPointer<Component> osp (std::make_unique<juce::AudioDeviceSelectorComponent>
                                                        (audio.getAudioDeviceManager(),
                                                         1, 2, 2, 2,
                                                         true, true, true, false));
            osp->setSize (450, 350);
            la.content = std::move (osp);
            la.componentToCentreAround = this;
            la.launchAsync();
        }
    }
}








