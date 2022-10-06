#ifndef MOVIE_H
#define MOVIE_H
#include "product.h"
#include "util.h"


class Movie : public Product {
	public:
		Movie(const std::string genre, const std::string rating, const std::string name, double price, int qty);
		
		~Movie();

		std::set<std::string> keywords() const;

		std::string displayString() const;

		void dump(std::ostream& os) const;

		std::string getGenre() const;

		std::string getRating() const;

		std::string category() const;

	protected:
		std::string genre_;
    std::string rating_;
};
#endif