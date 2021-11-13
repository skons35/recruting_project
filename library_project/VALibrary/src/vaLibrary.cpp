// vaLibrary.cpp : Defines the entry point for the application.
//


#include "LibraryManager.h"

using namespace librarymanagement;

#include "ConsoleManager.h"

using namespace consolemanagement;

#include<iostream>
using namespace std;


int main()
{		
	ConsoleManager consoleManager;

	consoleManager.displayCommands();

	LibraryManager& libraryManager = LibraryManager::getInstance();
	
	// blocking until explicit exit
	consoleManager.processCommands(&libraryManager);
	
	return 0;
}
