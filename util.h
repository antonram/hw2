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
	// will hold resulting items that intersect
	std::set<T> Result;

	// if either is empty, we return empty set
	if(s1.empty() || s2.empty()) {
		return Result;
	}

	// we want to find set with smaller size so we iterate through the smallest set
	typename std::set<T>::iterator itr;
	if(s1.size() >= s2.size()) {
		for(itr = s2.begin(); itr != s2.end(); ++itr) {
			//if item is found
			if(s1.find(*itr) != s1.end()) {
				Result.insert(*itr);
			}
		}
	}
	// if s2 is bigger
	else {
		for(itr = s1.begin(); itr != s1.end(); ++itr) {
			//if item is found
			if(s2.find(*itr) != s2.end()) {
				Result.insert(*itr);
			}
		}
		
	}
	// we return the resulting set. Will be empty if no items overlap
	return Result;
}


template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
	//will store result
	std::set<T> Result;

	// if no items, return empty set.
	if(s1.empty() && s2.empty()) {
		return Result;
	}

	//will iterate through sets
	typename std::set<T>::iterator itr;

	// we add items of s1 into result
	for(itr = s1.begin(); itr != s1.end(); ++itr) {
		// if item not already in result
		if(Result.find(*itr) == Result.end()) {
			Result.insert(*itr);
		}
	}

	// now items of s2 into result
	for(itr = s2.begin(); itr != s2.end(); ++itr) {
		// if item not already in result
		if(Result.find(*itr) == Result.end()) {
			Result.insert(*itr);
		}
	}

	// we return the resulting set.
	return Result;
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
