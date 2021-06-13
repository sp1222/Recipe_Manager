/*
	RecipeList.h
	Handles lists of type Recipe functionalities.
*/

#pragma once
#ifndef RECIPELIST_H
#define RECIPELIST_H

#include "Recipe.h"

/*
	Add a Recipe object to list<Recipe>.
	@param name : name of the Recipe object.
	@param cuisine : cultural cuisine type of the Recipe object.
	@param description : Recipe object's description.
	@param direction : Recipe object's directions.
	@param servingCount : the number of recipes produced by the Recipe object.	4 servings
	@param yield : numerical value indicating the number of units of measure.	8
	@param yieldUnit : the unit of measure produced by the Recipe.				POUND
	@param recipetype : usage of the recipe (dressing, main, appetizer, snack, etc).
	@param recipetypelst : list of recipetypes, pair<string, int>, to track number of different recipetypes.
	@param recipelst : list<Recipe> object to add the new Recipe object to.
*/
bool addRecipe(std::string& name, std::string& cuisine, std::string& description, std::string& direction, int& servingCount, int& yield, std::string& yieldUnit, std::string& recipetype, std::list<std::pair<std::string, int>>& recipetypelst, std::list<Recipe>& recipelst);

/*
	Add a Recipe object to list<Recipe>.
	@param recipe : Recipe object being added to the list<Recipe>.
	@param recipelst : list<Recipe> object to add the new Recipe object to.
*/
//void addRecipe(Recipe& recipe, list<Recipe>& lst);

/*
	Remove a Recipe object from list<Recipe>.
	@param name : name of the Recipe object.
	@param recipelst : list<Recipe> the Recipe object is being removed from.
	@return If recipe was successfully removed.
*/
bool removeRecipe(std::string& name, std::list<Recipe>& lst);

/*
	Save list<Recipe> to comma separated values file.
	Note: the fileName string must end in ".csv".
	@param fileName : name of the file to save the list<Recipe> to.
	@param recipelst : list<Recipe> object to save.
*/
void saveRecipeList(std::string& fileName, std::list<Recipe>& lst);

/*
	Comma separated values file to load list<Recipe> from.
	Note: the fileName string must end in ".csv".
	@param fileName : name of the file to load the list<Recipe> from.
	@param recipelst : list<Recipe> object to be loaded.
	@param ingredientlst : list<Recipe> object use as reference for list<IngredientInRecipe>.
	@param recipetypelst : list of recipetypes, pair<string, int>, to track number of different recipetypes.
*/
void loadRecipeList(std::string& fileName, std::list<Recipe>& recipelst, std::list<Ingredient>& ingredientlst, std::list<std::pair<std::string, int>>& recipetypelst);

/*
	Sort the list<Recipe> by column indicated in front end.
	@param byCol : the column indicated in front end to sort the list<Recipe> by.
	@param lst : list<Recipe> object to sort.
*/
void sortRecipes(int byCol, std::list<Recipe>& lst);

/*
	Comparator by name for two Recipe objects.
	@param first : first Recipe object to be compared.
	@param second : second Recipe object to be compared.
	@return If first is less than second.
*/
bool compareRecipeNames(const Recipe& first, const Recipe& second);

/*
	Comparator by cuisine for two Recipe objects.
	@param first : first Recipe object to be compared.
	@param second : second Recipe object to be compared.
	@return If first is less than second.
*/
bool compareRecipeCuisines(const Recipe& first, const Recipe& second);

/*
	Comparator by recipetype for two Recipe objects.
	@param first : first Recipe object to be compared.
	@param second : second Recipe object to be compared.
	@return If first is less than second.
*/
bool compareRecipeTypes(const Recipe& first, const Recipe& second);

/*
	Comparator by servingCount for two Recipe objects.
	@param first : first Recipe object to be compared.
	@param second : second Recipe object to be compared.
	@return If first is less than second.
*/
bool compareServingCounts(const Recipe& first, const Recipe& second);

/*
	Sort the list<IngredientInRecipe> by column indicated in front end.
	@param byCol : the column indicated in front end to sort the list<IngredientInRecipe> by.
	@param lst : list<IngredientInRecipe> object to sort.
*/
void sortRecipeIngredients(int byCol, std::list<IngredientInRecipe>& lst);

/*
	Comparator by name for two IngredientInRecipe objects.
	@param first : first IngredientInRecipe object to be compared.
	@param second : second IngredientInRecipe object to be compared.
	@return If first is less than second.
*/
bool compareIngredientInRecipeNames(const IngredientInRecipe& first, const IngredientInRecipe& second);

/*
	Comparator by quantity for two IngredientInRecipe objects.
	@param first : first IngredientInRecipe object to be compared.
	@param second : second IngredientInRecipe object to be compared.
	@return If first is less than second.
*/
bool compareIngredientInRecipeQuantity(const IngredientInRecipe& first, const IngredientInRecipe& second);

/*
	Comparator by Unit for two IngredientInRecipe objects.
	@param first : first IngredientInRecipe object to be compared.
	@param second : second IngredientInRecipe object to be compared.
	@return If first is less than second.
*/
bool compareIngredientInRecipeUnits(const IngredientInRecipe& first, const IngredientInRecipe& second);

/*
	Determines if a Recipe object exists in list<Recipe> by name.
	@param name : name of the Recipe object being searched for.
	@param lst : list<Recipe> to search in.
	@return If Recipe object by name exists in list<Recipe>.
*/
//bool doesRecipeExist(string& name, list<Recipe>& lst);

/*
	Returns the reference to Recipe object by name in list<Recipe>.
	@param name : name of the Recipe object to return.
	@param lst : list<Recipe> to search in.
	@return Reference to Recipe object in list<Recipe>.
*/
Recipe& getRecipeInList(std::string& name, std::list<Recipe>& lst);

#endif