#ifndef BOOK_MANAGER_HEADER
#define BOOK_MANAGER_HEADER

#include "book.h"

// Object that stores the known books and provides helper methods for looking up books
struct BookManager {
	vector<Book> books;

	Book& get(string isbn);
	Book& getOrCreate(string isbn);
};

#endif