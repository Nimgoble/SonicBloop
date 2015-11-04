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
#include "MainWindow.h"
//[/Headers]

#include "MainComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MainComponent::MainComponent ()
{
    //[Constructor_pre] You can add your own custom stuff here..
	InitializeAudioDeviceManager();
	InitializeApplicationSettings();
    //[/Constructor_pre]

    addAndMakeVisible (tabsContainer = new TabsContainerComponent (*audioDeviceManager, *applicationSettingsFile));
    tabsContainer->setName ("Tab Container");


    //[UserPreSize]
	setOpaque(true);
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
	//Command_LoadSoundHotKeyFile();
    //[/Constructor]
}

MainComponent::~MainComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    tabsContainer = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MainComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    tabsContainer->setBounds (0, 0, 456, 600);
    //[UserResized] Add your own custom resize handling here..
	tabsContainer->setBounds(getLocalBounds().reduced(4));
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void MainComponent::Cleanup()
{
	SaveAudioDeviceSettings();
	SaveApplicationSettings();
}

void MainComponent::InitializeAudioDeviceManager()
{
	audioDeviceManager = new AudioDeviceManager();
	String audioSettingsFileSrc = GetAudioSettingsFileLocation();
	juce::File audioSettingsFile = juce::File(audioSettingsFileSrc);
	XmlElement *savedState = nullptr;
	if (audioSettingsFile.existsAsFile())
	{
		XmlDocument doc(audioSettingsFile);
		savedState = doc.getDocumentElement();
	}
	else
	{
		juce::File::createFileWithoutCheckingPath(audioSettingsFileSrc);
	}

	String status = audioDeviceManager->initialise(2, 2, savedState, true, String::empty, 0);//TODO: device options.

	if (savedState != nullptr)
	{
		delete savedState;
		savedState = nullptr;
	}
}

void MainComponent::SaveAudioDeviceSettings()
{
	XmlElement *savedState = audioDeviceManager->createStateXml();
	if (savedState != nullptr)
	{
		savedState->writeToFile(GetAudioSettingsFileLocation(), String::empty);
		delete savedState;
		savedState = nullptr;
	}
}

String MainComponent::GetAudioSettingsFileLocation()
{
	return juce::File::getSpecialLocation(juce::File::SpecialLocationType::currentExecutableFile).getParentDirectory().getChildFile("audiosettings.xml").getFullPathName();
}

void MainComponent::InitializeApplicationSettings()
{
	applicationSettingsFile = new ApplicationSettingsFile(MainWindow::getApplicationCommandManager());
	String applicationSettingsFileSrc = GetApplicationSettingsFileLocation();
	juce::File applicationSettingsFileFile = juce::File(applicationSettingsFileSrc);
	if (!applicationSettingsFileFile.existsAsFile())
	{
		applicationSettingsFileFile = juce::File::createFileWithoutCheckingPath(applicationSettingsFileSrc);
		OutputStream *stream = applicationSettingsFileFile.createOutputStream();
		stream->setPosition(0);
		stream->writeString(String::empty);
		stream->flush();
		delete stream;
		stream = nullptr;
	}
	applicationSettingsFile->Load(applicationSettingsFileFile);
}
void MainComponent::SaveApplicationSettings()
{
	applicationSettingsFile->Save();
}
String MainComponent::GetApplicationSettingsFileLocation()
{
	return juce::File::getSpecialLocation(juce::File::SpecialLocationType::currentExecutableFile).getParentDirectory().getChildFile("applicationsettings.json").getFullPathName();
}


ApplicationCommandTarget* MainComponent::getNextCommandTarget()
{
	// this will return the next parent component that is an ApplicationCommandTarget (in this
	// case, there probably isn't one, but it's best to use this method in your own apps).
	return findFirstTargetParentComponent();
}

void MainComponent::getAllCommands(Array<CommandID>& commands)
{
	tabsContainer->getAllCommands(commands);
}

void MainComponent::getCommandInfo(CommandID commandID, ApplicationCommandInfo& result)
{
	tabsContainer->getCommandInfo(commandID, result);
}

bool MainComponent::perform(const InvocationInfo& info)
{
	return tabsContainer->perform(info);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainComponent" componentName=""
                 parentClasses="public Component, public ApplicationCommandTarget"
                 constructorParams="" variableInitialisers="&#10;" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="0"
                 initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <GENERICCOMPONENT name="Tab Container" id="ad8eeaaf265e1bad" memberName="tabsContainer"
                    virtualName="" explicitFocusOrder="0" pos="0 0 456 600" class="TabsContainerComponent"
                    params="*audioDeviceManager"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
