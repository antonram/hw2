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
	return name_ + "\n" + "Genre: " + genre_ + " Rating: " + rating_ + "\n" + to_string(price_) + " " + to_string(qty_) + " left.";
}

void Movie::dump(ostream& os) const {
	os << category() << std::endl;
	os << getName() << std::endl;
	os << to_string(getPrice()) << std::endl;
	os << to_string(getQty()) << std::endl;
	os << getGenre() << std::endl;
	os << getRating() << std:: endl;
}

string Movie::getGenre() const {
	return genre_;
}

string Movie::getRating() const {
	return rating_;
}

string Movie::category() const {
	return "movie";
}