#pragma once
#ifndef MEALTYPE_H
#define MEALTYPE_H
#include<list>
#include<string>
using namespace std;

void addMealType(string& type, list<pair<string, int>>& list);
void removeMealType(string& type, list<pair<string, int>>& list);
bool doesMealTypeExist(string& type, list<pair<string, int>>& list);
int getRecipeUsingMealTypeCount(string& type, list<pair<string, int>>& list);
void incrementRecipeUsingMealTypeCount(string& type, list<pair<string, int>>& list);
void decrementRecipeUsingMealTypeCount(string& type, list<pair<string, int>>& list);
void saveMealType(list<pair<string, int>>& list);
void loadMealType(list<pair<string, int>>& list);

#endif // !MEALTYPE_H