#ifndef BOOK_HEADER
#define BOOK_HEADER

#include <string>
#include <vector>

using namespace std;

class Book {
	public:
	string isbn = "";
	string title = "";
	string author = "";
	int edition = 0;
	int publication_month = 0;
	int publication_year = 0;
};

class BookManager {
	private:
	vector<Book> books;

	public:
	Book& get(string isbn);
	Book& getOrCreate(string isbn);
};

#endif
