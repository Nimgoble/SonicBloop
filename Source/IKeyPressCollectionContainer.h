/*
  ==============================================================================

    IKeyPressCollectionContainer.h
    Created: 29 Oct 2015 11:34:08am
    Author:  johnathan

  ==============================================================================
*/

#ifndef IKEYPRESSCOLLECTIONCONTAINER_H_INCLUDED
#define IKEYPRESSCOLLECTIONCONTAINER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class IKeyPressCollectionContainer
{
public:
	~IKeyPressCollectionContainer()
	{
		masterReference.clear();
	}

	virtual int OnKeyAdded(const KeyPress &newKeyPress) = 0;
	virtual void OnKeyRemoved(const KeyPress &keyPress) = 0;
	virtual void OnKeyChanged(const KeyPress &oldKeyPress, const KeyPress &newKeyPress) = 0;
	virtual int NumberOfKeyPresses() = 0;
	virtual const KeyPress &GetKeyPressByIndex(int index) = 0;
private:
	WeakReference<IKeyPressCollectionContainer>::Master masterReference;
	friend class WeakReference<IKeyPressCollectionContainer>;
};



#endif  // IKEYPRESSCOLLECTIONCONTAINER_H_INCLUDED
