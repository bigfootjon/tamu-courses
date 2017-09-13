#include <string>
#include "course.h"

using namespace std;

void Course::addBookForSection(Book &book, string section, bool required) {
	BookBinding binding;
	binding.book = book;
	binding.section = section;
	binding.required = required;
	books.push_back(binding);
}
