#ifndef COMMAND_HEADER
#define COMMAND_HEADER

#include "book_manager.h"
#include "course_manager.h"


// This object provides a unified interface to issue commands to update and access books and courses.
class CommandManager {
	BookManager books;
	CourseManager courses;

	// These functions represent the commands outlined in the project specification
	// Check the function definitions for more details
public:
	void commandAddBook(string isbn, string title);
	void commandSetBookDetail(string isbn, string mode, string data);
	void commandSetCost(string isbn, int cost, string type);
	void commandAddCourse(string department, string number, string name);
	void commandAddBookToCourse(string isbn, string department, string number, string section, string type);
	void commandPrintBooksForCourse(string department, string number);
	void commandPrintBooksForSection(string department, string number, string section);
	void commandPrintBook(string isbn);
	void commandPrintAllBooks();
	void commandPrintAllCourses();
	void commandPrintBooksSince(int month, int year);
	void commandPrintBooksInDepartment(string department);
	void commandPrintAverages(string department);
};

#endif