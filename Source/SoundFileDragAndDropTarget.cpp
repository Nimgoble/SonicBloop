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

#include "SoundFileDragAndDropTarget.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
SoundFileDragAndDropTarget::SoundFileDragAndDropTarget (SoundInfoOperationsListener *_listener)
{
    //[Constructor_pre] You can add your own custom stuff here..
	setInterceptsMouseClicks(true, true);
	backgroundColor = defaultBackgroundColor;
	listener = _listener;
    //[/Constructor_pre]

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("Drop Files Here To Add Them To The List!\n"
                                          "\n"
                                          "Or Double-Click To Choose Files!\n")));
    label->setFont (Font (15.00f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 100);


    //[Constructor] You can add your own custom stuff here..

	label->addMouseListener(this, true);
//	const AudioFormat* formats[] =
//	{
//		new AiffAudioFormat(),
//		new FlacAudioFormat(),
//#ifdef IOS
//		new CoreAudioFormat(),
//		/*MP3AudioFormat(),*/
//#endif
//		new OggVorbisAudioFormat(),
//		new WavAudioFormat(),
//		new WindowsMediaAudioFormat()
//	};

	Array<AudioFormat *> audioFormats;
	audioFormats.add(new AiffAudioFormat());
	audioFormats.add(new FlacAudioFormat());
#ifdef IOS
	audioFormats.add(new CoreAudioFormat());
	/*MP3AudioFormat(),*/
#endif
	audioFormats.add(new OggVorbisAudioFormat());
	audioFormats.add(new WavAudioFormat());
	audioFormats.add(new WindowsMediaAudioFormat());

	//std::initializer_list<AudioFormat> list
//	Array<AudioFormat *> audioFormats =
//	{
//		new AiffAudioFormat(),
//		new FlacAudioFormat(),
//#ifdef IOS
//		new CoreAudioFormat(),
//		/*MP3AudioFormat(),*/
//#endif
//		new OggVorbisAudioFormat(),
//		new WavAudioFormat(),
//		new WindowsMediaAudioFormat()
//	};

	//audioFormats.addArray(list)
	for (int i = 0; i < audioFormats.size(); ++i)
	{
		AudioFormat *format = audioFormats.getUnchecked(i);
		StringArray strAudioFormats = format->getFileExtensions();
		supportedAudioFormats.addArray(strAudioFormats);
		delete format;
		format = nullptr;
	}
	audioFormats.clear();
    //[/Constructor]
}

SoundFileDragAndDropTarget::~SoundFileDragAndDropTarget()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    label = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void SoundFileDragAndDropTarget::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
	g.fillAll(backgroundColor);
	g.setColour(Colours::black);
	Rectangle<int> bounds = getBounds().translated(0, -24);
	//I have no idea why I have to do -24.  The fill color fills the correct area, so why
	//doesn't the rectangle draw in the correct area?
	g.drawRect(bounds, 2.0f);
    //[/UserPaint]
}

void SoundFileDragAndDropTarget::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    label->setBounds (308 - (279 / 2), 52 - (48 / 2), 279, 48);
    //[UserResized] Add your own custom resize handling here..
	label->centreWithSize(label->getWidth(), label->getHeight());
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

bool SoundFileDragAndDropTarget::isInterestedInFileDrag(const StringArray& files)
{
	for (int i = 0; i < files.size(); ++i)
	{
		String file = files[i];
		String extension = File(file).getFileExtension();
		if (!supportedAudioFormats.contains(extension))
			return false;
	}

	return true;
}
void SoundFileDragAndDropTarget::filesDropped(const StringArray& files, int x, int y)
{
	for (int i = 0; i < files.size(); ++i)
	{
		String file = files[i];
		listener->CreateInfoFromFile(file);
	}
	backgroundColor = defaultBackgroundColor;
	repaint();
}

void SoundFileDragAndDropTarget::fileDragEnter(const StringArray& files, int x, int y)
{
	backgroundColor = (isInterestedInFileDrag(files)) ? Colours::green : Colours::red;
	repaint();
}
void SoundFileDragAndDropTarget::fileDragExit(const StringArray& files)
{
	backgroundColor = defaultBackgroundColor;
	repaint();
}
void SoundFileDragAndDropTarget::mouseDoubleClick(const MouseEvent& event)
{
	StringArray fileFormats;
	for (int i = 0; i < supportedAudioFormats.size(); ++i)
	{
		fileFormats.add("*" + supportedAudioFormats.getReference(i));
	}

	FileChooser fc
	(
		"Choose sound files to add...",
		File::getCurrentWorkingDirectory(),
		fileFormats.joinIntoString(";"),
		false
	);

	if (fc.browseForMultipleFilesToOpen())
	{
		for (int i = 0; i < fc.getResults().size(); ++i)
		{
			listener->CreateInfoFromFile(fc.getResults().getReference(i).getFullPathName());
		}
	}
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SoundFileDragAndDropTarget"
                 componentName="" parentClasses="public Component, public FileDragAndDropTarget"
                 constructorParams="SoundInfoOperationsListener *_listener" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="600" initialHeight="100">
  <BACKGROUND backgroundColour="ffffffff"/>
  <LABEL name="new label" id="8ed9c8a01a34ebfd" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="307.5c 52c 279 48" edTextCol="ff000000"
         edBkgCol="0" labelText="Drop Files Here To Add Them To The List!&#10;&#10;Or Double-Click To Choose Files!&#10;"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
