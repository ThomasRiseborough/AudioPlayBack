
/*
 ==============================================================================
 
 This file was auto-generated!
 
 ==============================================================================
 */

#pragma once

#include <JuceHeader.h>
#include "Audio.h"
#include "FilePlayerGui.h"
#include "/Volumes/SEAGATE POR/SDA/PlayBack 1.3/Source/MusicRoomGUI.h"
#include "ReverbTitles.h"

//==============================================================================
/*
 This component lives inside our window, and this is where you should put all
 your controls and content.
 */
class MainComponent   : public juce::Component, //Class declaration
public juce::MenuBarModel   // inherits juce component and juce MenubarModel
{
public:
    //==============================================================================
    /** Constructor */
    MainComponent (Audio& a);
    
    /** Destructor */
    ~MainComponent();
    
    //Comoponent====================================================================
    /** Resized */
    void resized() ;
    void paint (juce::Graphics&) override;
    
    //MenuBarEnums/MenuBarModel=====================================================
   /**Number of Menus*/
    enum Menus
    {
        FileMenu = 0,
        
        NumMenus
    };
    /**Number of menu items */
    enum FileMenuItems
    {
        AudioPrefs = 1,
        
        NumFileItems
    };
    /**Getting menu bar names */
    juce::StringArray getMenuBarNames() override;
    juce::PopupMenu getMenuForIndex (int topLevelMenuIndex, const juce::String& menuName) override;
    /**menu item selected*/
    void menuItemSelected (int menuItemID, int topLevelMenuIndex) override;
    
private:
/**referance to audio
 @see Audio.h*/
    Audio& audio;
    /**referance to filePlayerGui
     @see FilePlayerGui.h*/
    FilePlayerGui filePlayerGui;
    MusicRoomGUI musicRoom;
    ReverbTitles reverbTitles;
    
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};




