/*
  ==============================================================================

    GlobalHooksListener.h
    Created: 11 Oct 2015 3:41:39pm
    Author:  Nimgoble

  ==============================================================================
*/

#ifndef GLOBALHOOKSLISTENER_H_INCLUDED
#define GLOBALHOOKSLISTENER_H_INCLUDED

#include "..\libuiohook\uiohook.h"

class GlobalHooksDispatchListener
{
public:
	virtual void OnMessageReceived(uiohook_event * const event) = 0;
	virtual bool WantsMessage(uiohook_event * const event) = 0;
	virtual void KeyPressed(const juce::KeyPress& key) = 0;
};



#endif  // GLOBALHOOKSLISTENER_H_INCLUDED
