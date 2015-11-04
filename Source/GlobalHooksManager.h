/*
  ==============================================================================

    GlobalHooksManager.h
    Created: 11 Oct 2015 12:48:30pm
    Author:  Nimgoble

  ==============================================================================
*/

#ifndef GLOBALHOOKSMANAGER_H_INCLUDED
#define GLOBALHOOKSMANAGER_H_INCLUDED

#include "..\JuceLibraryCode\JuceHeader.h"
#include "..\libuiohook\uiohook.h"
#include "GlobalHooksListener.h"

class GlobalHooksManager : private FocusChangeListener, private GlobalHooksDispatchListener
{
public:

	static GlobalHooksManager& getGlobalHooksManager();

	void Init();
	void Shutdown();

	/** Registers a listener to be told when mouse events occur in this component.

	If you need to get informed about mouse events in a component but can't or
	don't want to override its methods, you can attach any number of listeners
	to the component, and these will get told about the events in addition to
	the component's own callbacks being called.

	Note that a MouseListener can also be attached to more than one component.

	@param newListener                              the listener to register
	@param wantsEventsForAllNestedChildComponents   if true, the listener will receive callbacks
	for events that happen to any child component
	within this component, including deeply-nested
	child components. If false, it will only be
	told about events that this component handles.
	@see MouseListener, removeMouseListener
	*/
	//void addMouseListener(MouseListener* newListener, bool wantsEventsForAllNestedChildComponents);

	///** Deregisters a mouse listener.
	//@see addMouseListener, MouseListener
	//*/
	//void removeMouseListener(MouseListener* listenerToRemove);

	//==============================================================================
	/** Adds a listener that wants to hear about keypresses that this component receives.

	The listeners that are registered with a component are called by its keyPressed() or
	keyStateChanged() methods (assuming these haven't been overridden to do something else).

	If you add an object as a key listener, be careful to remove it when the object
	is deleted, or the component will be left with a dangling pointer.

	@see keyPressed, keyStateChanged, removeKeyListener
	*/
	void addKeyListener(KeyListener* newListener);

	/** Removes a previously-registered key listener.
	@see addKeyListener
	*/
	void removeKeyListener(KeyListener* listenerToRemove);

	/** Callback to indicate that the currently focused component has changed. */
	virtual void globalFocusChanged(Component* focusedComponent);

	virtual void OnMessageReceived(uiohook_event * const event);
	virtual bool WantsMessage(uiohook_event * const event);
	virtual void KeyPressed(const juce::KeyPress& key);

private:
	typedef GenericScopedLock<CriticalSection> WantsMessagesLock;
	CriticalSection wantsMessageMutex;
	bool shouldForwardMessages;

	GlobalHooksManager();

	//class MouseListenerList;
	//friend class MouseListenerList;
	//friend struct ContainerDeletePolicy<MouseListenerList>;
	//ScopedPointer<MouseListenerList> mouseListeners;
	ScopedPointer<Array<KeyListener*> > keyListeners;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GlobalHooksManager)
};

#endif  // GLOBALHOOKSMANAGER_H_INCLUDED
