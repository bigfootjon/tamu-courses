#ifndef MAIN_HEADER
#define MAIN_HEADER

#include <string>
#include <vector>

using namespace std;

class Book {
	private:
	string isbn;
	string title;
	
	public:
	void setIsbn(string isbn);
	string getIsbn();

	void setTitle(string title);
	string getTitle();
};

class BookManager {
	private:
	vector<Book> books;

	public:
	Book get(string isbn);
	Book getOrCreate(string isbn);
};

class Course {

};

#endif
