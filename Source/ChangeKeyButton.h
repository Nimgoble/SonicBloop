/*
  ==============================================================================

    ChangeKeyButton.h
    Created: 16 Oct 2015 11:00:25am
    Author:  johnathan

  ==============================================================================
*/

#ifndef CHANGEKEYBUTTON_H_INCLUDED
#define CHANGEKEYBUTTON_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "SoundHotKeyInfo.h"

//==============================================================================
/*
*/

class ChangeKeyButton;
class ChangeKeyListener
{
public:
	virtual void OnKeyAdded(const KeyPress &newKeyPress, int keyIndex) = 0;
	virtual void OnKeyRemoved(ChangeKeyButton *button, const KeyPress &keyPress, int keyIndex) = 0;
	virtual void OnKeyChanged(const KeyPress &oldKeyPress, const KeyPress &newKeyPress, int keyIndex) = 0;
	virtual CommandID GetCommandIDForKeyPress(const KeyPress &keyPress) = 0;
	virtual String GetCommandName(CommandID id) = 0;
};

class ChangeKeyButton : public Button
{
public:
	ChangeKeyButton(ChangeKeyListener *_listener, KeyPress keyPress, const int keyIndex);

	void paintButton(Graphics& g, bool /*isOver*/, bool /*isDown*/) override;

	static void menuCallback(int result, ChangeKeyButton* button);

	void clicked() override;

	void fitToContent(const int h) noexcept;
	class KeyEntryWindow;

	static void assignNewKeyCallback(int result, ChangeKeyButton* button, KeyPress newKey);

	void setNewKey(const KeyPress& newKey, bool dontAskUser);

	static void keyChosen(int result, ChangeKeyButton* button);

	void assignNewKey();

private:
	ChangeKeyListener *listener;
	KeyPress keyPress;
	const int keyNum;
	ScopedPointer<KeyEntryWindow> currentKeyEntryWindow;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ChangeKeyButton)
};


#endif  // CHANGEKEYBUTTON_H_INCLUDED
