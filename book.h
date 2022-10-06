#ifndef BOOK_H
#define BOOK_H
#include "product.h"
#include "util.h"


class Book : public Product {
	public:
		Book(const std::string author, const std::string isbn, const std::string name, double price, int qty);
		
		~Book();

		std::set<std::string> keywords() const;

		std::string displayString() const;

		void dump(std::ostream& os) const;

		std::string getIsbn() const;

		std::string getAuthor() const;

		std::string category() const;

	protected:
		std::string isbn_;
    std::string author_;
};
#endif