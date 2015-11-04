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

#include "SoundHotKeyView.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
SoundHotKeyView::SoundHotKeyView (SoundInfoOperationsListener *_listener, SoundHotKeyInfoContainer *_container)
{
    //[Constructor_pre] You can add your own custom stuff here..
	container = _container;
	listener = _listener;
	setInterceptsMouseClicks(true, true);
	ApplicationCommandManager &manager = MainWindow::getApplicationCommandManager();
    //[/Constructor_pre]

    addAndMakeVisible (lblSoundName = new Label ("Sound Name",
                                                 TRANS("Sound Name\n")));
    lblSoundName->setTooltip (TRANS("The name of the sound to be played\n"));
    lblSoundName->setFont (Font (15.00f, Font::plain));
    lblSoundName->setJustificationType (Justification::centredLeft);
    lblSoundName->setEditable (false, false, false);
    lblSoundName->setColour (TextEditor::textColourId, Colours::black);
    lblSoundName->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("Sound:\n")));
    label->setFont (Font (15.00f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label2 = new Label ("new label",
                                           TRANS("Keys:\n")));
    label2->setFont (Font (15.00f, Font::plain));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label3 = new Label ("new label",
                                           TRANS("Name:\n")));
    label3->setFont (Font (15.00f, Font::plain));
    label3->setJustificationType (Justification::centredLeft);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lblName = new Label ("Name",
                                            TRANS("Name\n")));
    lblName->setTooltip (TRANS("The name of the sound to be played\n"));
    lblName->setFont (Font (15.00f, Font::plain));
    lblName->setJustificationType (Justification::centredLeft);
    lblName->setEditable (false, false, false);
    lblName->setColour (TextEditor::textColourId, Colours::black);
    lblName->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (keyMappingList = new KeyMappingList (manager, container, 5));
    keyMappingList->setName ("List Of Key Mappings");

    addAndMakeVisible (btnRemove = new TextButton ("Removal Button"));
    btnRemove->setTooltip (TRANS("Removes the current sound from the configuration\n"));
    btnRemove->setButtonText (TRANS("X"));
    btnRemove->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnTop);
    btnRemove->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 75);


    //[Constructor] You can add your own custom stuff here..
	addAndMakeVisible(keyMappingList);
	keyMappingList->setName("List Of Key Mappings");
	isSelected = false;
	update(false);
	setOpaque(true);
	startRepainting();
    //[/Constructor]
}

SoundHotKeyView::~SoundHotKeyView()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	container = nullptr;
    //[/Destructor_pre]

    lblSoundName = nullptr;
    label = nullptr;
    label2 = nullptr;
    label3 = nullptr;
    lblName = nullptr;
    keyMappingList = nullptr;
    btnRemove = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void SoundHotKeyView::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
	if (!container->DoesSourceFileExist())
		g.fillAll(Colours::red);
	else if (container->isPlaying())
	{
		//If we're playing, then draw how far
		//through the sound we are.
		Rectangle<int> bounds = getLocalBounds();
		double percentageDone = container->getPercentageDone();
		double removalLength = bounds.getWidth() - (bounds.getWidth() * percentageDone);
		bounds.removeFromRight(removalLength);
		g.setColour(Colours::yellowgreen);
		g.fillRect(bounds);
		g.setColour(Colours::black);
	}

	juce::Colour boundsColor = (isSelected) ? Colours::blue : Colours::black;
	float width = (isSelected) ? 2.0f : 1.0f;
	g.setColour(boundsColor);
	g.drawRect(getBounds(), width);
    //[/UserPaint]
}

void SoundHotKeyView::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    lblSoundName->setBounds (88, 24, 416, 24);
    label->setBounds (24, 24, 56, 24);
    label2->setBounds (24, 48, 56, 24);
    label3->setBounds (24, 0, 56, 24);
    lblName->setBounds (88, 0, 416, 24);
    keyMappingList->setBounds (88, 48, 416, 24);
    btnRemove->setBounds (0, 0, 24, 24);
    //[UserResized] Add your own custom resize handling here..
	Rectangle<int> area(getLocalBounds());
	area.removeFromLeft(88);
	int width = area.getWidth();
	lblName->setBounds(88, 0, width, 24);
	lblSoundName->setBounds(88, 24, width, 24);
	keyMappingList->setBounds(88, 48, width, 24);
    //[/UserResized]
}

void SoundHotKeyView::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == btnRemove)
    {
        //[UserButtonCode_btnRemove] -- add your button handler code here..
		listener->RemoveInfo(container->GetSoundHotKeyInfo().CommandID);
        //[/UserButtonCode_btnRemove]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void SoundHotKeyView::update(bool selected)
{

	isSelected = selected;
	String name = (container == nullptr) ? String::empty : container->GetSoundHotKeyInfo().Name;
	String sourceFile = (container == nullptr) ? String::empty : container->GetSoundHotKeyInfo().SourceFile;
	lblName->setText(name, juce::NotificationType::sendNotification);
	lblSoundName->setText(sourceFile, juce::NotificationType::sendNotification);
	keyMappingList->update();
}

void SoundHotKeyView::startRepainting()
{
	if (container == nullptr || !container->isPlaying())
		return;

	startTimer(100);
}

void SoundHotKeyView::timerCallback()
{
	if (container == nullptr || !container->isPlaying())
		stopTimer();
	repaint();
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SoundHotKeyView" componentName=""
                 parentClasses="public Component, private Timer" constructorParams="SoundInfoOperationsListener *_listener, SoundHotKeyInfoContainer *_container"
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="1" initialWidth="600" initialHeight="75">
  <BACKGROUND backgroundColour="ffffffff"/>
  <LABEL name="Sound Name" id="86c88e3f451a529d" memberName="lblSoundName"
         virtualName="" explicitFocusOrder="0" pos="88 24 416 24" tooltip="The name of the sound to be played&#10;"
         edTextCol="ff000000" edBkgCol="0" labelText="Sound Name&#10;"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="77b34494e0b0f430" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="24 24 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Sound:&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="2f546040ef7989e3" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="24 48 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Keys:&#10;" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="e2bc49fe0afad01b" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="24 0 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Name:&#10;" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="Name" id="58e24e66b8fe83d8" memberName="lblName" virtualName=""
         explicitFocusOrder="0" pos="88 0 416 24" tooltip="The name of the sound to be played&#10;"
         edTextCol="ff000000" edBkgCol="0" labelText="Name&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <GENERICCOMPONENT name="List Of Key Mappings" id="8d8dd9199cffc638" memberName="keyMappingList"
                    virtualName="" explicitFocusOrder="0" pos="88 48 416 24" class="KeyMappingList"
                    params="manager, container, 5"/>
  <TEXTBUTTON name="Removal Button" id="23d6a364c662b5d" memberName="btnRemove"
              virtualName="" explicitFocusOrder="0" pos="0 0 24 24" tooltip="Removes the current sound from the configuration&#10;"
              buttonText="X" connectedEdges="5" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
