#ifndef COURSE_HEADER
#define COURSE_HEADER

#include <string>
#include <vector>
#include "book.h"

using namespace std;

struct Course {
    string department = "";
    string number = "";
    string name = "";

    struct BookBinding {
        Book book;
        string section;
        bool required;
    };

    vector<BookBinding> books{};
    void addBookForSection(Book& book, string section, bool required);
};

class CourseManager {
private:
    vector<Course> courses;
public:
    Course& get(string department, string number);
    Course& getOrCreate(string department, string number);
};

#endif