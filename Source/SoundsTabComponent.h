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

#ifndef __JUCE_HEADER_7AC97C52F17A3894__
#define __JUCE_HEADER_7AC97C52F17A3894__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "SoundHotKeyInfo.h"
#include "SoundFileDragAndDropTarget.h"
#include "SoundInfoOperationsListener.h"
#include "SoundHotKeyConfigFile.h"
#include "ApplicationSettingsFile.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class SoundsTabComponent  : public Component,
                            public ListBoxModel,
                            public ChangeBroadcaster,
                            public MenuBarModel,
                            public SoundInfoOperationsListener,
                            public ApplicationCommandTarget
{
public:
    //==============================================================================
    SoundsTabComponent (AudioDeviceManager &_audioDeviceManager, ApplicationSettingsFile &_applicationSettingsFile);
    ~SoundsTabComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	int getNumRows() override;
	void paintListBoxItem(int rowNumber,
		Graphics& g,
		int width, int height,
		bool rowIsSelected) override;

	Component* refreshComponentForRow(int rowNumber, bool isRowSelected, Component*) override;

	StringArray getMenuBarNames() override;
	PopupMenu getMenuForIndex(int menuIndex, const String& /*menuName*/) override;
	void menuItemSelected(int menuItemID, int /*topLevelMenuIndex*/) override;


	void CreateInfoFromFile(const String &file) override;
	void RemoveInfo(CommandID id) override;

	ApplicationCommandTarget* getNextCommandTarget() override;
	void getAllCommands(Array<CommandID>& commands) override;
	void getCommandInfo(CommandID commandID, ApplicationCommandInfo& result) override;
	bool perform(const InvocationInfo& info) override;
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	ApplicationSettingsFile &applicationSettingsFile;
	AudioDeviceManager &audioDeviceManager;
	ScopedPointer<MenuBarComponent> menuBar;
	ScopedPointer<SoundHotKeyConfigFile> currentConfigFile;

	enum CommandIDs
	{
		cLoadSoundHotKeyFile = 0x2100,
		cSaveSoundHotkeyFile = 0x2101,
		cSaveSoundHotkeyFileAs = 0x2102
	};

	void Command_LoadSoundHotKeyFile();
	void LoadSoundHotKeyFile(File &file);
	void Command_SaveSoundHotKeyFile();
	void Command_SaveSoundHotKeyFileAs();
	void SaveSoundHotKeyFile(File &file);

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<ListBox> SoundHotKeyListBox;
    ScopedPointer<SoundFileDragAndDropTarget> soundFileDragAndDropTarget;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SoundsTabComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_7AC97C52F17A3894__
