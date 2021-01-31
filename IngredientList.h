
#pragma once
#ifndef INGREDIENTLIST_H
#define INGREDIENTLIST_H
#include "Ingredient.h"
#include "CategoryList.h"

void addIngredient(string& name, string& description, Category& category, list<Ingredient>& list);
//void addIngredient(Ingredient& name);
void removeIngredient(string& name, list<Ingredient>& list);
void saveIngredientList(string& ingredientListFile, list<Ingredient>& list);
void loadIngredientList(string& ingredientListFile, list<Ingredient>& ilist, list<Category>& clist);
void sortByCategory();
void sortByName();
bool doesIngredientExist(string& name, list<Ingredient>& list);
Ingredient& getIngredientInList(string& name, list<Ingredient>& list);

#endif
