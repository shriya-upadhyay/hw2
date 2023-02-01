#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include "datastore.h"
#include "product.h"
#include "user.h"
#include <string>
#include <set>
#include <vector>
#include <map>

class MyDataStore : public DataStore { 
public:
		//declare inherited functions 
		MyDataStore();
		~MyDataStore();
		void addProduct(Product* p);
		void addUser(User* u);
		std::vector<Product*> search(std::vector<std::string>& terms, int type);
		void dump(std::ostream& ofile);
		//add functions for menu options
		void add_cart(std::string username, Product* p);
		void view_cart(std::string username);
		void buy_cart(std::string username);

private:
	//create private data members
	//vectors to store all users & products (useful for dynamic memory allocation at end)
	std::vector<User*> users_;
	std::vector<Product*> products_;
	//map to store keywords and their corresponding products
	std::map<std::string, std::set<Product*>> keywords_products;
	//map to store usernames and their corresponding carts
	std::map<std::string, std::vector<Product*>> users_cart;
	//map to store usernames and their corresponding users
	std::map<std::string, User*> username_user;

};
#endif
