#include "book_manager.h"
#include "course_manager.h"

struct CommandManager {
	BookManager books;
	CourseManager courses;

	void commandAddBook(string isbn, string title);
	void commandSetBookDetail(string isbn, const string mode, string data);
	void commandSetPrice(string isbn, double cost, const string type);
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