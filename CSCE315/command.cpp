#import "command.h"


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
		cout << "Command mode '" << mode << "' not recognized";
	}
}

// Implements "M <ISBN> <cost> <N | U | R | E>" command
void CommandManager::commandSetCost(string isbn, double cost, const string type) {
	Book& book = books.get(isbn);
	if (type == "N") {
		book.cost_new = cost;
	} else if (type == "U") {
		book.cost_used = cost;
	} else if (type == "R") {
		book.cost_rented = cost;
	} else if (type == "E") {
		book.cost_electronic = cost;
	} else {
		throw "Invalid cost type";
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
		throw "Invalid selection for R/O";
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
	vector<Book> departmentBooks = courses.getBooksInDepartment(department);
	cout << "TODO This command has not been implemented" << endl;
}