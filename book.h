#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include <string>
#include <set>
class Book : public Product { 
	public: 
		//declare inherited functions 
		Book (const std::string category, const std::string name, double price, int qty, const std::string isbn, const std::string author);
		~Book();
		std::set<std::string> keywords() const;
		std::string displayString() const;
		void dump(std::ostream& os) const;

	private:
	//declare additional private data members
		std::string isbn_;
		std:: string author_;

};

#endif

