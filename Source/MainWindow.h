/*
  ==============================================================================

    MainWindow.h
    Created: 11 Oct 2015 12:23:32pm
    Author:  Nimgoble

  ==============================================================================
*/

#ifndef MAINWINDOW_H_INCLUDED
#define MAINWINDOW_H_INCLUDED

#include "MainComponent.h"

class MainWindow : public DocumentWindow, private AsyncUpdater
{
public:
	MainWindow(String name);
	~MainWindow();
        
    static MainWindow* getMainWindow(); // returns the MainWindow if it exists.

	// called by the OS when the window's close button is pressed.
	void closeButtonPressed() override;

	// (return the command manager object used to dispatch command events)
	static ApplicationCommandManager& getApplicationCommandManager();

	void Cleanup();

private:
	juce::ScopedPointer<MainComponent> mainComponent;
    void handleAsyncUpdate() override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
};




#endif  // MAINWINDOW_H_INCLUDED
