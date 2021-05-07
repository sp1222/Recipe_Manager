#pragma once
#ifndef MEALTYPELIST_H
#define MEALTYPELIST_H
#include<list>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
using namespace std;

void addMealType(string& type, list<pair<string, int>>& list);
void removeMealType(string& type, list<pair<string, int>>& list);
bool doesMealTypeExist(string& type, list<pair<string, int>>& list);
int getRecipeUsingMealTypeCount(string& type, list<pair<string, int>>& list);
void incrementRecipeUsingMealTypeCount(string& type, list<pair<string, int>>& list);
void decrementRecipeUsingMealTypeCount(string& type, list<pair<string, int>>& list);

#endif // !MEALTYPELIST_H