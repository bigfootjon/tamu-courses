#include <iostream>
#include <vector>
#include "command.h"
#include "main.h"

using namespace std;


// Many commands require a few arguments separated by spaces and then the rest of input is combined as the final argument
// For example, in the command "A 1234567890123 A book about books" the text "A book about books" is treated as a single
//     argument to the command.
// This function takes the input (as a vector split up by spaces) and the index of the first argument to combine.
// It then returns all the strings from that index to the end of the input vector and joins them with spaces
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

void call_command(CommandManager& commandManager, string input_line) {
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
	if (current.length() != 0) {
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
			string& isbn = split.at(1);
			string title = combine(split, 2);

			commandManager.commandAddBook(isbn, title);
		} else if (command == "D") {
			string& isbn = split.at(1);
			string& mode = split.at(2);
			string data = combine(split, 3);

			commandManager.commandSetBookDetail(isbn, mode, data);
		} else if (command == "M") {
			string& isbn = split.at(1);
			double cost = stod(split.at(2));
			string& type = split.at(3);

			auto cost_cents = static_cast<int>(cost * 100);

			commandManager.commandSetCost(isbn, cost_cents, type);
		} else if (command == "C") {
			string& department = split.at(1);
			string& number = split.at(2);
			string name = combine(split, 3);

			commandManager.commandAddCourse(department, number, name);
		} else if (command == "A") {
			string& isbn = split.at(1);
			string& department = split.at(2);
			string& number = split.at(3);
			string& section = split.at(4);
			string& type = split.at(5);

			commandManager.commandAddBookToCourse(isbn, department, number, section, type);
		} else if (command == "GC") {
			string& department = split.at(1);
			string& number = split.at(2);

			commandManager.commandPrintBooksForCourse(department, number);
		} else if (command == "GS") {
			string& department = split.at(1);
			string& number = split.at(2);
			string& section = split.at(3);

			commandManager.commandPrintBooksForSection(department, number, section);
		} else if (command == "GB") {
			string& isbn = split.at(1);

			commandManager.commandPrintBook(isbn);
		} else if (command == "PB") {
			commandManager.commandPrintAllBooks();
		} else if (command == "PC") {
			commandManager.commandPrintAllCourses();
		} else if (command == "PY") {
			int month = stoi(split.at(1).substr(0,2));
			int year = stoi(split.at(1).substr(3,8));

			if (month < 0 || month > 12) {
				throw InvalidCommand("Month must be in the range 01 <= X <= 12");
			}

			commandManager.commandPrintBooksSince(month, year);
		} else if (command == "PD") {
			string& department = split.at(1);

			commandManager.commandPrintBooksInDepartment(department);
		} else if (command == "PM") {
			string& department = split.at(1);

			commandManager.commandPrintAverages(department);
		} else {
			cout << "Invalid command: '" << command << "'" << endl;
		}
	} catch (InvalidCommand& exception) {
		cerr << exception.what() << endl;
	} catch (out_of_range& error) {
		cerr << "Incomplete command: " << input_line << endl;
	}
}

// Entry point to the program, input is ignored so those arguments have been removed
int main() {
	// Create global command manager object
	CommandManager commandManager;

	// Continually take input until the program ends
	while (true) {
		string input_line;
		getline(cin, input_line);

		call_command(commandManager, input_line);
	}
}
