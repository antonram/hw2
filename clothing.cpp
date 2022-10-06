#include "clothing.h"

using namespace std;

// for constructor, we first instantiate Book specific data members, then call the product constructor.
Clothing::Clothing(const string size, const string brand, const std::string name, double price, int qty):
	Product(category(), name, price, qty)
{
	size_ = size;
	brand_ = brand;

}

Clothing::~Clothing(){}

set<string> Clothing::keywords() const {
	set<string> Results;
	set<string> ResultsProd = parseStringToWords(getName());
	set<string> ResultsBrand = parseStringToWords(getBrand());
	set<string>::iterator itr;

// insert product name as keywords
	for(itr = ResultsProd.begin(); itr != ResultsProd.end(); ++itr) {
		Results.insert(*itr);
	}

	// insert author name as keywords
	for(itr = ResultsBrand.begin(); itr != ResultsBrand.end(); ++itr) {
		Results.insert(*itr);
	}

	// return the resulting set.
	return Results;


}

string Clothing::displayString() const {
	return name_ + "\n" + "Size: " + size_ + " Brand: " + brand_ + "\n" + to_string(price_) + " " + to_string(qty_) + " left.";
}

void Clothing::dump(ostream& os) const {
	os << category() << std::endl;
	os << getName() << std::endl;
	os << to_string(getPrice()) << std::endl;
	os << to_string(getQty()) << std::endl;
	os << getSize() << std::endl;
	os << getBrand() << std:: endl;
}

string Clothing::getSize() const {
	return size_;
}

string Clothing::getBrand() const {
	return brand_;
}

string Clothing::category() const {
	return "clothing";
}