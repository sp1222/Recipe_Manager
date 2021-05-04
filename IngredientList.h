
#pragma once
#ifndef INGREDIENTLIST_H
#define INGREDIENTLIST_H
#include "Ingredient.h"
#include "CategoryList.h"

bool addIngredient(string& name, string& description, Category& category, list<Ingredient>& list);
//void addIngredient(Ingredient& ingred, list<Ingredient>& list);
bool removeIngredient(string& name, list<Ingredient>& list);
void saveIngredientList(string& ingredientListFile, list<Ingredient>& list);
void loadIngredientList(string& ingredientListFile, list<Ingredient>& ilist, list<Category>& clist);
void sortIngredients(int byCol, list<Ingredient>& list);
bool compareIngredientNames(const Ingredient& first, const Ingredient& second);
bool compareCategories(const Ingredient& first, const Ingredient& second);
bool compareIngredientRecipeCount(const Ingredient& first, const Ingredient& second);
bool doesIngredientExist(string& name, list<Ingredient>& list);
Ingredient& getIngredientInList(string& name, list<Ingredient>& list);

#endif
