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

	int cost_new_cents = 0;
	int cost_used_cents = 0;
	int cost_rented_cents = 0;
	int cost_electronic_cents = 0;

	int lowestCostCents();
	int highestCostCents();
};

// Declare output operator for Book objects
ostream& operator<<(ostream& out, const Book& book);

#endif
