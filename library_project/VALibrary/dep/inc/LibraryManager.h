#ifndef LIBRARY_MANAGER_H_
#define LIBRARY_MANAGER_H_


#include<mutex>

#include<map>
#include<set>

using namespace std;

#include"Book.h"

using namespace libraryitems;


namespace librarymanagement {

	class LibraryManager
	{
	private:

		static mutex initLock;
		static mutex accessLock;

		map<Author, set<Book>> authorBookMap;

		LibraryManager();
		~LibraryManager();


	public:

		static LibraryManager& getInstance();

		bool addAuthor(const Author& _author);

		bool addBook(const Author& _author, const Book& _book);

		const set<Book> getBooksFromAuthor(const Author& _author);
		optional<Author> retrieveBookAuthor(const string& _bookTitle, const BookType& _booksType);

		const string getLibraryDetails();		
	};
};

#endif // LIBRARY_MANAGER_H_

