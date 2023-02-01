#ifndef UTIL_H
#define UTIL_H
#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
//create set to return
std::set<T> intersection;

//iterate through first set
for(typename std::set<T>::iterator it=s1.begin(); it != s1.end(); ++it)
	//if second set has an element that is also in the first set, add to set being returned
	if(s2.find(*it) != s2.end()) {
		intersection.insert(*it);
	}
	//return intersection set
return intersection;
}



template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
//create set to return
std::set<T> u;
//iterate through first set and add every element
for(typename std::set<T>::iterator it=s1.begin(); it != s1.end(); ++it){
u.insert(*it);
}

//iterate through second set
for(typename std::set<T>::iterator it=s2.begin(); it != s2.end(); ++it){
//if element is not already in union set, add it
if(u.find(*it) == u.end()) {
	u.insert(*it);
	}
}

//return union set
return u;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
