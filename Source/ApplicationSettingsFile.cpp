/*
  ==============================================================================

    ApplicationSettingsFile.cpp
    Created: 29 Oct 2015 2:32:14pm
    Author:  johnathan

  ==============================================================================
*/

#include "ApplicationSettingsFile.h"
#include "GlobalHooksManager.h"
#include "SoundHotKeyConfigFile.h"

ApplicationSettingsFile::ApplicationSettingsFile(ApplicationCommandManager& _commandManager) :
	commandManager(_commandManager)
{
	stopAllSoundsKeyListener = new StopAllSoundsKeysListener(commandManager, stopAllSoundsKeys, getStopAllSoundCommandInfo());
	setUseGlobalHooks(false);
	setPlayType(SoundPlayType::Restart);
}

void ApplicationSettingsFile::setUseGlobalHooks(bool _useGlobalHooks)
{
	useGlobalHooks = _useGlobalHooks;

	if (useGlobalHooks)
	{
		GlobalHooksManager::getGlobalHooksManager().Init();
	}
	else
	{
		GlobalHooksManager::getGlobalHooksManager().Shutdown();
	}
}

ApplicationCommandInfo ApplicationSettingsFile::getStopAllSoundCommandInfo()
{
	ApplicationCommandInfo commandInfo(CommandID(SoundHotKeyConfigFile::COMMANDS_BASE - 1));
	commandInfo.setInfo("Stop All Sounds", "Stops all sounds that are playing", juce::String::empty, 0);
	if (stopAllSoundsKeys.size() > 0)
	{
		const KeyPress &defaultKeyPress = stopAllSoundsKeys.getUnchecked(0);
		commandInfo.addDefaultKeypress(defaultKeyPress.getKeyCode(), defaultKeyPress.getModifiers());
	}

	return commandInfo;
}

void ApplicationSettingsFile::setPlayType(SoundPlayType _playType)
{
	playType = _playType;
	//Notify the SoundsTabComponent that the play type needs to change.
}

bool ApplicationSettingsFile::Load(File file)
{
	if (!file.exists())
		return false;

	configFile = file.getFullPathName();
	String jsonString = file.loadFileAsString();
	var json;
	Result result = JSON::parse(jsonString, json);
	if (result.ok())
	{
		DynamicObject* obj = json.getDynamicObject();
		if (obj == nullptr)
			return false;

		if(obj->hasProperty("PlayType"))
			setPlayType((SoundPlayType)(int)obj->getProperty("PlayType"));
		if (obj->hasProperty("UseGlobalHooks"))
			setUseGlobalHooks((bool)obj->getProperty("UseGlobalHooks"));

		if (obj->hasProperty("StopAllSoundKeyPresses"))
		{
			var keyPresses = obj->getProperty("StopAllSoundKeyPresses");
			if (keyPresses.isArray())
			{
				for (int i = 0; i < keyPresses.size(); ++i)
				{
					var jsonKeyPress(keyPresses[i]);
					if (jsonKeyPress.isVoid())
						continue;

					DynamicObject* jsonKeyPressObj = jsonKeyPress.getDynamicObject();
					if (jsonKeyPressObj == nullptr)
						continue;

					int keyCode = (int)jsonKeyPressObj->getProperty("KeyCode");
					int modifierFlags = (int)jsonKeyPressObj->getProperty("ModifierFlags");
					juce::juce_wchar textCharacter = (juce_wchar)((int)jsonKeyPressObj->getProperty("TextCharacter"));
					ModifierKeys modifierKeys;
					modifierKeys = modifierKeys.withFlags(modifierFlags);
					KeyPress keyPress(keyCode, modifierKeys, textCharacter);
					stopAllSoundsKeys.add(keyPress);
				}
			}
		}
	}

	return true;
}

void ApplicationSettingsFile::Save()
{
	if (configFile == String::empty)
		return;
	SaveAs(File(configFile));
}
void ApplicationSettingsFile::SaveAs(File file)
{
	var json = toJSON();
	FileOutputStream *outputStream = file.createOutputStream();
	outputStream->setPosition(0);
	JSON::writeToStream(*outputStream, json);
	outputStream->flush();
	delete outputStream;
	outputStream = nullptr;
}

var ApplicationSettingsFile::toJSON()
{
	DynamicObject *root = new DynamicObject();
	root->setProperty("PlayType", (int)playType);
	root->setProperty("UseGlobalHooks", useGlobalHooks);

	Array<var> keyPressObjects;
	for (int i = 0; i < stopAllSoundsKeys.size(); ++i)
	{
		const KeyPress &keyPress = stopAllSoundsKeys.getUnchecked(i);
		DynamicObject *keyPressObject = new DynamicObject();
		keyPressObject->setProperty("KeyCode", keyPress.getKeyCode());
		keyPressObject->setProperty("ModifierFlags", keyPress.getModifiers().getRawFlags());
		keyPressObject->setProperty("TextCharacter", (int)keyPress.getTextCharacter());
		keyPressObjects.add(var(keyPressObject));
	}

	root->setProperty("StopAllSoundKeyPresses", keyPressObjects);

	return var(root);
}