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
	//represents words to be returned
    std::set<std::string> wordList;
    //if empty string, returns empty list
    if(rawWords.size() == 0) {
        return wordList;
    }
    
    //represents delimiters (punctiation)
    std::set<char> delim = {' ', ',', '.', '\'', '\"', '!', '?', 
    '(', ')', '#', '%'};
    //eliminates whitespace at ends of input
    trim(rawWords);
    //will iterate through string
    size_t start = 0;
    size_t end = 0;
    //iterates through entire word
    while(end != rawWords.size()) {
				// if we hit a delimiter
        if(delim.find(rawWords[end]) != delim.end()) {
					// if above acceptable size, insert what we have so far
            if(end - start >= 2) {
                wordList.insert(rawWords.substr(start, end - start));
            }
            //in case there's more than one punctuation, must keep moving end index forward until we hit another character
            while(delim.find(rawWords[end]) != delim.end()) {
                end++;
            }
            start = end;
						end++;
        }
        else {
            end++;
        }
    }
    //since word cannot end in whitespace, we add last phrase to wordList in case we missed a word
    if(end - start >= 2) {
        wordList.insert(rawWords.substr(start));
    }
    //returns newly formed set of words
    return wordList;
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
