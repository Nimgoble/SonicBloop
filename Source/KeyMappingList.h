/*
  ==============================================================================

    KeyMappingList.h
    Created: 16 Oct 2015 10:57:28am
    Author:  johnathan

  ==============================================================================
*/

#ifndef KEYMAPPINGLIST_H_INCLUDED
#define KEYMAPPINGLIST_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "ChangeKeyButton.h"
#include "IKeyPressCollectionContainer.h"

//==============================================================================
/*
*/
class KeyMappingList : public Component, public ChangeKeyListener
{
public:
	KeyMappingList(ApplicationCommandManager& _commandManager, IKeyPressCollectionContainer *_container, int _maxKeys);
	~KeyMappingList();
	void addKeyPressButton(int keyNum, const KeyPress &keyPress, const bool isReadOnly);
	void paint(Graphics& g) override;
	void resized() override;

	void update();

	virtual void OnKeyAdded(const KeyPress &newKeyPress, int keyIndex);
	virtual void OnKeyRemoved(ChangeKeyButton *button, const KeyPress &keyPress, int keyIndex);
	virtual void OnKeyChanged(const KeyPress &oldKeyPress, const KeyPress &newKeyPress, int keyIndex);
	virtual CommandID GetCommandIDForKeyPress(const KeyPress &keyPress);
	virtual String GetCommandName(CommandID id);

private:
	ApplicationCommandManager& commandManager;
	OwnedArray<ChangeKeyButton> keyChangeButtons;
	WeakReference<IKeyPressCollectionContainer> container;
	ScopedPointer<ChangeKeyButton> addKeyButton;

	int maxKeys;

	//ChangeKeyButton *GetChangeKeyButtonByKeyCode(int keyCode);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KeyMappingList)
};


#endif  // KEYMAPPINGLIST_H_INCLUDED
