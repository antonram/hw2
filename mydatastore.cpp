#include "mydatastore.h"
#include "util.h"
#include <string>
#include <map>

MyDataStore::~MyDataStore() {

		for(size_t i = 0; i < cart_.size(); i++) {
			delete cart_[i];
		}

		for(size_t i = 0; i < users_.size(); i++) {
			delete users_[i];
		}


}

MyDataStore::MyDataStore() {}

// add product to the cart vector
void MyDataStore::addProduct(Product* p) {
	cart_.push_back(p);
}

//adds user to the data store's user vector
void MyDataStore::addUser(User* u) {
	users_.push_back(u);

}


std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
	//define set to hold the terms
	std::vector<Product*> Results;

	std::set<std::string> termSet;
	// iterate through terms to convert from vector into set
	for(size_t i = 0; i < terms.size(); ++i) {
		termSet.insert(terms.at(i));
	}

	//AND case
	if(type == 0) {
		//iterate through list of products
		for(size_t i = 0; i < cart_.size(); ++i) {
			//retrieve each product
			Product* prod = cart_.at(i);
			//find intersection
			std::set<std::string> keywordSet = prod->keywords();
			std::set<std::string> intersect = setIntersection(termSet, keywordSet);
			//if ALL words in product
			if(intersect.size() == termSet.size()) {
				//add product to result
				Results.push_back(prod);
			}
		}
	}


	//OR case
	if(type == 1) {
		//iterate through list of products
		for(size_t i = 0; i < cart_.size(); ++i) {
			//retrieve each product
			Product* prod = cart_.at(i);
			//find union
			std::set<std::string> keywordSet = prod->keywords();
			std::set<std::string> unionSet = setUnion(termSet, keywordSet);
			//if AT LEAST ONE word in product
			if(unionSet.size() > 0) {
				//add product to result
				Results.push_back(prod);
			}
		}

	}



	return Results;


}

void MyDataStore::dump(std::ostream& ofile) {


	ofile << "<products>" << std::endl;
	// fetch list of products
	for(size_t i = 0; i < cart_.size(); ++i) {
		// output the info of each product
		cart_.at(i)->dump(ofile);
	}
	ofile << "</products>" << std::endl;

	ofile << "<users>" << std::endl;
	// fetch list of users
	for(size_t i = 0; i < users_.size(); ++i) {
		//output info of each user
		users_.at(i)->dump(ofile);
	}
	ofile << "</users>" << std::endl;

}

std::vector<User*> MyDataStore::getUsers() {
	return users_;
}

std::vector<Product*> MyDataStore::getCart() {
	return cart_;
}

std::map<std::string, std::vector<Product*>> MyDataStore::getUserCart() {
	return userCart_;
}


void MyDataStore::addToUserCart(std::string username, Product* product) {
	// if no info for the username yet...
	if(userCart_.find(username) == userCart_.end()) {
		std::vector<Product*> products;
		products.push_back(product);
		userCart_[username] = products;
	}
	else {
		userCart_[username].push_back(product);
	}
}

	void MyDataStore::removeFromCart(std::string username, std::size_t index) {
		//if username exists
		if(userCart_.find(username) != userCart_.end()) {
			//if within bounds
			
			if(index < userCart_[username].size()) {
				std::vector<Product*> temp;
				// we add all values we still want into temp
				for(size_t i = 0; i < userCart_[username].size(); ++i) {
					if(index != i) {
						temp.push_back(userCart_[username][i]);
					}
				} 
			
				//wipe contents of user cart
			
				size_t size = userCart_[username].size();
				for(size_t i = 0; i < size; i++) {
						userCart_[username].pop_back();
				} 

				for(size_t i = 0; i < temp.size(); i++) {
						userCart_[username].push_back(temp[i]);
				}
			}
		}
	}