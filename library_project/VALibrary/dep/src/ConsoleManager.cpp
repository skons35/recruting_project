#include "ConsoleManager.h"

#include<iostream>
// #include<iomanip> // setfill()
using namespace std;

#include"LibraryManager.h"

namespace consolemanagement
{
	
	ConsoleManager::ConsoleManager()
	{
		libraryManager = nullptr;
	}

	ConsoleManager::~ConsoleManager()
	{
	}

	void ConsoleManager::displayCommands()
	{
		cout << "Library management (books, comics) :" << endl;
		cout << string(40, '-') << endl;
		cout << "(A) : Add an author," << endl;
		cout << "(B) : Add a book," << endl;
		cout << "(D) : Display library content" << endl;
		cout << "(F) : Find book(s) from an author" << endl;
		cout << "(S) : Find author of a book" << endl;
		cout << "(H) : Help (display this menu)" << endl;
		cout << "(Q) : Quit program" << endl;
		cout << string(40, '-') << endl;
	}

	
	void ConsoleManager::processCommands(LibraryManager* _libraryManager)
	{
		libraryManager = _libraryManager;
		bool loopRequired = true;	
		
		while(loopRequired)
		{
			char cmd = getCommandKey("- Enter your command :");
			
			switch(cmd)
			{

				case 'A':
						manageAuthorAdd();
						break;
				case 'B':
						manageBookAdd();
						break;
				case 'D':
						displayLibraryContent();
						break;
				case 'F':
						manageFindBooksFromAuthor();
						break;
				case 'S':
						manageFindAuthorOfBook();
						break;
				case 'H':
						displayCommands();
						break;
				case 'Q': 
						loopRequired = false;
						break;
				default:
					cout << "! Sorry, un-managed command !" << endl;
			}


		}		
	}

	char ConsoleManager::getCommandKey(const char* comment)
	{		
		cout << string(comment) << endl;
		string cmdString;
		std::getline(std::cin, cmdString);
		char cmd = cmdString[0];
		cmd = islower(cmd) ? (char)toupper(cmd) : cmd;
		return cmd;
	}

	void ConsoleManager::manageAuthorAdd() 
	{
		std::string authorFirstName, authorLastName;
		char enteredCommand;
		while (1) 
		{
			cout << "> ---- ADDing an author : ----" << endl;
			// First Name
			cout << "    - FirstName : " ;
			std::getline(std::cin, authorFirstName);			
			// Last name
			cout << "    - LastName  : ";
			std::getline(std::cin, authorLastName);			
			
			// whole input sequence (un)validation :
			enteredCommand = getCommandKey("<V> to Validate; <C> to Cancel,  (other key : restart add), then <Enter>");
			if ((enteredCommand == 'V')|| (enteredCommand == 'C'))
				break;
		}	
		
		// Add it in library (if validated add)
		if (enteredCommand == 'V')
		{
			bool opRes = libraryManager->addAuthor(Author(authorFirstName, authorLastName));
			cout << (opRes ? "Done" : "Failed") << "> Adding Author : " << authorFirstName << " , " << authorLastName << endl;
		}
		else 
		{
			cout << "Adding an author : cancelled operation" << endl;
		}
	}

