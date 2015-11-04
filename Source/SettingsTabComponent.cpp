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

#include "SettingsTabComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
SettingsTabComponent::SettingsTabComponent (AudioDeviceManager &_audioDeviceManager, ApplicationSettingsFile &_applicationSettingsFile)
    : audioDeviceManager(_audioDeviceManager),
      applicationSettingsFile(_applicationSettingsFile)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (audioDeviceSelector = new AudioDeviceSelectorComponent (audioDeviceManager,
                                                                               2,
                                                                               2,
                                                                               2,
                                                                               2,
                                                                               false,
                                                                               false,
                                                                               true,
                                                                               true));
    audioDeviceSelector->setName ("Audio Device Selector");

    addAndMakeVisible (cmbPlaySoundType = new ComboBox ("Play Sound Type Combobox"));
    cmbPlaySoundType->setTooltip (TRANS("How a sound should react to the \'play\' button.\n"));
    cmbPlaySoundType->setEditableText (false);
    cmbPlaySoundType->setJustificationType (Justification::centredLeft);
    cmbPlaySoundType->setTextWhenNothingSelected (String::empty);
    cmbPlaySoundType->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    cmbPlaySoundType->addListener (this);

    addAndMakeVisible (lblPlaySoundType = new Label ("Play Sound Type Label",
                                                     TRANS("Play Sound Mode:")));
    lblPlaySoundType->setFont (Font (15.00f, Font::plain));
    lblPlaySoundType->setJustificationType (Justification::centredLeft);
    lblPlaySoundType->setEditable (false, false, false);
    lblPlaySoundType->setColour (TextEditor::textColourId, Colours::black);
    lblPlaySoundType->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lblUseBackgroundHooks = new Label ("Use Background Hooks Label",
                                                          TRANS("Use Background Hooks:")));
    lblUseBackgroundHooks->setFont (Font (15.00f, Font::plain));
    lblUseBackgroundHooks->setJustificationType (Justification::centredLeft);
    lblUseBackgroundHooks->setEditable (false, false, false);
    lblUseBackgroundHooks->setColour (TextEditor::textColourId, Colours::black);
    lblUseBackgroundHooks->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (chkUseGlobalHooks = new ToggleButton ("Use Global Hooks Checkbox"));
    chkUseGlobalHooks->setButtonText (String::empty);
    chkUseGlobalHooks->addListener (this);

    addAndMakeVisible (lblStopAllSoundsHotkey = new Label ("Stop All Sounds Hotkey Label",
                                                           TRANS("Stop All Sounds Hotkey:")));
    lblStopAllSoundsHotkey->setFont (Font (15.00f, Font::plain));
    lblStopAllSoundsHotkey->setJustificationType (Justification::centredLeft);
    lblStopAllSoundsHotkey->setEditable (false, false, false);
    lblStopAllSoundsHotkey->setColour (TextEditor::textColourId, Colours::black);
    lblStopAllSoundsHotkey->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (klStopAllSounds = new KeyMappingList (applicationSettingsFile.getCommandManager(), applicationSettingsFile.getStopAllSoundsCollectionContainer(), 5));
    klStopAllSounds->setName ("Stop All Sounds Keylist");


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
	cmbPlaySoundType->addItem("Restart", (int)SoundPlayType::Restart);
	cmbPlaySoundType->addItem("Play/Stop", (int)SoundPlayType::StopAndPlay);
	cmbPlaySoundType->setSelectedId(applicationSettingsFile.getPlayType());
	chkUseGlobalHooks->setToggleState(applicationSettingsFile.getUseGlobalHooks(), juce::NotificationType::sendNotificationSync);
    //[/Constructor]
}

