/*
	Helpers.h
	Helper functions to handle quick small tasks needed across multiple classes.
*/

#pragma once
#ifndef HELPERS_H
#define HELPERS_H

#include <list>
#include <string>

using namespace std;

/*
	Removes all commas from a string.
	@param str : reference to string variable to remove comments from
*/
void stringRemoveCommas(string& str);

/*
	Converts all characters in a string to uppercase
	@param str : reference to string variable to convert all characters to uppercase
*/
void stringToUpperAll(string& str);

// Do I want to keep this one?
void float2Decimals(float& flt);

#endif // !HELPERS_H
