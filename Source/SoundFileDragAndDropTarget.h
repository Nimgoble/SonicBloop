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

#ifndef __JUCE_HEADER_8A6E8F29924344__
#define __JUCE_HEADER_8A6E8F29924344__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "SoundInfoOperationsListener.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class SoundFileDragAndDropTarget  : public Component,
                                    public FileDragAndDropTarget
{
public:
    //==============================================================================
    SoundFileDragAndDropTarget (SoundInfoOperationsListener *_listener);
    ~SoundFileDragAndDropTarget();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

	bool isInterestedInFileDrag(const StringArray& files) override;
	void filesDropped(const StringArray& files, int x, int y) override;
	void fileDragEnter(const StringArray& files, int x, int y) override;
	void fileDragExit(const StringArray& files) override;
	void mouseDoubleClick(const MouseEvent& event) override;
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	SoundInfoOperationsListener *listener;
	StringArray supportedAudioFormats;
	Colour backgroundColor;
	const Colour defaultBackgroundColor = Colours::aliceblue;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> label;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SoundFileDragAndDropTarget)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_8A6E8F29924344__
