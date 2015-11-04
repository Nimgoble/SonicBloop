/*
  ==============================================================================

    SoundInfoOperationsListener.h
    Created: 17 Oct 2015 10:46:17am
    Author:  Nimgoble

  ==============================================================================
*/

#ifndef SOUNDINFOOPERATIONSLISTENER_H_INCLUDED
#define SOUNDINFOOPERATIONSLISTENER_H_INCLUDED

#include "JuceHeader.h"
#include "SoundHotKeyInfo.h"

class SoundInfoOperationsListener
{
public:
	virtual void CreateInfoFromFile(const String &file) = 0;
	virtual void RemoveInfo(CommandID id) = 0;
};



#endif  // SOUNDINFOOPERATIONSLISTENER_H_INCLUDED
