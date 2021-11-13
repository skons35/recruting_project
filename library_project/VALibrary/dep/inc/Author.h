#ifndef AUTHOR_H_
#define AUTHOR_H_

#include <string>
#include <optional>

using namespace std;

#include<iostream>

namespace libraryitems
{
	
	class Author
	{
		private:
			string firstName;
			string lastName;

			Author() {};

		public:
			Author(string _firstName, string _lastName) : firstName(_firstName), lastName(_lastName) {};
			
			bool operator==(const Author& _author) const;
			bool operator<(const Author& _author) const;
						
			// for easy display in console:
			friend ostream& operator<<(ostream& os, const Author& _author);
	};
}

#endif // AUTHOR_H_

