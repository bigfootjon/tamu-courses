#include <iostream>
#include <vector>
#include "book.h"
#include "course.h"

string combine(vector<string> split, unsigned int initial) {
    string title;
    for (unsigned i = initial; i < split.size(); ++i) {
        if (i != initial) {
            title += " ";
        }
        title += split.at(i);
    }
    return title;
}

using namespace std;

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
                Course& course = courses.getOrCreate(split.at(2), split.at(3));
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
				cout << "Title: " << book.title << endl;
                cout << "Author: " << book.author << endl;
                cout << "Edition: " << book.edition << endl;
                cout << "Publication Date: " << book.publication_month << "/" << book.publication_year << endl;
                cout << "Cost (new): " << book.cost_new << endl;
                cout << "Cost (used): " << book.cost_used << endl;
                cout << "Cost (rented): " << book.cost_rented << endl;
                cout << "Cost (electronic): " << book.cost_electronic << endl;
			} else if (command == "PB") {
                for (auto& book : books.books) {
                    cout << book.title << endl;
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
                        cout << book.title << endl;
                    }
                }
			} else if (command == "PD") {
                vector<Book> departmentBooks = courses.getBooksInDepartment(split.at(1));
                for (auto& book : departmentBooks) {
                    cout << book.title << endl;
                }
			} else if (command == "PM") {
                vector<Book> departmentBooks = courses.getBooksInDepartment(split.at(1));
                int count = 0;
                double max_double = numeric_limits<double>::max();
                double min_double = numeric_limits<double>::min();

                double max_total = 0;
                double min_total = 0;
                for (auto& book : departmentBooks) {
                    double min = max_double;
                    double max = min_double;
                    if (book.cost_new < min) min = book.cost_new;
                    if (book.cost_used < min) min = book.cost_used;
                    if (book.cost_rented < min) min = book.cost_rented;
                    if (book.cost_electronic < min) min = book.cost_electronic;

                    if (book.cost_new > max) max = book.cost_new;
                    if (book.cost_used > max) max = book.cost_used;
                    if (book.cost_rented > max) max = book.cost_rented;
                    if (book.cost_electronic > max) max = book.cost_electronic;

                    if (min != 0) {
                        min_total += min;
                    }
                    if (max != 0) {
                        max_total += max;
                    }
                    if (max != 0 || min != 0) {
                        ++count;
                    }
                }

                cout << "Average (MIN): " << min_total <<
                        "Average (MAX): " << max_total << endl;
			} else {
				cout << "Invalid command: '" << command << "'" << endl;
                break;
			}
		} catch (const char* error) {
			cerr << error << endl;
		}
	}
}
