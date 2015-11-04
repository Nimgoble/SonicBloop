/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.2.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_CB0E969D2A8CE66E__
#define __JUCE_HEADER_CB0E969D2A8CE66E__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "ApplicationSettingsFile.h"
#include "KeyMappingList.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class SettingsTabComponent  : public Component,
                              public ApplicationCommandTarget,
                              public ComboBoxListener,
                              public ButtonListener
{
public:
    //==============================================================================
    SettingsTabComponent (AudioDeviceManager &_audioDeviceManager, ApplicationSettingsFile &_applicationSettingsFile);
    ~SettingsTabComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	ApplicationCommandTarget* getNextCommandTarget() override;
	void getAllCommands(Array<CommandID>& commands) override;
	void getCommandInfo(CommandID commandID, ApplicationCommandInfo& result) override;
	bool perform(const InvocationInfo& info) override;
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	AudioDeviceManager &audioDeviceManager;
	ApplicationSettingsFile &applicationSettingsFile;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<AudioDeviceSelectorComponent> audioDeviceSelector;
    ScopedPointer<ComboBox> cmbPlaySoundType;
    ScopedPointer<Label> lblPlaySoundType;
    ScopedPointer<Label> lblUseBackgroundHooks;
    ScopedPointer<ToggleButton> chkUseGlobalHooks;
    ScopedPointer<Label> lblStopAllSoundsHotkey;
    ScopedPointer<KeyMappingList> klStopAllSounds;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SettingsTabComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_CB0E969D2A8CE66E__
