#include "book.h"

using namespace std;

// for constructor, we first instantiate Book specific data members, then call the product constructor.
Book::Book(const string author, const string isbn, const std::string name, double price, int qty):
	Product(category(), name, price, qty)
{
	isbn_ = isbn;
	author_ = author;

}

Book::~Book(){}

set<string> Book::keywords() const {
	set<string> Results;
	set<string> ResultsProd = parseStringToWords(getName());
	set<string> ResultsAuthor = parseStringToWords(getAuthor());
	set<string>::iterator itr;
	
	// insert isbn as keyword
	Results.insert(getIsbn());

// insert product name as keywords
	for(itr = ResultsProd.begin(); itr != ResultsProd.end(); ++itr) {
		Results.insert(*itr);
	}

	// insert author name as keywords
	for(itr = ResultsAuthor.begin(); itr != ResultsAuthor.end(); ++itr) {
		Results.insert(*itr);
	}

	// return the resulting set.
	return Results;

}

string Book::displayString() const {
	return name_ + "\n" + "Author: " + author_ + " ISBN: " + isbn_ + "\n" + to_string(price_) + " " + to_string(qty_) + " left.";
}

void Book::dump(ostream& os) const {
	os << category() << std::endl;
	os << getName() << std::endl;
	os << to_string(getPrice()) << std::endl;
	os << to_string(getQty()) << std::endl;
	os << getIsbn() << std::endl;
	os << getAuthor() << std:: endl;
}

string Book::getIsbn() const {
	return isbn_;
}

string Book::getAuthor() const {
	return author_;
}

string Book::category() const {
	return "book";
}

