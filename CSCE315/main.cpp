#include <iostream>
#include <vector>
#include <limits>
#include "book.h"
#include "course.h"

using namespace std;

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

int main(int argc, char** argv) {
	BookManager books;
	CourseManager courses;

	while (true) {
		string input;
		getline(cin, input);

		vector<string> split;
		string current;
		for (char i : input) {
			if (i == ' ') {
				split.push_back(current);
				current = "";
			} else {
				current += i;
			}
		}
		if (current.length() != 0) {
			split.push_back(current);
		}
		
		if (split.empty()) {
			continue;
		}
	
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
