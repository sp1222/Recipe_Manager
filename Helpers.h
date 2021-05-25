#pragma once
#ifndef HELPERS_H
#define HELPERS_H

#include <list>
#include <string>

using namespace std;

void stringRemoveCommas(string& str);
void stringToUpperAll(string& str);
void float2Decimals(float& flt);


template<class T>
bool doesItemExist(string& str, list<T>& lst);

/*
template<class T>
bool compareNames(const T& first, const T& second);
*/

#endif // !HELPERS_H
