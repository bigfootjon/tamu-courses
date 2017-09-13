#ifndef BOOK_MANAGER_HEADER
#define BOOK_MANAGER_HEADER

#include "book.h"

struct BookManager {
	vector<Book> books;

	bool isValidIsbn(string isbn);
	Book& get(string isbn);
	Book& getOrCreate(string isbn);
};

#endif