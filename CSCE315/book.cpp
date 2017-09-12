#include "book.h"

string Book::getIsbn() {
    return isbn;
}

void Book::setIsbn(string new_isbn) {
    isbn = new_isbn;
}

string Book::getTitle() {
    return title;
}

void Book::setTitle(string new_title) {
    title = new_title;
}

Book& BookManager::get(const string isbn) {
    for (auto& book : books) {
        if (book.getIsbn() == isbn) {
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
        new_book.setIsbn(isbn);
        books.push_back(new_book);
        return get(isbn);
    }
}