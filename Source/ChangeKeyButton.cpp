/*
  ==============================================================================

    ChangeKeyButton.cpp
    Created: 16 Oct 2015 11:00:25am
    Author:  johnathan

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "ChangeKeyButton.h"

//==============================================================================
ChangeKeyButton::ChangeKeyButton(ChangeKeyListener *_listener, KeyPress keyPress, const int keyIndex)
	: Button(keyPress.getTextDescription()),
	listener(_listener),
	keyNum(keyIndex)
{
	this->keyPress = keyPress;
	setWantsKeyboardFocus(false);
	setTriggeredOnMouseDown(keyNum >= 0);

	setTooltip(keyNum >= 0 ? TRANS("Adds a new key-mapping")
		: TRANS("Click to change this key-mapping"));
}

void ChangeKeyButton::paintButton(Graphics& g, bool /*isOver*/, bool /*isDown*/)
{
	getLookAndFeel().drawKeymapChangeButton(g, getWidth(), getHeight(), *this,
		keyNum >= 0 ? keyPress.getTextDescription() : String::empty);
}

void ChangeKeyButton::menuCallback(int result, ChangeKeyButton* button)
{
	if (button != nullptr)
	{
		switch (result)
		{
		case 1: button->assignNewKey(); break;
		case 2:
		{
			button->listener->OnKeyRemoved(button, button->keyPress, button->keyNum);
		}
		break;
		default: break;
		}
	}
}

void ChangeKeyButton::clicked()
{
	if (keyNum >= 0)
	{
		// existing key clicked..
		PopupMenu m;
		m.addItem(1, TRANS("Change this key-mapping"));
		m.addSeparator();
		m.addItem(2, TRANS("Remove this key-mapping"));

		m.showMenuAsync(PopupMenu::Options(),
			ModalCallbackFunction::forComponent(menuCallback, this));
	}
	else
	{
		assignNewKey();  // + button pressed..
	}
}

void ChangeKeyButton::fitToContent(const int h) noexcept
{
	if (keyNum < 0)
		setSize(h, h);
	else
		setSize(jlimit(h * 4, h * 8, 6 + Font(h * 0.6f).getStringWidth(getName())), h);
}

//==============================================================================
class ChangeKeyButton::KeyEntryWindow : public AlertWindow
{
public:
	KeyEntryWindow(ChangeKeyListener *_listener)
		: AlertWindow(TRANS("New key-mapping"),
		TRANS("Please press a key combination now..."),
		AlertWindow::NoIcon),
		listener(_listener)
	{
		addButton(TRANS("OK"), 1);
		addButton(TRANS("Cancel"), 0);

		// (avoid return + escape keys getting processed by the buttons..)
		for (int i = getNumChildComponents(); --i >= 0;)
			getChildComponent(i)->setWantsKeyboardFocus(false);

		setWantsKeyboardFocus(true);
		grabKeyboardFocus();
	}

	bool keyPressed(const KeyPress& key) override
	{
		lastPress = key;
		String message(TRANS("Key") + ": " + key.getTextDescription());

		const CommandID previousCommand = listener->GetCommandIDForKeyPress(key);

		if (previousCommand != 0)
			message << "\n\n("
			<< TRANS("Currently assigned to \"CMDN\"")
			.replace("CMDN", TRANS(listener->GetCommandName(previousCommand)))
			<< ')';

		setMessage(message);
		return true;
	}

	bool keyStateChanged(bool) override
	{
		return true;
	}

	KeyPress lastPress;

private:
	ChangeKeyListener *listener;

	JUCE_DECLARE_NON_COPYABLE(KeyEntryWindow)
};

void ChangeKeyButton::assignNewKeyCallback(int result, ChangeKeyButton* button, KeyPress newKey)
{
	if (result != 0 && button != nullptr)
		button->setNewKey(newKey, true);
}

void ChangeKeyButton::setNewKey(const KeyPress& newKey, bool dontAskUser)
{
	if (newKey.isValid())
	{
		if (keyNum >= 0)
			listener->OnKeyChanged(keyPress, newKey, keyNum);
		else
			listener->OnKeyAdded(newKey, keyNum);

		keyPress = newKey;
		setName(keyPress.getTextDescription());
	}
}

void ChangeKeyButton::keyChosen(int result, ChangeKeyButton* button)
{
	if (result != 0 && button != nullptr && button->currentKeyEntryWindow != nullptr)
	{
		button->currentKeyEntryWindow->setVisible(false);
		button->setNewKey(button->currentKeyEntryWindow->lastPress, false);
	}

	button->currentKeyEntryWindow = nullptr;
}

void ChangeKeyButton::assignNewKey()
{
	currentKeyEntryWindow = new KeyEntryWindow(listener);
	currentKeyEntryWindow->enterModalState(true, ModalCallbackFunction::forComponent(keyChosen, this));
}
