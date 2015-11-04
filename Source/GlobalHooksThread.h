/*
  ==============================================================================

    GlobalHooksThread.h
    Created: 11 Oct 2015 3:34:51pm
    Author:  Nimgoble

  ==============================================================================
*/

#ifndef GLOBALHOOKSTHREAD_H_INCLUDED
#define GLOBALHOOKSTHREAD_H_INCLUDED

#include "..\JuceLibraryCode\JuceHeader.h"
#include "..\libuiohook\uiohook.h"

class GlobalHooksThread : public Thread
{
public:
	GlobalHooksThread(event_type _eventTypeToHook);
	~GlobalHooksThread();

	void run() override;

	int StopHook();

private:
	event_type eventTypeToHook;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GlobalHooksThread)
};



#endif  // GLOBALHOOKSTHREAD_H_INCLUDED
