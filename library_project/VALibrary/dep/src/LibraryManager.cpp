#include "LibraryManager.h"

#include<iostream>
#include<sstream>

namespace librarymanagement
{
	mutex LibraryManager::initLock;
	mutex LibraryManager::accessLock;

	LibraryManager& LibraryManager::getInstance()
	{
		lock_guard<mutex> lock(initLock);   // possibly un-needed on most recent compilers  (C++11 and above)
		static LibraryManager libraryManager; // as local static variable is now constructed in a thread safe way
		return libraryManager;
	}

	LibraryManager::LibraryManager()
	{
	}

	LibraryManager::~LibraryManager()
	{
	}

	bool LibraryManager::addAuthor(const Author& _author)
	{
		lock_guard<mutex> lock(accessLock);
		
		if (authorBookMap.end() != authorBookMap.find(_author))		
		{ 
			cout << "Author already inserted ! Skipping add." << endl; 
			return false;
		}

		// add it
		authorBookMap[_author] = set<Book>();		
		
		return true;
	}

	bool LibraryManager::addBook(const Author& _author, const Book& _book)
	{
		lock_guard<mutex> lock(accessLock);

		// Author may need to be inserted...
		if (authorBookMap.end() == authorBookMap.find(_author))
		{
			cout << "Adding Author in library first..." << endl;
			authorBookMap[_author] = set<Book>();			
		}

		// inserting the book in the author set (duplicate(s) are not inserted)
		const auto& a = authorBookMap.find(_author);
		auto res = a->second.insert(_book);
		return res.second; // false is set already contains that entry, true otherwise
	}

	const set<Book> LibraryManager::getBooksFromAuthor(const Author& _author) 
	{
		set<Book> authorBooks {};

		const auto& a = authorBookMap.find(_author);

		if (authorBookMap.end() != a)
		{
			for (const auto& b : a->second)
				authorBooks.insert(b);
		}

		return authorBooks;
	}

	optional<Author> LibraryManager::retrieveBookAuthor(const string& _bookTitle, const BookType& _booksType)
	{
		optional<Author> candidateAuthor;

		lock_guard<mutex> lock(accessLock);

		for (const auto& p : authorBookMap)
		{
			for (const auto& b : p.second)
			{
				if (isMatching(_bookTitle, _booksType, b))
				{
					candidateAuthor = p.first;
					break;
				}
			}
				
		}


		return candidateAuthor;
	}

	const string LibraryManager::getLibraryDetails()
	{
		lock_guard<mutex> lock(accessLock);
				
		stringstream sstream;

		sstream << "Defined Author(s) : " << authorBookMap.size() << endl;

		for (const auto& p : authorBookMap)
		{
			sstream << "Author : " << (p.first) << ", book count : " << (p.second).size() << endl;
			
			for (const auto& b : p.second)
				sstream << "     Book : " << b << endl;
		}
		return sstream.str();
	}

};
