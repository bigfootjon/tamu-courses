#include <iostream>
#include <vector>
#include "book.h"
#include "course.h"
#include "book_manager.h"
#include "course_manager.h"

using namespace std;

// Many commands require a few arguments separated by spaces and then the rest of input is combined as the final argument
// For example, in the command "A 1234567890123 A book about books" the text "A book about books" is treated as a single
//     argument.
// This function takes the input (as a vector split up by spaces) and the index of the first argument to combine.
// It then returns all the variables from that index to the end of the input vector and joins them with spaces
string combine(vector<string> split, unsigned int initial) {
	if (initial >= split.size()) {
		throw out_of_range("combine");
	}

	string title;
	for (unsigned i = initial; i < split.size(); ++i) {
		if (i != initial) {
			title += " ";
		}
		title += split.at(i);
	}
	return title;
}

// Entry point to the program, input is ignored so those arguments have been removed
int main() {
	// Create the manager to store the books
	BookManager books;
	// Create the manager to store the courses
	CourseManager courses;

	// Continually take input until the program ends
	while (true) {
		string input;
		getline(cin, input);

		// Vector to store the split input
		vector<string> split;
		// Temporary variable to store substrings of input
		string current;
		// Read through each character of input in turn
		for (char i : input) {
			if (i == ' ') {
				// If the input is a space then add the current string to the vector and clear the current string
				split.push_back(current);
				current = "";
			} else {
				// If the input character is not a space add it to the current string
				current += i;
			}
		}
		// Since there isn't a space at the end of input to trigger the logic to add it to the input vector
		//    we need to check if there is data in the current string and add it to the end of the input if there is
		if (current.empty()) {
			split.push_back(current);
		}

		// If the input is empty, go to the next line
		if (split.empty()) {
			continue;
		}


		// The first part of input is the command code, so we store that here for convenience
		string& command = split.at(0);

		try {
			if (command == "B") {
				Book& book = books.getOrCreate(split.at(1));
				string title = combine(split, 2);
				book.title = title;
			} else if (command == "D") {
				Book& book = books.get(split.at(1));
				if (split.at(2) == "A") {
					string author = combine(split, 3);
					book.author = author;
				} else if (split.at(2) == "E") {
					int edition = stoi(split.at(3));
					book.edition = edition;
				} else if (split.at(2) == "D") {
					string& date = split.at(3);
					int month = stoi(date.substr(0,2));
					int year = stoi(date.substr(3,8));
					book.publication_month = month;
					book.publication_year = year;
				} else {
					cout << "Command '" << split.at(2) << "' not recognized";
				}
			} else if (command == "M") {
				Book& book = books.get(split.at(1));
				double cost = stod(split.at(2));
				if (split.at(3) == "N") {
					book.cost_new = cost;
				} else if (split.at(3) == "U") {
					book.cost_used = cost;
				} else if (split.at(3) == "R") {
					book.cost_rented = cost;
				} else if (split.at(3) == "E") {
					book.cost_electronic = cost;
				}
			} else if (command == "C") {
				Course& course = courses.getOrCreate(split.at(1), split.at(2));
				course.name = combine(split, 3);
			} else if (command == "A") {
				Book& book = books.get(split.at(1));
				Course& course = courses.get(split.at(2), split.at(3));
				string& section = split.at(4);
				bool required;
				if (split.at(5) == "R") {
					required = true;
				} else if (split.at(5) == "O") {
					required = false;
				} else {
					throw "Invalid selection for R/O";
				}
				course.addBookForSection(book, section, required);
			} else if (command == "GC") {
				Course& course = courses.get(split.at(1), split.at(2));
				for (auto& binding : course.books) {
					cout << binding.book.title << " (Section " << binding.section << ", ";
					if (binding.required) {
						cout << "Required";
					} else {
						cout << "Optional";
					}
					cout << ")" << endl;
				}
			} else if (command == "GS") {
				Course& course = courses.get(split.at(1), split.at(2));
				for (auto& binding : course.books) {
					if (binding.section == split.at(3)) {
						cout << binding.book.title << " (";
						if (binding.required) {
							cout << "Required";
						} else {
							cout << "Optional";
						}
						cout << ")" << endl;
					}
				}
			} else if (command == "GB") {
				Book book = books.get(split.at(1));
				cout << book << endl;
			} else if (command == "PB") {
				for (auto& book : books.books) {
					cout << book << endl;
				}
			} else if (command == "PC") {
				for (auto& course : courses.courses) {
					cout << course.department << " " << course.number << endl;
				}
			} else if (command == "PY") {
				int month = stoi(split.at(1).substr(0,2));
				int year = stoi(split.at(1).substr(3,8));
				for (auto& book : books.books) {
					bool shouldPrint = false;
					if (book.publication_year > year) {
						shouldPrint = true;
					} else if (book.publication_year == year && book.publication_month >= month) {
						shouldPrint = true;
					}
					if (shouldPrint) {
						cout << book << endl;
					}
				}
			} else if (command == "PD") {
				vector<Book> departmentBooks = courses.getBooksInDepartment(split.at(1));
				for (auto& book : departmentBooks) {
					cout << book << endl;
				}
			} else if (command == "PM") {
				vector<Book> departmentBooks = courses.getBooksInDepartment(split.at(1));
				cout << "TODO This command has not been implemented" << endl;
			} else if (command == "_EXIT") {
				break;
			} else if (command == "_PRINT") {
				cout << combine(split, 1) << endl;
			} else {
				cout << "Invalid command: '" << command << "'" << endl;
			}
		} catch (const char* error) {
			cerr << error << endl;
		} catch (out_of_range& error) {
			cerr << "Invalid command: " << input << endl;
		}
	}
}
