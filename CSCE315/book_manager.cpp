#include "book_manager.h"

Book& BookManager::get(const string isbn) {
	if (!isValidIsbn(isbn)) {
		throw "ISBN is not valid";
	}
	for (auto& book : books) {
		if (book.isbn == isbn) {
			return book;
		}
	}
	throw "No book exists with that ISBN";
}

Book& BookManager::getOrCreate(const string isbn) {
	if (!isValidIsbn(isbn)) {
		throw "ISBN is not valid";
	}
	// Attempt to get from known books
	try {
		return get(isbn);
	} catch (const char*) {
		// Create if not found
		Book new_book;
		new_book.isbn = isbn;
		books.push_back(new_book);
		return get(isbn);
	}
}

bool BookManager::isValidIsbn(string isbn) {
	if (isbn.length() != 13) {
		return false;
	}
	int sum = 0;
	for (int i = 0; i < isbn.length(); ++i) {
		int digit = isbn[i] - '0';
		int multiplier = 1;
		if (i % 2 == 1) {
			multiplier = 3;
		}
		sum += multiplier * digit;
	}
	return sum % 10 == 0;
}