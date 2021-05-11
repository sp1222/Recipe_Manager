#pragma once
#ifndef RECIPELIST_H
#define RECIPELIST_H
#include "Recipe.h"

void addRecipe(string& name, string& desc, string& direct, int& count, int& yield, string& unit, string& type, list<pair<string, int>>& tList, list<Recipe>& list);
void addRecipe(Recipe& recipe, list<Recipe>& list);
bool removeRecipe(string& name, list<Recipe>& list);
void saveRecipeList(string& file, list<Recipe>& list);
void loadRecipeList(string& file, list<Recipe>& rList, list<Ingredient>& iList, list<pair<string, int>>& mlist);
void sortRecipes(int byCol, list<Recipe>& list);
bool compareRecipeNames(const Recipe& first, const Recipe& second);
bool compareMealTypes(const Recipe& first, const Recipe& second);
bool compareServingCounts(const Recipe& first, const Recipe& second);
void sortRecipeIngredients(int byCol, list<IngredientInRecipe>& list);
bool compareIngredientInRecipeNames(const IngredientInRecipe& first, const IngredientInRecipe& second); 
bool compareIngredientInRecipeQuantity(const IngredientInRecipe& first, const IngredientInRecipe& second);
bool compareIngredientInRecipeUnits(const IngredientInRecipe& first, const IngredientInRecipe& second);
bool doesRecipeExist(string& name, list<Recipe>& list);
Recipe& getRecipeInList(string& name, list<Recipe>& list);

#endif