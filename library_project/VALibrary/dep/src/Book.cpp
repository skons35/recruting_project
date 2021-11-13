#include "Book.h"

#include<iostream>
using namespace std;

namespace libraryitems
{
	bool Book::operator==(const Book& _book)  const
	{
		// NOTE: i do not use optional information (ISBN,...)
		//       to discrimate books
		return ( (author == _book.author) &&
			     (title == _book.title)  &&
				 (bookType == _book.bookType)
			   );
	}

	bool Book::operator<(const Book& _book) const
	{
		if (bookType != _book.bookType)
		{
			return bookType < _book.bookType;
		} 
		else if (title != _book.title)
		{
			return title < _book.title;
		}		

		return (author < _book.author);
	}
	


	bool isMatching(const string& _searchTitle, const BookType& _searchBookType, const Book& _candidateBook)
	{
		return ((_searchTitle == _candidateBook.title) && (_searchBookType == _candidateBook.bookType));
	}

	ostream& operator<<(ostream& os, const Book& _book)
	{
		return os << _book.title << " , type : " << ( (_book.bookType == BookType::BOOK) ? "Book" : "Comic");
	}

};
