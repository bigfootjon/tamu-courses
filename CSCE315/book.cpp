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