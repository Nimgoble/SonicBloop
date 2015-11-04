/*
  ==============================================================================

    SoundHotKeyConfigFile.h
    Created: 19 Oct 2015 11:24:21am
    Author:  johnathan

  ==============================================================================
*/

#ifndef SOUNDHOTKEYCONFIGFILE_H_INCLUDED
#define SOUNDHOTKEYCONFIGFILE_H_INCLUDED

#include "JuceHeader.h"
#include "SoundHotKeyInfo.h"
#include "SoundHotKeyInfoContainer.h"

class SoundHotKeyConfigFile
{
public:
	SoundHotKeyConfigFile(AudioDeviceManager &_audioDeviceManager, ApplicationCommandManager &_commandManager, ApplicationSettingsFile &_applicationSettingsFile);
	~SoundHotKeyConfigFile();
	bool LoadFile(File &file);
	bool SaveFile();
	void SaveFileAs(File &file);
	void Unload();

	int NumberOfSoundHotKeyEntries() { return SoundHotKeyInfoContainers.size(); }

	int AddSoundHotKey(String fileSource);
	void RemoveSoundHotKey(CommandID id);

	SoundHotKeyInfoContainer *GetContainerByCommandID(CommandID id);
	SoundHotKeyInfoContainer *GetContainerByIndex(int index);
	int GetIndexOfContainer(SoundHotKeyInfoContainer *container);

	bool IsNewFile(){ return isNewFile; }
	String GetConfigFilePath(){ return configFile; }

	static int COMMANDS_BASE;
private:
	AudioDeviceManager &audioDeviceManager;
	ApplicationCommandManager &commandManager;
	ApplicationSettingsFile &applicationSettingsFile;
	OwnedArray<SoundHotKeyInfoContainer> SoundHotKeyInfoContainers;
	String configFile;
	bool isNewFile;

	CommandID getNextCommandID();
};

#endif  // SOUNDHOTKEYCONFIGFILE_H_INCLUDED
