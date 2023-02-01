#ifndef MOVIE_H
#define MOVIE_H
#include <iostream>
#include <string>
#include <set>

class Movie : public Product { 
public: 
		//declare inherited functions 
		Movie (const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating);
		~Movie();
		std::set<std::string> keywords() const;
		std::string displayString() const;
		void dump(std::ostream& os) const;

private:
	//declare additional private data members
	std::string genre_;
	std::string rating_;

};


#endif