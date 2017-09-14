#include "course_manager.h"
#include "main.h"

// Get a course object by its department and number (e.g. CSCE 121)
// Otherwise, throw an exception
Course& CourseManager::get(const string department, const string number) {
	// Iterate through all known courses
	for (auto& course : courses) {
		// If the department and number match, return that course
		if (course.department == department && course.number == number) {
			return course;
		}
	}
	// If no courses match, throw an error
	throw InvalidCommand("No course exists with that department and number");
}

// Get a course object by its department and number (e.g. CSCE 121)
// Create it if it can't be found
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


// Fetch all books in a given department
vector<Book> CourseManager::getBooksInDepartment(string department) {
	vector<Book> books;
	// Iterate through known courses
	for (auto& course : courses) {
		// If the department matches, add the books from that courses
		if (course.department == department) {
			// Iterate through the books in the course
			for (auto& new_book : course.books) {
				// Make sure the book is not already included in the book vector
				bool alreadyIncluded = false;
				for (auto& book : books) {
					if (new_book.book.isbn == book.isbn) {
						alreadyIncluded = true;
						break;
					}
				}
				// If it isn't, add it
				if (!alreadyIncluded) {
					books.push_back(new_book.book);
				}
			}
		}
	}
	return books;
}

vector<Course> CourseManager::getCoursesInDepartment(string department) {
	vector<Course> courses;
	for (Course& course : courses) {
		if (course.department == department) {
			courses.push_back(course);
		}
	}
	return courses;
}
