#include "book.h"

Book& BookManager::get(const string isbn) {
	for (auto& book : books) {
		if (book.isbn == isbn) {
			return book;
		}
	}
	throw "No book exists with that ISBN";
}

Book& BookManager::getOrCreate(const string isbn) {
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

ostream& operator<<(ostream& out, const Book& book) {
	out << "Title: " << book.title;
	if (!book.author.empty()) {
		out  << endl << "- Author: " << book.author;
	}
	if (book.edition != 0) {
		out  << endl << "- Edition: " << book.edition;
	}
	if (book.publication_month != 0 && book.publication_year != 0) {
		out  << endl << "- Publication Date: " << book.publication_month << "/" << book.publication_year;
	}
	if (book.cost_new != 0) {
		out  << endl << "- Cost (new): " << book.cost_new;
	}
	if (book.cost_used != 0) {
		out  << endl << "- Cost (used): " << book.cost_used;
	}
	if (book.cost_rented != 0) {
		out  << endl << "- Cost (rented): " << book.cost_rented;
	}
	if (book.cost_electronic != 0) {
		out  << endl << "- Cost (electronic): " << book.cost_electronic;
	}
	return out;
}