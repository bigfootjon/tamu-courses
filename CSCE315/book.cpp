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
	if (book.cost_new != 0) {
		out  << endl << "- Cost (new): " << book.cost_new;
	}
	// If the cost of an used book has been set, print it
	if (book.cost_used != 0) {
		out  << endl << "- Cost (used): " << book.cost_used;
	}
	// If the cost of a rented book has been set, print it
	if (book.cost_rented != 0) {
		out  << endl << "- Cost (rented): " << book.cost_rented;
	}
	// If the cost of a electronic book has been set, print it
	if (book.cost_electronic != 0) {
		out  << endl << "- Cost (electronic): " << book.cost_electronic;
	}
	return out;
}

double Book::lowestCost() {
	double lowestCost = numeric_limits<double>::max();
	if (cost_new < lowestCost && cost_new != 0) {
		lowestCost = cost_new;
	}
	if (cost_used < lowestCost && cost_used != 0) {
		lowestCost = cost_used;
	}
	if (cost_rented < lowestCost && cost_rented != 0) {
		lowestCost = cost_rented;
	}
	if (cost_electronic < lowestCost && cost_electronic != 0) {
		lowestCost = cost_electronic;
	}
	return lowestCost;
}

double Book::highestCost() {
	double highestCost = numeric_limits<double>::min();
	if (cost_new > highestCost && cost_new != 0) {
		highestCost = cost_new;
	}
	if (cost_used > highestCost && cost_used != 0) {
		highestCost = cost_used;
	}
	if (cost_rented > highestCost && cost_rented != 0) {
		highestCost = cost_rented;
	}
	if (cost_electronic > highestCost && cost_electronic != 0) {
		highestCost = cost_electronic;
	}
	return highestCost;
}
