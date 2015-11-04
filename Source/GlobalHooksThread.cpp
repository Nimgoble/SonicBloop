/*
  ==============================================================================

    GlobalHooksThread.cpp
    Created: 11 Oct 2015 3:35:05pm
    Author:  Nimgoble

  ==============================================================================
*/

#include "GlobalHooksThread.h"

GlobalHooksThread::GlobalHooksThread(event_type _eventTypeToHook) :
	Thread("Global Hooks Thread")
{	
	eventTypeToHook = _eventTypeToHook;
	startThread(8);
}

GlobalHooksThread::~GlobalHooksThread()
{
	signalThreadShouldExit();
	stopThread(2000);
}

void GlobalHooksThread::run()
{
	int result = hook_run(eventTypeToHook);
}

int GlobalHooksThread::StopHook()
{
	return hook_stop();
}

