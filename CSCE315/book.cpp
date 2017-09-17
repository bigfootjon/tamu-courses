#include "book.h"

using namespace std;

// Enable printing of Book objects to an output stream
// E.g. std::cout << book << std::endl;
ostream& operator<<(ostream& out, const Book& book) {
	// Always print the ISBN
	out << "ISBN: " << book.isbn;
	// If the title is not blank, print it
	if (!book.title.empty()) {
		out << endl << "- Title: " << book.title;
	}
	// If the author has been set, print it
	if (!book.author.empty()) {
		out  << endl << "- Author: " << book.author;
	}
	// If the edition has been set, print it
	if (book.edition != 0) {
		out  << endl << "- Edition: " << book.edition;
	}
	// If the publication date has been set, print it
	if (book.publication_month != 0 && book.publication_year != 0) {
		out  << endl << "- Publication Date: " << book.publication_month << "/" << book.publication_year;
	}
	// If the cost of a new book has been set, print it
	if (book.cost_new_cents != 0) {
		int dollars = book.cost_new_cents / 100;
		int cents = book.cost_new_cents % 100;
		out  << endl << "- Cost (new): " << dollars << "." << cents;
	}
	// If the cost of an used book has been set, print it
	if (book.cost_used_cents != 0) {
		int dollars = book.cost_used_cents / 100;
		int cents = book.cost_used_cents % 100;
		out  << endl << "- Cost (used): " << dollars << "." << cents;
	}
	// If the cost of a rented book has been set, print it
	if (book.cost_rented_cents != 0) {
		int dollars = book.cost_rented_cents / 100;
		int cents = book.cost_rented_cents % 100;
		out  << endl << "- Cost (rented): " << dollars << "." << cents;
	}
	// If the cost of a electronic book has been set, print it
	if (book.cost_electronic_cents != 0) {
		int dollars = book.cost_electronic_cents / 100;
		int cents = book.cost_electronic_cents % 100;
		out  << endl << "- Cost (electronic): " << dollars << "." << cents;
	}
	return out;
}

int Book::lowestCostCents() {
	int lowestCost = numeric_limits<int>::max();
	if (cost_new_cents < lowestCost && cost_new_cents != 0) {
		lowestCost = cost_new_cents;
	}
	if (cost_used_cents < lowestCost && cost_used_cents != 0) {
		lowestCost = cost_used_cents;
	}
	if (cost_rented_cents < lowestCost && cost_rented_cents != 0) {
		lowestCost = cost_rented_cents;
	}
	if (cost_electronic_cents < lowestCost && cost_electronic_cents != 0) {
		lowestCost = cost_electronic_cents;
	}
	return lowestCost;
}

int Book::highestCostCents() {
	int highestCost = numeric_limits<int>::min();
	if (cost_new_cents > highestCost && cost_new_cents != 0) {
		highestCost = cost_new_cents;
	}
	if (cost_used_cents > highestCost && cost_used_cents != 0) {
		highestCost = cost_used_cents;
	}
	if (cost_rented_cents > highestCost && cost_rented_cents != 0) {
		highestCost = cost_rented_cents;
	}
	if (cost_electronic_cents > highestCost && cost_electronic_cents != 0) {
		highestCost = cost_electronic_cents;
	}
	return highestCost;
}
