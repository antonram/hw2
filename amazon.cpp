#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>
#include <algorithm>
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "mydatastore.h"

using namespace std;
struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};
void displayProducts(vector<Product*>& hits);

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    /****************
     * Declare your derived DataStore object here replacing
     *  DataStore type to your derived type
     ****************/
    MyDataStore ds;



    // Instantiate the individual section and product parsers we want
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;

    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);

    // Now parse the database to populate the DataStore
    if( parser.parse(argv[1], ds) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    }

    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term ...                   " << endl;
    cout << "  ADD username search_hit_number     " << endl;
    cout << "  VIEWCART username                  " << endl;
    cout << "  BUYCART username                   " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "====================================" << endl;

    vector<Product*> hits;
    bool done = false;
    while(!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin,line);
        stringstream ss(line);
        string cmd;
        if((ss >> cmd)) {
            
            if( cmd == "AND") {
              string term;
              vector<string> terms;
              while(ss >> term) {
                  term = convToLower(term);
                  terms.push_back(term);
              }
              hits = ds.search(terms, 0);
              displayProducts(hits);
            }
            else if ( cmd == "OR" ) {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 1);
                displayProducts(hits);
            }
            else if ( cmd == "QUIT") {
                string filename;
                if(ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile);
                    ofile.close();
                }
                done = true;
            }
	    /* Add support for other commands here */
			else if ( cmd == "ADD") {
                            
            //first we check if both user and hit number exist
            std::vector<User*> userList;
            userList = ds.getUsers();
            bool userFound = false;
            string user;
            ss >> user;
            for(size_t i = 0; i < userList.size(); ++i) {
                if(userList[i]->getName() == user) {
                    userFound = true;
                    break;
                }
            }

            bool hitFound = false;
            size_t hit;
            ss >> hit;

            if(hit <= hits.size() && hit > 0) {
                hitFound = true;
            }

            // if either is invalid, whole operation is invalid
            if(!hitFound || !userFound) {
                cout << "Invalid request" << endl;
            }
            // if both valid, we may begin
            else {
                ds.addToUserCart(user, hits[hit-1]);
            }
                            
		}
		else if ( cmd == "VIEWCART") {
			//we pass in the user whose cart we want to access
            string username;
            ss >> username;
            map<string, vector<Product*>> carts = ds.getUserCart();
						//if no cart matches the user, we return invalid username
            if(carts.find(username) == carts.end()) {
                cout << "Invalid username" << endl;
            }
						// or if the username's cart has been emptied due to purchases, we also do nothing
						else if((carts.find(username))->second.size() == 0) {

						}
						//valid input
            else {
                vector<Product*> products = carts[username];
									//we iterate through the products attributed to the user
                    for(size_t i = 0; i < products.size(); ++i) {
                        cout << to_string(i+1) << ":" << endl;
                        cout << products[i]->displayString() << endl;
                    }
            }

		}
		else if ( cmd == "BUYCART") {
			//we fetch users
            vector<User*> userList = ds.getUsers();
            string username;
            User* user;
            ss >> username;
            bool valid = false;
						//we check if user is valid by finding the name
            for(size_t i = 0; i < userList.size(); ++i) {
                if(userList[i]->getName() == username) {
                    user = userList[i];
                    valid = true;
                    break;
                }
            }
						//if no user found, we don't do anything
            if(!valid) {
                cout << "Invalid username" << endl;
            }
            else {
                size_t index = 0;
								//we access the particular user's cart
                vector<Product*> cart = (ds.getUserCart().find(username))->second;
								//we iterate through the user's products
                for(size_t i = 0; i < cart.size(); ++i) {
									//if user has money and still at least 1 in stock
                    if((user->getBalance() >= cart[i]->getPrice()) && (cart[i]->getQty() > 0)) {
                        user->deductAmount(cart[i]->getPrice());
                        cart[i]->subtractQty(1);
                        ds.removeFromCart(username, index);
                    }
										//if invalid item, we just keep iterating
                    else {
                        index++;
                    }
                } 
            }
						
		}




        else {
            cout << "Unknown command" << endl;
        }
    }

    }
    return 0;
}

void displayProducts(vector<Product*>& hits)
{
    int resultNo = 1;
    if (hits.begin() == hits.end()) {
    	cout << "No results found!" << endl;
    	return;
    }
    std::sort(hits.begin(), hits.end(), ProdNameSorter());
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}
