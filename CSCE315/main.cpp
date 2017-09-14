#include <iostream>
#include <vector>
#include "command.h"

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
			commandManager.commandAddBook(split.at(1), combine(split, 2));
		} else if (command == "D") {
			commandManager.commandSetBookDetail(split.at(1), split.at(2), combine(split, 3));
		} else if (command == "M") {
			commandManager.commandSetPrice(split.at(1), stod(split.at(2)), split.at(3));
		} else if (command == "C") {
			commandManager.commandAddCourse(split.at(1), split.at(2), combine(split, 3));
		} else if (command == "A") {
			commandManager.commandAddBookToCourse(split.at(1), split.at(2), split.at(3), split.at(4), split.at(5));
		} else if (command == "GC") {
			commandManager.commandPrintBooksForCourse(split.at(1), split.at(2));
		} else if (command == "GS") {
			commandManager.commandPrintBooksForSection(split.at(1), split.at(2), split.at(3));
		} else if (command == "GB") {
			commandManager.commandPrintBook(split.at(1));
		} else if (command == "PB") {
			commandManager.commandPrintAllBooks();
		} else if (command == "PC") {
			commandManager.commandPrintAllCourses();
		} else if (command == "PY") {
			int month = stoi(split.at(1).substr(0,2));
			int year = stoi(split.at(1).substr(3,8));
			commandManager.commandPrintBooksSince(month, year);
		} else if (command == "PD") {
			commandManager.commandPrintBooksInDepartment(split.at(1));
		} else if (command == "PM") {
			commandManager.commandPrintAverages(split.at(1));
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
	// Create global command manager object
	CommandManager commandManager;

	// Continually take input until the program ends
	while (true) {
		string input_line;
		getline(cin, input_line);

		call_command(commandManager, input_line);
	}
}
