/*
  ==============================================================================

    MainWindow.cpp
    Created: 11 Oct 2015 12:23:39pm
    Author:  Nimgoble

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainWindow.h"
#include "GlobalHooksManager.h"

static ScopedPointer<ApplicationCommandManager> applicationCommandManager;

MainWindow::MainWindow(String name) : 
	DocumentWindow(name, Colours::lightgrey, DocumentWindow::allButtons)
{
	setUsingNativeTitleBar(true);
	mainComponent = new MainComponent();
	setContentNonOwned(mainComponent, false);

	setResizable(true, false);
	setResizeLimits(400, 400, 10000, 10000);
	centreWithSize(600, 400);
	setVisible(true);

	// this lets the command manager use keypresses that arrive in our window to send out commands
	addKeyListener(getApplicationCommandManager().getKeyMappings());
	GlobalHooksManager::getGlobalHooksManager().addKeyListener(getApplicationCommandManager().getKeyMappings());
	triggerAsyncUpdate();
}
MainWindow::~MainWindow()
{
	Cleanup();
}

void MainWindow::Cleanup()
{
	mainComponent->Cleanup();
	GlobalHooksManager::getGlobalHooksManager().removeKeyListener(getApplicationCommandManager().getKeyMappings());
	GlobalHooksManager::getGlobalHooksManager().Shutdown();
	if (applicationCommandManager != nullptr)
		applicationCommandManager = nullptr;
}

MainWindow* MainWindow::getMainWindow()
{
	for (int i = TopLevelWindow::getNumTopLevelWindows(); --i >= 0;)
		if (MainWindow* maw = dynamic_cast<MainWindow*> (TopLevelWindow::getTopLevelWindow(i)))
			return maw;

	return nullptr;
}

ApplicationCommandManager& MainWindow::getApplicationCommandManager()
{
	if (applicationCommandManager == nullptr)
		applicationCommandManager = new ApplicationCommandManager();

	return *applicationCommandManager;
}

void MainWindow::closeButtonPressed()
{
	// This is called when the user tries to close this window. Here, we'll just
	// ask the app to quit when this happens, but you can change this to do
	// whatever you need.
	JUCEApplication::getInstance()->systemRequestedQuit();
}

void MainWindow::handleAsyncUpdate()
{
	// This registers all of our commands with the command manager but has to be done after the window has
	// been created so we can find the number of rendering engines available
	ApplicationCommandManager& commandManager = MainWindow::getApplicationCommandManager();
	commandManager.registerAllCommandsForTarget(mainComponent);
	commandManager.registerAllCommandsForTarget(JUCEApplication::getInstance());
	commandManager.setFirstCommandTarget(mainComponent);
}
