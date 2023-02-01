#include "util.h"
#include "mydatastore.h"
#include "product.h"
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
using namespace std;

MyDataStore:: MyDataStore() 
{
	//instantiate all private data members
	std::vector<User*> users_();
	std::vector<Product*> products_();
	std::map<std::string, std::set<Product*>> keywords_products();
	std::map<std::string, std::vector<Product*>> users_cart();
	std::map<std::string, User*> username_user();


}

MyDataStore::~MyDataStore() 
{
	//deallocate products vector if necessary (ie if any products have been allocated)
	if(products_.size() > 0) {
		for(std::vector<Product*>::iterator it= products_.begin(); it != products_.end(); ++it) {
			delete *it;
		}
	}

	//deallocate users vector if necessary (ie if any users have been allocated)
	if (users_.size() > 0) {
		for(std::vector<User*>::iterator it= users_.begin(); it != users_.end(); ++it) {
			delete *it;
		}
	}

}

void MyDataStore::addProduct(Product* p) {
	//add product to products vector
	(products_).push_back(p);
	//create a set to hold keywords from given product
	std::set<std::string> p_keywords = p -> keywords();
	//iterate through keywords for the product
	for(std::set<std::string>::iterator it=p_keywords.begin(); it != p_keywords.end(); ++it) {
	//if keyword is in map already, add product to set that is stored in the value for that keyword
	//the set contains all products that have this keyword
		if (keywords_products.find(*it) != keywords_products.end()) {
				keywords_products.find(*it) -> second.insert(p);
		}
	//otherwise, create a new pair with this keyword and a new set
	//add this product to the new set
		else {
			std::set<Product*> product_set;
			product_set.insert(p);
			keywords_products[*it] = product_set;
		}
	}
}

void MyDataStore::addUser(User* u) {
	//add user to vector of users
	(users_).push_back(u);
	//add user to map of usernames to users
	username_user[u -> getName()] = u;
	//add user to map that will map user to their cart
	std::vector<Product*> prod;
	users_cart[u ->getName()] = prod;
}

std::vector<Product*> MyDataStore:: search(std::vector<std::string>& terms, int type) {
	//create set to hold products to return
	//create vector to return 
	std::set<Product*> currentset_products;
	std::vector<Product*> vector_products;
	//instantiate current set of products to the set of products that the first term points to
	if (keywords_products.find(terms[0]) != keywords_products.end()) {		
		currentset_products = keywords_products.find(terms[0]) -> second;
	}
	//if type == AND(ie we want an intersection between sets of products from multiple key words), run this code
	if (type == 0) {
		//iterate through terms vector
		for(size_t i = 1; i < terms.size(); i++) {
			if (keywords_products.find(terms[i]) != keywords_products.end()) {
				//create a set for the products found	for each keyword		
				std::set<Product*> new_products = keywords_products.find(terms[i]) -> second;
				//add to currentset of products (union between new set and currentset)
				currentset_products = setIntersection(currentset_products, new_products);
			}
		}
	}
	//if type == OR(ie we want a union between sets of products from multiple key words), run this code
	else if (type == 1) {
		//iterate through terms vector
		for(size_t i = 1; i < terms.size(); i++) {
			if (keywords_products.find(terms[i]) != keywords_products.end()) {
				//create a set for the products found	for each keyword
				std::set<Product*> new_products = keywords_products.find(terms[i]) -> second;		
				//add to currentset of products (union between new set and currentset)
				currentset_products = setUnion(currentset_products, new_products);
			}
		}	
	}

	for(std::set<Product*>::iterator it = currentset_products.begin(); it != currentset_products.end(); ++it)
	{
		//add each product from current set to vector to return
		vector_products.push_back(*it);
	}
return vector_products;
}

void MyDataStore:: add_cart(std::string username, Product* p) {
	//account for invalid username entry
	if (!(users_cart.find(username) != users_cart.end())) {
		cout << "Invalid request" << endl;
	} 
	//otherwise, add the product to the user's cart via the map that connects usernames to carts
	else if (users_cart.find(username) != users_cart.end()) {
		(users_cart.find(username) -> second).push_back(p);
	}
}

void MyDataStore :: view_cart(std::string username) {
	//account for invalid username entry
	if (!(users_cart.find(username) != users_cart.end())) {
		cout << "Invalid username" << endl;
	} 
	else if (users_cart.find(username) != users_cart.end()) {
		//create a variable size to hold the size of the user's cart from the map of usernames to carts
		unsigned int size = (users_cart.find(username) -> second).size();
		//create a variable cart to hold contents of user's cart from the cart that maps usernames to carts
		std::vector<Product*> cart = (users_cart.find(username) -> second);
		//iterate through the cart and call displayString for each product in the cart
		for (size_t t = 0; t < size; t++) {
			cout << "Item " << t+1 << endl;
    	cout << (cart[t]) -> displayString() << endl;
			(cart[t]) -> displayString();
    }
	}
}

void MyDataStore :: buy_cart(std:: string username) {
	//account for invalid username entry
	if (!(users_cart.find(username) != users_cart.end())) {
		cout << "Invalid username" << endl;
	}
	else if (users_cart.find(username) != users_cart.end()) {
		//create a variable size to hold the size of the user's cart from the map of usernames to carts
		unsigned int size = (users_cart.find(username) -> second).size();
		//create a variable cart to hold contents of user's cart from the map of usernames to carts
		std::vector<Product*>* curr_cart = &(users_cart.find(username) -> second);
		//create a new cart to hold items that the user cannot afford or isn't in stock
		std::vector<Product*> new_cart;
		//create a variable curr_user to hold current user pointer
		User* curr_user = (username_user.find(username)) -> second; 
		//iterate through user's cart
		for (size_t t = 0; t < size; t++) {
			//check if user can afford item and if it is in stock
			if ((curr_user -> getBalance() >= (*curr_cart)[t] -> getPrice()) && ((*curr_cart)[t] -> getQty() > 0)) {
				//deduct items cost from users's balance
				curr_user -> deductAmount((*curr_cart)[t] -> getPrice());
				//decrease the stock quantity by 1
				(*curr_cart)[t] -> subtractQty(1);
			}
			else {
				//if user cannot afford item or is not in stock, add it to the new vector
				new_cart.push_back((*curr_cart)[t]);
				//skip to next item
				t++;
			}
		}
		//set the current user's cart = to the new_cart created
		*curr_cart = new_cart;
	}
}


void MyDataStore:: dump(std::ostream& ofile) {
	//list products
	ofile << "<products>" << "\n";
	//iterate through products vector and call each product's dump
	for (unsigned int i = 0; i < products_.size(); i++) {
		products_[i] -> dump(ofile);
	}
	ofile << "</products>" << "\n";
	//list users
	ofile << "<users>" << "\n";
	//iterate through users vector and call each users's dump
	for (unsigned int j = 0; j < users_.size(); j++)
	{
		users_[j] -> dump(ofile);
	}
	ofile <<"</users>";

}



