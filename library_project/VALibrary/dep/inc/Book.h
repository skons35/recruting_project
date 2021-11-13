#ifndef BOOK_H_
#define BOOK_H_

#include"Author.h"

#include <string>
#include <optional>

using namespace std;

namespace libraryitems
{
	enum class BookType { COMIC, BOOK };

	class Book
	{
		private:
			string title;
			Author author;
			BookType bookType;			
			// below are nice to have information,
			// but are optionals (not used to discriminate books)
			optional<string> isbn;		
			// idea for completing the Book class :
			//optional<string> abstract;
			//optional<string> publisher;
			//optional<uint16_t> publishedYear;
			//optional<uint16_t> pagesCount;
				
			Book();

		public:
			Book(const string& _title, const Author& _author, const BookType& _bookType, const optional<string>& _isbn) :
				  title(_title), author(_author), bookType(_bookType), isbn(_isbn) {};

			bool operator==(const Book& _book) const;
			bool operator<(const Book& _book) const;

			
			friend bool isMatching(const string& _searchTitle, const BookType& _searchBookType, const Book& _candidateBook);

			// for easy display in console:
			friend ostream& operator<<(ostream& os, const Book& _book);
	};

}

#endif // BOOK_H_