	void ConsoleManager::manageBookAdd()
	{
		std::string bookTitle;
		optional<string> optBookIsbn;
		string authorFirstName, authorLastName, bookIsbn;
		BookType booktype;
		char enteredCommand;
		while (1)
		{
			cout << "> ---- ADDing a book : ----" << endl;	
			// Book Type			
			bool typeValid = false;
			while (!typeValid)
			{
				enteredCommand = getCommandKey("Book Type : press <B> for Book, <C> for Comic, then <Enter>");
				typeValid = ((enteredCommand == 'B') || (enteredCommand == 'C'));
			};
			booktype = (enteredCommand == 'B') ? BookType::BOOK : BookType::COMIC;
			// Author 
			//   First Name
			cout << "    - Author FirstName : ";
			std::getline(std::cin, authorFirstName);
			//   Last name
			cout << "    - Author LastName  : ";
			std::getline(std::cin, authorLastName);
			// Book Title
			cout << "    - Book Title : ";
			std::getline(std::cin, bookTitle);
			// Book ISBN (optional)
			cout << "    - Book ISBN (optional) : ";
			std::getline(std::cin, bookIsbn);
			if (!bookIsbn.empty())
				optBookIsbn = bookIsbn;

			// whole input sequence (un)validation :
			enteredCommand = getCommandKey("<V> to Validate; <C> to Cancel,  (other key : restart add), then <Enter>");
			if ((enteredCommand == 'V') || (enteredCommand == 'C'))
				break;
		}

		// Add it in library (if validated add)
		if (enteredCommand == 'V')
		{
			Author bookAuthor(authorFirstName, authorLastName);
			Book book(bookTitle, bookAuthor, booktype, optBookIsbn);
			bool opRes = libraryManager->addBook(bookAuthor, book);
			cout << (opRes ? "Done" : "Failed") << "> Adding Book : " << bookTitle << endl;
		}
		else
		{
			cout << "Adding a book : cancelled operation" << endl;
		}
	}

	void ConsoleManager::manageFindBooksFromAuthor()
	{
		std::string authorFirstName, authorLastName;
		char enteredCommand;
		while (1)
		{
			cout << "> ---- Books from an author : ----" << endl;
			// First Name
			cout << "Author FirstName : ";
			std::getline(std::cin, authorFirstName);
			// Last name
			cout << "Author LastName  : ";
			std::getline(std::cin, authorLastName);

			// whole input sequence (un)validation :
			enteredCommand = getCommandKey("<V> to Validate; <C> to Cancel,  (other key : restart add), then <Enter>");
			if ((enteredCommand == 'V') || (enteredCommand == 'C'))
				break;
		}

		// Add it in library (if validated add)
		if (enteredCommand == 'V')
		{
			// get list of matching books
			Author queryAuthor(authorFirstName, authorLastName);
			const set<Book> authorBooks = libraryManager->getBooksFromAuthor(queryAuthor);
			
			cout << "Book(s) count for author "<< queryAuthor << " : " << authorBooks.size() << endl;
			for (const auto& b : authorBooks)
				cout << " - " << b << endl;			
		}
		else
		{
			cout << "Searching for book(s) from an author : cancelled operation" << endl;
		}
	}

	void ConsoleManager::manageFindAuthorOfBook()
	{
		std::string bookTitle;		
		string authorFirstName, authorLastName;
		BookType bookType;
		char enteredCommand;
		while (1)
		{
			cout << "> ---- Search for author of a book : ----" << endl;
			// Book Type			
			bool typeValid = false;
			while (!typeValid)
			{
				enteredCommand = getCommandKey("Book Type : press <B> for Book, <C> for Comic, then <Enter>");
				typeValid = ((enteredCommand == 'B') || (enteredCommand == 'C'));
			};
			bookType = (enteredCommand == 'B') ? BookType::BOOK : BookType::COMIC;			
			// Book Title (complete or partial)
			cout << "    - Exact book's Title to search : ";
			std::getline(std::cin, bookTitle);
			
			// whole input sequence (un)validation :
			enteredCommand = getCommandKey("<V> to Validate; <C> to Cancel,  (other key : restart add), then <Enter>");
			if ((enteredCommand == 'V') || (enteredCommand == 'C'))
				break;
		}

		// Add it in library (if validated add)
		if (enteredCommand == 'V')
		{
			optional<Author> foundAuthor = libraryManager->retrieveBookAuthor(bookTitle, bookType);
			
			if (foundAuthor.has_value())
			{
				cout << "Found the book's author, this is :  " << foundAuthor.value() << endl;
			}
			else 
				cout << "Sorry, no author found for the book : " << bookTitle << " , of type : "<< ( (bookType == BookType::BOOK) ? "Book" : "Comic") << endl;
		}
		else
		{
			cout << "Search for author of a book : cancelled operation" << endl;
		}
	}

	void ConsoleManager::displayLibraryContent()
	{
		cout << "> ---- Library content details : ----" << endl;
		cout << libraryManager->getLibraryDetails() << endl;
	}
};
