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

#ifndef __JUCE_HEADER_5541AB09C63B7428__
#define __JUCE_HEADER_5541AB09C63B7428__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "KeyMappingList.h"
#include "SoundInfoOperationsListener.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class SoundHotKeyView  : public Component,
                         private Timer,
                         public ButtonListener
{
public:
    //==============================================================================
    SoundHotKeyView (SoundInfoOperationsListener *_listener, SoundHotKeyInfoContainer *_container);
    ~SoundHotKeyView();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void update(bool selected);
	const SoundHotKeyInfoContainer *getSoundHotKeyInfoContainer(){ return container; }
	void startRepainting();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	SoundInfoOperationsListener *listener;
	bool isSelected;
	WeakReference<SoundHotKeyInfoContainer> container;
	void timerCallback() override;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> lblSoundName;
    ScopedPointer<Label> label;
    ScopedPointer<Label> label2;
    ScopedPointer<Label> label3;
    ScopedPointer<Label> lblName;
    ScopedPointer<KeyMappingList> keyMappingList;
    ScopedPointer<TextButton> btnRemove;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SoundHotKeyView)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_5541AB09C63B7428__
