/*
	Helpers.h
	Helper functions to handle quick small tasks needed across multiple classes.
*/

#pragma once
#ifndef HELPERS_H
#define HELPERS_H

#include <list>
#include <string>

/*
	Removes all commas from a string.
	@param str : reference to string variable to remove comments from
*/
void stringRemoveCommas(std::string& str);

/*
	Converts all characters in a string to uppercase
	@param str : reference to string variable to convert all characters to uppercase
*/
void stringToUpperAll(std::string& str);
/*
	Standardizes float value to two decimal places.
	@param flt : reference to float variable to make two decimal places
*/
void float2Decimals(float& flt);

/*
	Checks if a string can be converted to float.
	@param str : reference to string, is it a float?
	@return boolean if str can be converted to float.
*/
bool isFloat(std::string& str);

/* 
	Template that checks if an object exists in a list based on object's getName().
	@param str : reference to string, name of the object to be searched for.
	@param lst : list of objects being searched.
	@return if an object of type T exists in list<T> by name.

*/
template<typename T>
bool doesNamedItemExist(std::string& str, std::list<T>& lst)
{
	for (auto it = lst.begin(); it != lst.end(); ++it)
	{
		if (it->getName() == str)
			return true;
	}
	return false;
};
/*
// makes a comparison between two objects by their name
template<class T>
bool compareByNames(const T& first, const T& second)
{
	unsigned  i = 0;
	while ((i < first.getName().length()) && (i < second.getName().length()))
	{
		if (tolower(first.getName()[i]) < tolower(second.getName()[i]))
			return true;
		else if (tolower(first.getName()[i]) > tolower(second.getName()[i]))
			return false;
		i++;
	}
	return (first.getName().length() < second.getName().length());
};
*/

#endif // !HELPERS_H
