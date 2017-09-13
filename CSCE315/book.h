#ifndef BOOK_HEADER
#define BOOK_HEADER

#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct Book {
public:
	string isbn = "";
	string title = "";
	string author = "";
	int edition = 0;
	int publication_month = 0;
	int publication_year = 0;

	double cost_new = 0;
	double cost_used = 0;
	double cost_rented = 0;
	double cost_electronic = 0;
};

struct BookManager {
	vector<Book> books;

	Book& get(string isbn);
	Book& getOrCreate(string isbn);
};

ostream& operator<<(ostream& out, const Book& book);

#endif
