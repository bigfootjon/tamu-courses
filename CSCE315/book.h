#ifndef BOOK_HEADER
#define BOOK_HEADER

#include <string>
#include <vector>
#include <iostream>

using namespace std;

// This struct is used for storing all information about a book
struct Book {
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

	double lowestCost();
	double highestCost();
};

// Declare output operator for Book objects
ostream& operator<<(ostream& out, const Book& book);

#endif