SettingsTabComponent::~SettingsTabComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    audioDeviceSelector = nullptr;
    cmbPlaySoundType = nullptr;
    lblPlaySoundType = nullptr;
    lblUseBackgroundHooks = nullptr;
    chkUseGlobalHooks = nullptr;
    lblStopAllSoundsHotkey = nullptr;
    klStopAllSounds = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void SettingsTabComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void SettingsTabComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    audioDeviceSelector->setBounds (0, 0, 416, 264);
    cmbPlaySoundType->setBounds (176, 272, 238, 24);
    lblPlaySoundType->setBounds (0, 272, 150, 24);
    lblUseBackgroundHooks->setBounds (0, 320, 150, 24);
    chkUseGlobalHooks->setBounds (176, 320, 24, 24);
    lblStopAllSoundsHotkey->setBounds (0, 368, 150, 24);
    klStopAllSounds->setBounds (176, 368, 240, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void SettingsTabComponent::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == cmbPlaySoundType)
    {
        //[UserComboBoxCode_cmbPlaySoundType] -- add your combo box handling code here..
		applicationSettingsFile.setPlayType((SoundPlayType)comboBoxThatHasChanged->getSelectedId());
        //[/UserComboBoxCode_cmbPlaySoundType]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void SettingsTabComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == chkUseGlobalHooks)
    {
        //[UserButtonCode_chkUseGlobalHooks] -- add your button handler code here..
		applicationSettingsFile.setUseGlobalHooks(buttonThatWasClicked->getToggleState());
        //[/UserButtonCode_chkUseGlobalHooks]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
ApplicationCommandTarget* SettingsTabComponent::getNextCommandTarget()
{
	// this will return the next parent component that is an ApplicationCommandTarget (in this
	// case, there probably isn't one, but it's best to use this method in your own apps).
	return findFirstTargetParentComponent();
}

void SettingsTabComponent::getAllCommands(Array<CommandID>& commands)
{
}

void SettingsTabComponent::getCommandInfo(CommandID commandID, ApplicationCommandInfo& result)
{
}

bool SettingsTabComponent::perform(const InvocationInfo& info)
{
	return false;
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SettingsTabComponent" componentName=""
                 parentClasses="public Component, public ApplicationCommandTarget"
                 constructorParams="AudioDeviceManager &amp;_audioDeviceManager, ApplicationSettingsFile &amp;_applicationSettingsFile"
                 variableInitialisers="audioDeviceManager(_audioDeviceManager)&#10;applicationSettingsFile(_applicationSettingsFile)&#10;"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <GENERICCOMPONENT name="Audio Device Selector" id="dc7596dee90e04d3" memberName="audioDeviceSelector"
                    virtualName="" explicitFocusOrder="0" pos="0 0 416 264" class="AudioDeviceSelectorComponent"
                    params="audioDeviceManager,&#10;2,&#10;2,&#10;2,&#10;2,&#10;false,&#10;false,&#10;true,&#10;true"/>
  <COMBOBOX name="Play Sound Type Combobox" id="fd8186a5b0de3d8d" memberName="cmbPlaySoundType"
            virtualName="" explicitFocusOrder="0" pos="176 272 238 24" tooltip="How a sound should react to the 'play' button.&#10;"
            editable="0" layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="Play Sound Type Label" id="32abba3b9033298d" memberName="lblPlaySoundType"
         virtualName="" explicitFocusOrder="0" pos="0 272 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Play Sound Mode:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="Use Background Hooks Label" id="5e54dced95461aa6" memberName="lblUseBackgroundHooks"
         virtualName="" explicitFocusOrder="0" pos="0 320 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Use Background Hooks:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="Use Global Hooks Checkbox" id="9e238c3a734f2d3c" memberName="chkUseGlobalHooks"
                virtualName="" explicitFocusOrder="0" pos="176 320 24 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <LABEL name="Stop All Sounds Hotkey Label" id="652a7ba0170b1b31" memberName="lblStopAllSoundsHotkey"
         virtualName="" explicitFocusOrder="0" pos="0 368 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Stop All Sounds Hotkey:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <GENERICCOMPONENT name="Stop All Sounds Keylist" id="3afabf010f6ae563" memberName="klStopAllSounds"
                    virtualName="" explicitFocusOrder="0" pos="176 368 240 24" class="KeyMappingList"
                    params="applicationSettingsFile.getCommandManager(), applicationSettingsFile.getStopAllSoundsCollectionContainer(), 5"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
