#ifndef BOOK_HEADER
#define BOOK_HEADER

#include <string>
#include <vector>

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

class BookManager {
	vector<Book> books;

public:
	Book& get(string isbn);
	Book& getOrCreate(string isbn);
};

#endif
