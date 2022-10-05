#include "movie.h"

using namespace std;

// for constructor, we first instantiate Book specific data members, then call the product constructor.
Movie::Movie(const string genre, const string rating, const std::string name, double price, int qty):
	Product(category(), name, price, qty)
{
	genre_ = genre;
	rating_ = rating;

}

Movie::~Movie(){}

set<string> Movie::keywords() const {
	set<string> Results;
	set<string> ResultsProd = parseStringToWords(getName());
	set<string> ResultsGenre = parseStringToWords(getGenre());
	set<string>::iterator itr;

// insert product name as keywords
	for(itr = ResultsProd.begin(); itr != ResultsProd.end(); ++itr) {
		Results.insert(*itr);
	}

	// insert author name as keywords
	for(itr = ResultsGenre.begin(); itr != ResultsGenre.end(); ++itr) {
		Results.insert(*itr);
	}

	// return the resulting set.
	return Results;

}

string Movie::displayString() const {
	return "qty: " + to_string(qty_) + ", name: " + name_ + ", rating: " + rating_ + ", genre: " + genre_ + ", price: " + to_string(price_);
}

void Movie::dump(ostream& os) const {
	os << qty_ << name_ << rating_ << genre_ << price_;
}

string Movie::getGenre() const {
	return genre_;
}

string Movie::getRating() const {
	return rating_;
}

const string Movie::category() {
	return "movie";
}