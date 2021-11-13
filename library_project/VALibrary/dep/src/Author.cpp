#include "Author.h"

//#include<iostream>
//using namespace std;


namespace libraryitems
{
	bool Author::operator==(const Author& _author) const 
	{
		return ((lastName == _author.lastName) && (firstName == _author.firstName));
	}
	
	bool Author::operator<(const Author& _author) const
	{
		if (firstName != _author.firstName) 
		{
			return firstName < _author.firstName;
		}
		return ( lastName < _author.lastName);
	}
	

	ostream& operator<<(ostream& os, const Author& _author)
	{
		return os << _author.firstName << " " << _author.lastName;
	}

};
