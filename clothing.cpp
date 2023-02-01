#include "product.h"
#include "clothing.h"
#include "util.h"
#include <iomanip>

using namespace std;

Clothing::Clothing (const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand) : 
Product(category, name, price, qty),
size_(size),
brand_(brand)
{

}

Clothing::~Clothing() 
{

}

std::set<std::string> Clothing::keywords() const {
	//create set to return
	set<std::string> keywords;
	//in set, insert keywords from name
	keywords = parseStringToWords(name_);
	//create new set to hold keywords from brand name
	set<std::string> brand_keywords = parseStringToWords(brand_);
	//set keywords = union of name keywords and brand keywords
	keywords = setUnion(keywords, brand_keywords);
	//return set
	return keywords;
}

std::string Clothing:: displayString() const {
	//create string to return and add each data member value as a string to the return string 
	std::string ret_val = "";
	ret_val += name_;
	ret_val += "\n";
	ret_val += "Size: ";
	ret_val += size_;
	ret_val += " Brand: ";
	ret_val += brand_;
	ret_val += "\n";
	ret_val += std::to_string(price_);
	ret_val += " ";
	ret_val += std::to_string(qty_); 
	ret_val += " left.";
	return ret_val;
}

void Clothing::dump(std::ostream& os) const {
		//use Product's dump function and account for additional size and brand data members
	Product::dump(os);
	os << size_ << "\n" << brand_ << endl;
}