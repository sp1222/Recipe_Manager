/*
	IngredientList.h
	Handles lists of type Ingredient functionalities.
*/

#pragma once
#ifndef INGREDIENTLIST_H
#define INGREDIENTLIST_H

#include "CategoryList.h"
#include "Helpers.h"
#include "Ingredient.h"


/*
	Add an Ingredient object to list<Ingredient>.
	@param name : name of the Ingredient object.
	@param description : description of the Ingredient object.
	@param categoryObj : reference to Category object of the Ingredient object.
	@param lst : list<Ingredient> that the Ingredient object is being added to.
*/
bool addIngredient(std::string& name, std::string& description, Category& categoryObj, std::list<Ingredient>& lst);

/*
	Add an Ingredient object to list<Ingredient>.
	@param name : name of the Ingredient object.
	@param description : description of the Ingredient object.
	@param categoryObj : reference to Category object of the Ingredient object.
	@param lst : list<Ingredient> that the Ingredient object is being added to.
*/
void addIngredientFromLoad(std::string& name, std::string& description, Category& categoryObj, std::list<Ingredient>& lst);

/*
	Remove an Ingredient object from list<Ingredient>.
	@param name : name of the Ingredient object.
	@param lst : list<Ingredient> that the Ingredient object is being removed from.
*/
bool removeIngredient(std::string& name, std::list<Ingredient>& lst);

/*
	Save existing list<Ingredient> to designated fileName.
	Output is CSV format, fileName value must end in .csv.
	@param fileName : file name that the ingredient information will be saved to.
	@param lst : list<Ingredient> that the Ingredient object is being saved from.

*/
void saveIngredientList(std::string& fileName, std::list<Ingredient>& lst);

/*
	Load list<Ingredient> from designated fileName.
	Output is CSV format, fileName value must end in .csv.
	@param fileName : file name that the ingredient information will be loaded from.
	@param lst : list<Ingredient> that the Ingredient objects are being loaded to.
*/
void loadIngredientList(std::string& fileName, std::list<Ingredient>& ilst, std::list<Category>& clst);

/*
	Sorts a list<Ingredient> by indicated column.
	@param byCol : column to be sorted by, obtained from wxCommandEvent.
	@param lst : list<Ingredient> that the Ingredient object is being sorted.

*/
void sortIngredients(int byCol, std::list<Ingredient>& lst);

/*
	Comparator by Name.
	@param first : the first constant Ingredient object to be compared.
	@param second : the second constant Ingredient object to be compared.
*/
bool compareIngredientNames(const Ingredient& first, const Ingredient& second);

/*
	Comparator by Categories
	@param first : the first constant Ingredient object to be compared.
	@param second : the second constant Ingredient object to be compared.
*/
bool compareCategories(const Ingredient& first, const Ingredient& second);

/*
	Comparator by number of Recipe objects using Ingredient.
	@param first : the first constant Ingredient object to be compared.
	@param second : the second constant Ingredient object to be compared.
*/
bool compareIngredientRecipeCount(const Ingredient& first, const Ingredient& second);

/*
	Checks if a Ingredient object exists in list<Category> based on its name.
	@param name : name of the Ingredient object.
	@param lst : list<Ingredient> that the Ingredient object is being searched for in.
*/
//bool doesNamedIngredientExist(string& name, list<Ingredient>& lst);

/*
	Returns a reference to named Ingredient object in list<Ingredient> if it exists.
	Otherwise returns first Ingredient object in list<Ingredient>.
	@param name : name of the Ingredient object.
	@param lst : list<Ingredient> that the Ingredient object is being called from.
*/
Ingredient& getIngredientInList(std::string& name, std::list<Ingredient>& lst);

#endif
