/*
  ==============================================================================

    SoundHotKeyInfo.h
    Created: 15 Oct 2015 11:25:09am
    Author:  Nimgoble

  ==============================================================================
*/

#ifndef SOUNDHOTKEYINFO_H_INCLUDED
#define SOUNDHOTKEYINFO_H_INCLUDED

#include "JuceHeader.h"

class SoundHotKeyInfo
{
    //What do we need?  We need...    
public:
	SoundHotKeyInfo();
	SoundHotKeyInfo(var json);

	var toJSON();
	ApplicationCommandInfo getApplicationCommandInfo();

	juce::CommandID CommandID;
    //A name for this particular file/keypress set
    juce::String Name;
    //The location of the sound file to play
    juce::String SourceFile;
    //Hotkey mappings
    Array<KeyPress> KeyPresses;

private:

	JUCE_LEAK_DETECTOR(SoundHotKeyInfo)
};

#endif  // SOUNDHOTKEYINFO_H_INCLUDED
