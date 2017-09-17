#ifndef COURSE_MANAGER_HEADER
#define COURSE_MANAGER_HEADER

#include "course.h"

// Define a structure to store known courses
struct CourseManager {
	vector<Course> courses;
	Course& get(string department, string number);
	Course& getOrCreate(string department, string number);

	vector<Book> getBooksInDepartment(string department);

	vector<Course> getCoursesInDepartment(string department);
};

#endif