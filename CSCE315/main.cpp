#include <iostream>
#include <vector>
#include <string>
#include "main.h"

using namespace std;

BookManager books;

int main(int argc, char** argv) {
	while (true) {
		string input = "";
		getline(cin, input);

		vector<string> split;
		string current = "";
		for (int i = 0; i < input.length(); ++i) {
			if (input[i] == ' ') {
				split.push_back(current);
				current = "";
			} else {
				current += input[i];
			}
		}
		if (current.length() != 0) {
			split.push_back(current);
		}
		
		if (split.size() == 0) {
			continue;
		}
	
		string command = split.at(0);

		try {
			if (command == "B") {
				Book book = books.getOrCreate(split.at(1));
				string title = "";
				for (int i = 2; i < split.size(); ++i) {
					if (i != 2) {
						title += " ";
					}
					title += split.at(i);
				}
				book.setTitle(title);
			} else if (command == "D") {
			} else if (command == "M") {
			} else if (command == "C") {
			} else if (command == "A") {
			} else if (command == "GC") {
			} else if (command == "GS") {
			} else if (command == "GB") {
				Book book = books.get(split.at(1));
				cout << '"' << book.getTitle() << '"' << endl;
			} else if (command == "PB") {
			} else if (command == "PC") {
			} else if (command == "PY") {
			} else if (command == "PD") {
			} else if (command == "PM") {
			} else {
				cout << "Invalid command: '" << command << "'" << endl;
			}
		} catch (const char* error) {
			cerr << error << endl;
		}
	}
}

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

Book BookManager::get(string isbn) {
	for (Book book : books) {
		if (book.getIsbn() == isbn) {
			return book;
		}
	}
	throw "No book exists with that ISBN";
}

Book BookManager::getOrCreate(string isbn) {
	// Attempt to get from known books
	try {
		return get(isbn);
	} catch (const char*) {
		// Create if not found
		Book new_book;
		new_book.setIsbn(isbn);
		books.push_back(new_book);
		return new_book;
	}
}
