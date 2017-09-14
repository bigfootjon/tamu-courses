#include <iostream>
#include <vector>
#include "book.h"
#include "course.h"
#include "book_manager.h"
#include "course_manager.h"

using namespace std;

// Create the global manager to store the books
BookManager books;
// Create the global manager to store the courses
CourseManager courses;

// Many commands require a few arguments separated by spaces and then the rest of input is combined as the final argument
// For example, in the command "A 1234567890123 A book about books" the text "A book about books" is treated as a single
//     argument.
// This function takes the input (as a vector split up by spaces) and the index of the first argument to combine.
// It then returns all the variables from that index to the end of the input vector and joins them with spaces
string combine(vector<string> split, unsigned int initial) {
	// Return an error is the input is shorter than the given initial index
	if (initial >= split.size()) {
		throw out_of_range("combine");
	}

	string combined;
	// Iterate through the split parts of the input
	for (unsigned i = initial; i < split.size(); ++i) {
		// If we're not on the first iteration, add a space before adding the input segment
		if (i != initial) {
			combined += " ";
		}
		combined += split.at(i);
	}
	return combined;
}

void commandAddBook(string isbn, string title) {
	Book& book = books.getOrCreate(isbn);
	book.title = title;
}

void commandSetBookDetail(string isbn, const string mode, string data) {
	Book& book = books.get(isbn);
	if (mode == "A") {
		book.author = data;
	} else if (mode == "E") {
		int edition = stoi(data);
		book.edition = edition;
	} else if (mode == "D") {
		int month = stoi(data.substr(0,2));
		int year = stoi(data.substr(3,8));
		book.publication_month = month;
		book.publication_year = year;
	} else {
		cout << "Command mode '" << mode << "' not recognized";
	}
}

void commandSetPrice(string isbn, double cost, const string type) {
	Book& book = books.get(isbn);
	if (type == "N") {
		book.cost_new = cost;
	} else if (type == "U") {
		book.cost_used = cost;
	} else if (type == "R") {
		book.cost_rented = cost;
	} else if (type == "E") {
		book.cost_electronic = cost;
	}
}

void commandAddCourse(string department, string number, string name) {
	Course& course = courses.getOrCreate(department, number);
	course.name = name;
}

void commandAddBookToCourse(string isbn, string department, string number, string section, string type) {
	Book& book = books.get(isbn);
	Course& course = courses.get(department, number);
	bool required;
	if (type == "R") {
		required = true;
	} else if (type == "O") {
		required = false;
	} else {
		throw "Invalid selection for R/O";
	}
	course.addBookForSection(book, section, required);
}

void commandPrintBooksForCourse(string department, string number) {
	Course& course = courses.get(department, number);
	for (auto& binding : course.books) {
		cout << binding.book.title << " (Section " << binding.section << ", ";
		if (binding.required) {
			cout << "Required";
		} else {
			cout << "Optional";
		}
		cout << ")" << endl;
	}
}

void commandPrintBooksForSection(string department, string number, string section) {
	Course& course = courses.get(department, number);
	for (auto& binding : course.books) {
		if (binding.section == section) {
			cout << binding.book.title << " (";
			if (binding.required) {
				cout << "Required";
			} else {
				cout << "Optional";
			}
			cout << ")" << endl;
		}
	}
}

void commandPrintBook(string isbn) {
	Book book = books.get(isbn);
	cout << book << endl;
}

void commandPrintAllBooks() {
	for (auto& book : books.books) {
		cout << book << endl;
	}
}

void commandPrintAllCourses() {
	for (auto& course : courses.courses) {
		cout << course.department << " " << course.number << endl;
	}
}

void commandPrintBooksSince(int month, int year) {
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
}

void commandPrintBooksInDepartment(string department) {
	vector<Book> departmentBooks = courses.getBooksInDepartment(department);
	for (auto& book : departmentBooks) {
		cout << book << endl;
	}
}

void commandPrintAverages(string department) {
	vector<Book> departmentBooks = courses.getBooksInDepartment(department);
	cout << "TODO This command has not been implemented" << endl;
}

void call_command(string input_line) {
	// Vector to store the split input
	vector<string> split;
	// Temporary variable to store substrings of input
	string current;
	// Read through each character of input in turn
	for (char i : input_line) {
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

	// If the input is empty, go to the next line of input
	if (split.empty()) {
		return;
	}


	// The first part of input is the command code, so we store that here for convenience
	string& command = split.at(0);

	try {
		if (command == "B") {
			commandAddBook(split.at(1), combine(split, 2));
		} else if (command == "D") {
			commandSetBookDetail(split.at(1), split.at(2), combine(split, 3));
		} else if (command == "M") {
			commandSetPrice(split.at(1), stod(split.at(2)), split.at(3));
		} else if (command == "C") {
			commandAddCourse(split.at(1), split.at(2), combine(split, 3));
		} else if (command == "A") {
			commandAddBookToCourse(split.at(1), split.at(2), split.at(3), split.at(4), split.at(5));
		} else if (command == "GC") {
			commandPrintBooksForCourse(split.at(1), split.at(2));
		} else if (command == "GS") {
			commandPrintBooksForSection(split.at(1), split.at(2), split.at(3));
		} else if (command == "GB") {
			commandPrintBook(split.at(1));
		} else if (command == "PB") {
			commandPrintAllBooks();
		} else if (command == "PC") {
			commandPrintAllCourses();
		} else if (command == "PY") {
			int month = stoi(split.at(1).substr(0,2));
			int year = stoi(split.at(1).substr(3,8));
			commandPrintBooksSince(month, year);
		} else if (command == "PD") {
			commandPrintBooksInDepartment(split.at(1));
		} else if (command == "PM") {
			commandPrintAverages(split.at(1));
		} else {
			cout << "Invalid command: '" << command << "'" << endl;
		}
	} catch (const char* error) {
		cerr << error << endl;
	} catch (out_of_range& error) {
		cerr << "Incomplete command: " << input_line << endl;
	}
}

// Entry point to the program, input is ignored so those arguments have been removed
int main() {

	// Continually take input until the program ends
	while (true) {
		string input_line;
		getline(cin, input_line);

		call_command(input_line);
	}
}
