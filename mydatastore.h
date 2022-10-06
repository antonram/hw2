#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <vector>
#include <queue>
#include <map>
#include "product.h"
#include "user.h"
#include "datastore.h"

/**
 * DataStore Interface needed for parsing and instantiating products and users
 *
 * A derived version of the DataStore can provide other services as well but
 * must support those below
 *
 * DO NOT EDIT
 */


class MyDataStore : public DataStore{
public:
    ~MyDataStore();

		MyDataStore();

    /**
     * Adds a product to the data store
     */
    void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
    void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile);

		std::vector<User*> getUsers();

		std::vector<Product*> getCart();

		std::map<std::string, std::vector<Product*>> getUserCart();

		void removeFromCart(std::string username, std::size_t index);

		void addToUserCart(std::string username, Product* product);

	private:
		std::vector<Product*> cart_;
		std::vector<User*> users_;
		std::map<std::string, std::vector<Product*>> userCart_;


};

#endif
