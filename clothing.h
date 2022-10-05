#ifndef CLOTHING_H
#define CLOTHING_H
#include "product.h"
#include "util.h"


class Clothing : public Product {
	public:
		Clothing(const std::string size, const std::string brand, const std::string name, double price, int qty);
		
		~Clothing();

		std::set<std::string> keywords() const;

		std::string displayString() const;

		void dump(std::ostream& os) const;

		std::string getSize() const;

		std::string getBrand() const;

		const std::string category();

	protected:
		std::string size_;
    std::string brand_;
};
#endif