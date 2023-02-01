#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
	//conv input to lower
	rawWords = convToLower(rawWords);
	//create set of strings to return
	set<std::string> words;
	//create and initialize keyword variable
	string keyword = "";
	//loop through input
	for (size_t i = 0; i < rawWords.size(); i++) {
		//check for punctuation
		if (rawWords[i] == 39 || rawWords[i] == ' '|| rawWords[i] == '.') {
			//check for current keyword size if punctuation found
			if (keyword.size() >= 2) {
			//if keyword is valid (greater than size 2)
			keyword = convToLower(keyword);
			//insert it into to set
			words.insert(keyword);
			}
			//reset keyword variable
			keyword = "";
		}
		else {
			//keep adding characters from input string
			keyword += rawWords[i];
		}
	}
	//if we finish iterating through word and have a valid keyword, add it to set
	if (keyword.size() >= 2) {
		words.insert(keyword);
	}
	//return set of keywords
	return words;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
