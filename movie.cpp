#include "product.h"
#include "movie.h"
#include "util.h"
#include <iomanip>

using namespace std;

Movie::Movie (const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating) : 
Product(category, name, price, qty),
genre_(genre),
rating_(rating)
{

}

Movie::~Movie() 
{

}

std::set<std::string> Movie::keywords() const{
	set<std::string> keywords;
	keywords = parseStringToWords(name_);
	set<std::string> genre_keywords = parseStringToWords(genre_);
	keywords = setUnion(keywords, genre_keywords);
	return keywords;
}

std::string Movie:: displayString() const {
	std::string ret_val = "";
	ret_val += name_;
	ret_val += "\n";
	ret_val += "Genre: ";
	ret_val += genre_;
	ret_val += " Rating: ";
	ret_val += rating_;
	ret_val += "\n";
	ret_val += std::to_string(price_);
	ret_val += " ";
	ret_val += std::to_string(qty_); 
	ret_val += " left.";
	return ret_val;
}

void Movie::dump(std::ostream& os) const {
	Product::dump(os);
	os << genre_ << "\n" << rating_ << endl;
}