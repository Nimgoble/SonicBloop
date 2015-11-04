/*
  ==============================================================================

    ApplicationSettingsFile.h
    Created: 29 Oct 2015 2:32:14pm
    Author:  johnathan

  ==============================================================================
*/

#ifndef APPLICATIONSETTINGSFILE_H_INCLUDED
#define APPLICATIONSETTINGSFILE_H_INCLUDED

#include "..\JuceLibraryCode\JuceHeader.h"
#include "IKeyPressCollectionContainer.h"

enum SoundPlayType
{
	StopAndPlay = 1,
	Restart
};

class ApplicationSettingsFile
{
public:
	ApplicationSettingsFile(ApplicationCommandManager& _commandManager);
	bool getUseGlobalHooks(){ return useGlobalHooks; }
	void setUseGlobalHooks(bool _useGlobalHooks);

	Array<KeyPress> getStopAllSoundKeys(){ return stopAllSoundsKeys; }
	ApplicationCommandInfo getStopAllSoundCommandInfo();

	IKeyPressCollectionContainer *getStopAllSoundsCollectionContainer(){ return stopAllSoundsKeyListener; }

	SoundPlayType getPlayType(){ return playType; }
	void setPlayType(SoundPlayType _playType);

	bool Load(File file);
	void Save();
	void SaveAs(File file);
	var toJSON();
	String getConfigFileSource(){ return configFile; }

	ApplicationCommandManager &getCommandManager(){ return commandManager; }

private:
	bool useGlobalHooks;
	Array<KeyPress> stopAllSoundsKeys;
	SoundPlayType playType;

	ApplicationCommandManager& commandManager;

	class StopAllSoundsKeysListener : public IKeyPressCollectionContainer
	{
	public:
		StopAllSoundsKeysListener(ApplicationCommandManager& _commandManager, Array<KeyPress> &_stopAllSoundsKeys, ApplicationCommandInfo _stopAllSoundsKeysCommandInfo) :
			commandManager(_commandManager),
			stopAllSoundsKeys(_stopAllSoundsKeys),
			stopAllSoundsKeysCommandInfo(_stopAllSoundsKeysCommandInfo)
		{
		}

		virtual int OnKeyAdded(const KeyPress &newKeyPress)
		{
			commandManager.getKeyMappings()->addKeyPress(stopAllSoundsKeysCommandInfo.commandID, newKeyPress);
			stopAllSoundsKeys.add(newKeyPress);
			return stopAllSoundsKeys.indexOf(newKeyPress);
		}
		virtual void OnKeyRemoved(const KeyPress &keyPress)
		{
			int keyIndex = commandManager.getKeyMappings()->getKeyPressesAssignedToCommand(stopAllSoundsKeysCommandInfo.commandID).indexOf(keyPress);
			commandManager.getKeyMappings()->removeKeyPress(stopAllSoundsKeysCommandInfo.commandID, keyIndex);
			stopAllSoundsKeys.removeFirstMatchingValue(keyPress);
		}
		virtual void OnKeyChanged(const KeyPress &oldKeyPress, const KeyPress &newKeyPress)
		{
			OnKeyRemoved(oldKeyPress);
			OnKeyAdded(newKeyPress);
		}
		virtual int NumberOfKeyPresses()
		{
			return stopAllSoundsKeys.size();
		}
		virtual const KeyPress &GetKeyPressByIndex(int index)
		{
			return stopAllSoundsKeys.getReference(index);
		}

	private:
		ApplicationCommandManager& commandManager;
		Array<KeyPress> &stopAllSoundsKeys;
		ApplicationCommandInfo stopAllSoundsKeysCommandInfo;

	};

	ScopedPointer<StopAllSoundsKeysListener> stopAllSoundsKeyListener;
	String configFile;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ApplicationSettingsFile)
};

#endif  // APPLICATIONSETTINGSFILE_H_INCLUDED
