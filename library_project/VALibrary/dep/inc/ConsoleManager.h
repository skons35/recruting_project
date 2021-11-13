#ifndef CONSOLE_MANAGER_H_
#define CONSOLE_MANAGER_H_

#include<LibraryManager.h>
using namespace librarymanagement;

namespace consolemanagement {

	class ConsoleManager
	{
		private: 
			LibraryManager* libraryManager;
		
		public:

			ConsoleManager();
			~ConsoleManager();

			void displayCommands();
			void processCommands(LibraryManager* _libraryManager);

		private:
			
			char getCommandKey(const char* comment);

			void manageAuthorAdd();
			void manageBookAdd();
			void manageFindBooksFromAuthor();
			void manageFindAuthorOfBook();

			void displayLibraryContent();
	
	};
};

#endif // CONSOLE_MANAGER_H_

