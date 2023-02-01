#include "product.h"
#include "book.h"
#include "util.h"
#include <iomanip>

using namespace std;

//use constructor initialization lists to initalize data members of Book class
Book::Book(const std::string category, const std::string name, double price, int qty, const std::string isbn, const std::string author) :
Product(category, name, price, qty),
isbn_(isbn),
author_(author)
{

}

Book::~Book() 
{
}

std::set<std::string> Book::keywords() const{
	//create set to return
	set<std::string> keywords;
	//in set, insert keywords from name
	keywords = parseStringToWords(name_);
	//create new set to hold keywords from author's name
	set<std::string> author_keywords = parseStringToWords(author_);
	//set keywords = union of name keywords and author keywords
	keywords = setUnion(keywords, author_keywords);
	//add isbn to keywords set
	keywords.insert(isbn_);
	//return set
	return keywords;
}

std::string Book:: displayString() const {
	//create string to return and add each data member value as a string to the return string 
	std::string ret_val = "";
	ret_val += name_;
	ret_val += "\n";
	ret_val += "Author: ";
	ret_val += author_;
	ret_val += " ISBN: ";
	ret_val += isbn_;
	ret_val += "\n";
	ret_val += std::to_string(price_);
	ret_val += " ";
	ret_val += std::to_string(qty_); 
	ret_val += " left.";
	//return string
	return ret_val;
}

void Book::dump(std::ostream& os) const {
	//use Product's dump function and account for additional isbn and author members
	Product::dump(os);
	os << isbn_ << "\n" << author_ << endl;
}
