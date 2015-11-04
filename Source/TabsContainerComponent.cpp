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

//[Headers] You can add your own extra header files here...

//[/Headers]

#include "TabsContainerComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
TabsContainerComponent::TabsContainerComponent (AudioDeviceManager &_audioDeviceManager, ApplicationSettingsFile &_applicationSettingsFile)
    : TabbedComponent (TabbedButtonBar::TabsAtTop),
      audioDeviceManager(_audioDeviceManager),
      applicationSettingsFile(_applicationSettingsFile)
{
    //[Constructor_pre] You can add your own custom stuff here..
	soundsTab = new SoundsTabComponent(audioDeviceManager, applicationSettingsFile);
	settingsTab = new SettingsTabComponent(audioDeviceManager, applicationSettingsFile);
	addTab("Sounds", juce::Colours::white, soundsTab, true, 0);
	addTab("Settings", juce::Colours::white, settingsTab, true, 1);
    //[/Constructor_pre]


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

TabsContainerComponent::~TabsContainerComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	/*soundsTab = nullptr;
	settingsTab = nullptr;*/
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TabsContainerComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
	TabbedComponent::paint(g);
    //[/UserPaint]
}

void TabsContainerComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
	TabbedComponent::resized();
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
ApplicationCommandTarget* TabsContainerComponent::getNextCommandTarget()
{
	// this will return the next parent component that is an ApplicationCommandTarget (in this
	// case, there probably isn't one, but it's best to use this method in your own apps).
	return findFirstTargetParentComponent();
}

void TabsContainerComponent::getAllCommands(Array<CommandID>& commands)
{
	settingsTab->getAllCommands(commands);
	soundsTab->getAllCommands(commands);
}

void TabsContainerComponent::getCommandInfo(CommandID commandID, ApplicationCommandInfo& result)
{
	settingsTab->getCommandInfo(commandID, result);
	soundsTab->getCommandInfo(commandID, result);
}

bool TabsContainerComponent::perform(const InvocationInfo& info)
{
	return settingsTab->perform(info) || soundsTab->perform(info);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TabsContainerComponent" componentName=""
                 parentClasses="public TabbedComponent, public ApplicationCommandTarget"
                 constructorParams="AudioDeviceManager &amp;_audioDeviceManager, ApplicationSettingsFile &amp;_applicationSettingsFile"
                 variableInitialisers="TabbedComponent (TabbedButtonBar::TabsAtTop),&#10;audioDeviceManager(_audioDeviceManager),&#10;applicationSettingsFile(_applicationSettingsFile)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
