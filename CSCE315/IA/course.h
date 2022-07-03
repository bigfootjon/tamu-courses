#ifndef COURSE_HEADER
#define COURSE_HEADER

#include <string>
#include <vector>
#include "book.h"

using namespace std;

// Define the structure to store information about courses
struct Course {
	string department = "";
	string number = "";
	string name = "";

	// Define a structure to connect books and courses
	// Also includes information like the section and whether or not the book is required
	struct BookBinding {
		Book book;
		string section;
		bool required;
	};

	// List of all known books
	vector<BookBinding> books{};

	void addBookForSection(Book& book, string section, bool required);
};

#endif