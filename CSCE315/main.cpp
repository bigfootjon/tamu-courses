#include <iostream>
#include <vector>
#include "book.h"

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
			} else if (command == "C") {
			} else if (command == "A") {
			} else if (command == "GC") {
			} else if (command == "GS") {
			} else if (command == "GB") {
				Book book = books.get(split.at(1));
				cout << '"' << book.title << '"' << endl;
                cout << book.author << endl;
                cout << book.edition << endl;
                cout << book.publication_month << "/" << book.publication_year << endl;
			} else if (command == "PB") {
			} else if (command == "PC") {
			} else if (command == "PY") {
			} else if (command == "PD") {
			} else if (command == "PM") {
			} else {
				cout << "Invalid command: '" << command << "'" << endl;
                break;
			}
		} catch (const char* error) {
			cerr << error << endl;
		}
	}
}
