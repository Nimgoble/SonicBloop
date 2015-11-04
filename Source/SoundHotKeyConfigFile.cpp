/*
  ==============================================================================

    SoundHotKeyConfigFile.cpp
    Created: 19 Oct 2015 11:24:21am
    Author:  johnathan

  ==============================================================================
*/

#include "SoundHotKeyConfigFile.h"

int SoundHotKeyConfigFile::COMMANDS_BASE = 0x2200;

SoundHotKeyConfigFile::SoundHotKeyConfigFile(AudioDeviceManager &_audioDeviceManager, ApplicationCommandManager &_commandManager, ApplicationSettingsFile &_applicationSettingsFile) :
	audioDeviceManager(_audioDeviceManager),
	commandManager(_commandManager),
	applicationSettingsFile(_applicationSettingsFile),
	isNewFile(true)
{

}
SoundHotKeyConfigFile::~SoundHotKeyConfigFile()
{
	Unload();
}

bool SoundHotKeyConfigFile::LoadFile(File &file)
{
	if (!file.exists())
		return false;

	String jsonString = file.loadFileAsString();
	var json;
	Result result = JSON::parse(jsonString, json);
	if (result.ok())
	{
		if (json.isArray())
		{
			for (int i = 0; i < json.size(); ++i)
			{
				var& child(json[i]);
				if (child.isVoid())
					continue;

				SoundHotKeyInfo info(child);
				info.CommandID = CommandID(COMMANDS_BASE + i);
				SoundHotKeyInfoContainer *container = new SoundHotKeyInfoContainer(commandManager, audioDeviceManager, applicationSettingsFile, info);
				SoundHotKeyInfoContainers.add(container);

				//Add the new command
				commandManager.registerCommand(info.getApplicationCommandInfo());
			}
		}
	}
	isNewFile = false;
	configFile = file.getFullPathName();

	return true;
}
bool SoundHotKeyConfigFile::SaveFile()
{
	if (isNewFile)
		return false;
	File saveFile(configFile);
	SaveFileAs(saveFile);
	return true;
}

void SoundHotKeyConfigFile::SaveFileAs(File &file)
{
	Array<var> children;
	for (int i = 0; i < SoundHotKeyInfoContainers.size(); ++i)
	{
		SoundHotKeyInfoContainer *container = SoundHotKeyInfoContainers.getUnchecked(i);
		SoundHotKeyInfo &info = container->GetSoundHotKeyInfo();
		var childJSON = info.toJSON();
		children.add(childJSON);
	}
	var root(children);
	FileOutputStream *outputStream = file.createOutputStream();
	outputStream->setPosition(0);
	JSON::writeToStream(*outputStream, root);
	outputStream->flush();
	delete outputStream;
	outputStream = nullptr;
}

void SoundHotKeyConfigFile::Unload()
{
	for (int i = 0; i < SoundHotKeyInfoContainers.size(); ++i)
	{
		SoundHotKeyInfoContainer *container = SoundHotKeyInfoContainers.getUnchecked(i);
		if (container == nullptr)
			continue;

		commandManager.removeCommand(container->GetSoundHotKeyInfo().CommandID);
	}
	SoundHotKeyInfoContainers.clear(true);
	/*isNewFile = true;
	configFile = String::empty;*/
}

int SoundHotKeyConfigFile::AddSoundHotKey(String fileSource)
{
	SoundHotKeyInfo info;
	File file = File(fileSource);
	info.Name = file.getFileName();
	info.SourceFile = file.getFullPathName();
	info.CommandID = getNextCommandID();
	int newRowIndex = SoundHotKeyInfoContainers.size();

	SoundHotKeyInfoContainer *container = new SoundHotKeyInfoContainer(commandManager, audioDeviceManager, applicationSettingsFile, info);
	SoundHotKeyInfoContainers.add(container);

	commandManager.registerCommand(info.getApplicationCommandInfo());

	return newRowIndex;
}
void SoundHotKeyConfigFile::RemoveSoundHotKey(CommandID id)
{
	SoundHotKeyInfoContainer *container = GetContainerByCommandID(id);
	if (container == nullptr)
		return;

	SoundHotKeyInfoContainers.removeObject(container, true);
}

SoundHotKeyInfoContainer *SoundHotKeyConfigFile::GetContainerByCommandID(CommandID id)
{
	for (int i = 0; i < SoundHotKeyInfoContainers.size(); ++i)
	{
		SoundHotKeyInfoContainer *container = SoundHotKeyInfoContainers.getUnchecked(i);
		if (container->GetSoundHotKeyInfo().CommandID == id)
			return container;
	}
	return nullptr;
}

SoundHotKeyInfoContainer *SoundHotKeyConfigFile::GetContainerByIndex(int index)
{
	if (index < 0 || index > NumberOfSoundHotKeyEntries())
		return nullptr;

	return SoundHotKeyInfoContainers.getUnchecked(index);
}

int SoundHotKeyConfigFile::GetIndexOfContainer(SoundHotKeyInfoContainer *container)
{
	return SoundHotKeyInfoContainers.indexOf(container);
}

CommandID SoundHotKeyConfigFile::getNextCommandID()
{
	if (SoundHotKeyInfoContainers.size() == 0)
		return CommandID(COMMANDS_BASE);

	CommandID highest(COMMANDS_BASE);
	for (int i = 0; i < SoundHotKeyInfoContainers.size(); ++i)
	{
		CommandID current = SoundHotKeyInfoContainers.getUnchecked(i)->GetSoundHotKeyInfo().CommandID;
		if (highest < current)
			highest = current;
	}

	return CommandID(highest + 1);
}