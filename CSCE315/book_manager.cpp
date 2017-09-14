#include "book_manager.h"
#include "main.h"

// Get a book from the manager by its ISBN (throw an error if not found)
Book& BookManager::get(const string isbn) {
	// Check ISBN validity
	if (!isISBNValid(isbn)) {
		throw InvalidCommand("ISBN is not valid");
	}

	// Iterate through all known books
	for (auto& book : books) {
		// If the ISBN matches the requested ISBN, return the book
		if (book.isbn == isbn) {
			return book;
		}
	}
	// If no books match the exception, throw an error
	throw InvalidCommand("No book exists with that ISBN");
}

// Try to lookup a book in the manager by its ISBN, if that fails create the book
Book& BookManager::getOrCreate(const string isbn) {
	// Check ISBN validity
	if (!isISBNValid(isbn)) {
		throw InvalidCommand("ISBN is not valid");
	}

	// Attempt to get from known books
	try {
		return get(isbn);
	} catch (InvalidCommand error) {
		// Create if not found
		Book new_book;
		new_book.isbn = isbn;
		books.push_back(new_book);
		return get(isbn);
	}
}

// Check if given ISBN number contains 13 digits
bool BookManager::isISBNValid(const string isbn) {
	return isbn.length() == 13;
}
