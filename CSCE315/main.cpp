#include <iostream>
#include <vector>
#include <string>

using namespace std;

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
		
		string command = split[0];
		if (command == "B") {

		} else if (command == "D") {
		} else if (command == "M") {
		} else if (command == "C") {
		} else if (command == "A") {
		} else if (command == "GC") {
		} else if (command == "GS") {
		} else if (command == "GB") {
		} else if (command == "PB") {
		} else if (command == "PC") {
		} else if (command == "PY") {
		} else if (command == "PD") {
		} else if (command == "PM") {
		} else {
			// TODO: Handle invalid command
		}
	}
}
