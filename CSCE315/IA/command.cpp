#include <unordered_map>
#include "command.h"
#include "main.h"


// Implements "B <ISBN> <title>" command
void CommandManager::commandAddBook(string isbn, string title) {
	Book& book = books.getOrCreate(isbn);
	book.title = title;
}

// Implements "D <ISBN> <A | E | D> <value>" command
void CommandManager::commandSetBookDetail(string isbn, const string mode, string data) {
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
		throw InvalidCommand("Command mode not recognized");
	}
}

// Implements "M <ISBN> <cost> <N | U | R | E>" command
void CommandManager::commandSetCost(string isbn, int cost, const string type) {
	Book& book = books.get(isbn);
	if (type == "N") {
		book.cost_new_cents = cost;
	} else if (type == "U") {
		book.cost_used_cents = cost;
	} else if (type == "R") {
		book.cost_rented_cents = cost;
	} else if (type == "E") {
		book.cost_electronic_cents = cost;
	} else {
		throw InvalidCommand("Invalid cost type");
	}
}

// Implements "C <department> <number> <name>" command
void CommandManager::commandAddCourse(string department, string number, string name) {
	Course& course = courses.getOrCreate(department, number);
	course.name = name;
}

// Implements "A <ISBN> <department> <number> <section> <R | O>" command
void CommandManager::commandAddBookToCourse(string isbn, string department, string number, string section, string type) {
	Book& book = books.get(isbn);
	Course& course = courses.get(department, number);
	bool required;
	if (type == "R") {
		required = true;
	} else if (type == "O") {
		required = false;
	} else {
		throw InvalidCommand("Invalid selection for R/O");
	}
	course.addBookForSection(book, section, required);
}

// Implements "GC <department> <number>" command
void CommandManager::commandPrintBooksForCourse(string department, string number) {
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

// Implements "GS <department> <number> <section>" command
void CommandManager::commandPrintBooksForSection(string department, string number, string section) {
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

// Implements "GB <ISBN>" command
void CommandManager::commandPrintBook(string isbn) {
	Book book = books.get(isbn);
	cout << book << endl;
}

// Implements "PB" command
void CommandManager::commandPrintAllBooks() {
	for (auto& book : books.books) {
		cout << book << endl;
	}
}

// Implements "PC" command
void CommandManager::commandPrintAllCourses() {
	for (auto& course : courses.courses) {
		cout << course.department << " " << course.number << endl;
	}
}

// Implements "PY <MM/YYYY>" command
void CommandManager::commandPrintBooksSince(int month, int year) {
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

// Implements "PD <department>" command
void CommandManager::commandPrintBooksInDepartment(string department) {
	vector<Book> departmentBooks = courses.getBooksInDepartment(department);
	for (auto& book : departmentBooks) {
		cout << book << endl;
	}
}

// Implements "PM <department>" command
void CommandManager::commandPrintAverages(string department) {
	vector<Course> departmentCourses = courses.getCoursesInDepartment(department);

	// Map definition
	// key is "<number>-<section>"
	// value is a vector of books (required only for the first map, and all books for the second)
	unordered_map<string, vector<Book>> mapRequiredBooks;
	unordered_map<string, vector<Book>> mapAllBooks;

	for (Course& course : departmentCourses) {
		for (Course::BookBinding& bookBinding : course.books) {
			string key = course.number + "-" + bookBinding.section;

			vector<Book>& sectionRequiredBooks = mapRequiredBooks[key];
			if (bookBinding.required) {
				sectionRequiredBooks.push_back(bookBinding.book);
			}

			vector<Book>& sectionAllBooks = mapAllBooks[key];
			sectionAllBooks.push_back(bookBinding.book);
		}
	}

	// Map definition
	// key is "<number>-<section>"
	// value is cost to buy all books for this section (required only for the first map, and all books for the second)
	unordered_map<string, int> mapRequiredCost;
	unordered_map<string, int> mapFullCost;

	for (auto pair : mapRequiredBooks) {
		vector<Book> requiredBooks = pair.second;
		int total = 0;
		for (Book& book : requiredBooks) {
			total += book.lowestCostCents();
		}
		mapRequiredCost[pair.first] = total;
	}

	for (auto pair : mapAllBooks) {
		vector<Book> allBooks = pair.second;
		int total = 0;
		for (Book& book : allBooks) {
			total += book.highestCostCents();
		}
		mapFullCost[pair.first] = total;
	}

	int requiredCostAverage = 0;
	int fullCostAverage = 0;

	for (auto pair : mapRequiredCost) {
		requiredCostAverage += pair.second;
	}

	for (auto pair : mapFullCost) {
		fullCostAverage += pair.second;
	}

	requiredCostAverage /= mapRequiredCost.size();
	fullCostAverage /= mapFullCost.size();

	int requiredCostAverageDollars = requiredCostAverage / 100;
	int requiredCostAverageCents = requiredCostAverage % 100;

	int fullCostAverageDollars = fullCostAverage / 100;
	int fullCostAverageCents = fullCostAverage % 100;

	cout << "Minimum cost: " << requiredCostAverageDollars << "." << requiredCostAverageCents << endl
		 << "Maximum cost: " << fullCostAverageDollars << "." << fullCostAverageCents << endl;
}
