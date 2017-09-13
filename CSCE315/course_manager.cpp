#include "course_manager.h"

Course& CourseManager::get(const string department, const string number) {
	for (auto& course : courses) {
		if (course.department == department && course.number == number) {
			return course;
		}
	}
	throw "No course exists with that department and number";
}

Course& CourseManager::getOrCreate(string department, string number) {
	// Attempt to get from known books
	try {
		return get(department, number);
	} catch (const char*) {
		// Create if not found
		Course new_course;
		new_course.department = department;
		new_course.number = number;
		courses.push_back(new_course);
		return get(department, number);
	}
}

vector<Book> CourseManager::getBooksInDepartment(string department) {
	vector<Book> books;
	for (auto& course : courses) {
		if (course.department == department) {
			for (auto& new_book : course.books) {
				bool alreadyIncluded = false;
				for (auto& book : books) {
					if (new_book.book.isbn == book.isbn) {
						alreadyIncluded = true;
						break;
					}
				}
				if (!alreadyIncluded) {
					books.push_back(new_book.book);
				}
			}
		}
	}
	return books;
}