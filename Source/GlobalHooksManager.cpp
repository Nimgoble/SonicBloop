/*
  ==============================================================================

    GlobalHooksManager.cpp
    Created: 11 Oct 2015 12:48:37pm
    Author:  Nimgoble

  ==============================================================================
*/

#include "GlobalHooksManager.h"
#include "GlobalHooksHooker.h"

static ScopedPointer<GlobalHooksManager> globalHooksManager;

GlobalHooksManager& GlobalHooksManager::getGlobalHooksManager()
{
	if (globalHooksManager == nullptr)
		globalHooksManager = new GlobalHooksManager();

	return *globalHooksManager;
}

//==============================================================================

GlobalHooksManager::GlobalHooksManager() :
	shouldForwardMessages(false)
{
}

void GlobalHooksManager::Init()
{
	Desktop::getInstance().addFocusChangeListener(this);
	GlobalHooksHooker::AddListener(this);
	GlobalHooksHooker::Init();
	GlobalHooksHooker::Run();
}

void GlobalHooksManager::Shutdown()
{
	GlobalHooksHooker::RemoveListener(this);
	GlobalHooksHooker::Shutdown();
	Desktop::getInstance().removeFocusChangeListener(this);
	globalHooksManager = nullptr;
}

void GlobalHooksManager::addKeyListener(KeyListener* const newListener)
{
	if (keyListeners == nullptr)
		keyListeners = new Array<KeyListener*>();

	keyListeners->addIfNotAlreadyThere(newListener);
}

void GlobalHooksManager::removeKeyListener(KeyListener* const listenerToRemove)
{
	if (keyListeners != nullptr)
		keyListeners->removeFirstMatchingValue(listenerToRemove);
}

/** Callback to indicate that the currently focused component has changed. */
void GlobalHooksManager::globalFocusChanged(Component* focusedComponent)
{
	{
		WantsMessagesLock lock(wantsMessageMutex);
		shouldForwardMessages = (focusedComponent == nullptr);
	}
}

void GlobalHooksManager::OnMessageReceived(uiohook_event * const event)
{

}

bool GlobalHooksManager::WantsMessage(uiohook_event * const event)
{
	bool result = false;
	{
		WantsMessagesLock lock(wantsMessageMutex);
		result = (event->type == GlobalHooksHooker::GetEventTypeToHook() && shouldForwardMessages);
	}
	return result;
}

void GlobalHooksManager::KeyPressed(const juce::KeyPress& keyInfo)
{
	int rawKeyCode = keyInfo.getKeyCode();
	int mods = keyInfo.getModifiers().getRawFlags();
	for (int i = keyListeners->size(); --i >= 0;)
	{
		{
			MessageManagerLock mml;
			bool keyWasUsed = keyListeners->getUnchecked(i)->keyPressed(keyInfo, nullptr);
		}
		i = jmin(i, keyListeners->size());
	}
}
