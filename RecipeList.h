#pragma once
#ifndef RECIPELIST_H
#define RECIPELIST_H
#include "Recipe.h"

void addRecipe(string& name, string& desc, string& direct, int& count, int& yield, string& unit, string& type, list<pair<string, int>>& tList, list<Recipe>& list);
void addRecipe(Recipe& recipe, list<Recipe>& list);
void removeRecipe(string& name, list<Recipe>& list);
void saveRecipeList(string& file, list<Recipe>& list);
void loadRecipeList(string& file, list<Recipe>& rList, list<Ingredient>& iList, list<pair<string, int>>& mlist);
void sortByMealType();
void sortByNameRecipe();
bool doesRecipeExist(string& name, list<Recipe>& list);
Recipe& getRecipeInList(string& name, list<Recipe>& list);

#endif