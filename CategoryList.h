/*
	CategoryList.h
	Handles lists of type Category functionalities.
*/

#pragma once
#ifndef CATEGORYLIST_H
#define CATEGORYLIST_H

#include <list>

#include "Category.h"

/*
	Adds a new Category object to a list<Category>.
	@param name : Reference to string, the name of the Category object being added to list<Category>.
	@param lst : The list<Category> that the Category object is being added to.
	@return : If the Category object was successfully added to list<Category>.
*/
bool addCategory(std::string& name, std::list<Category>& lst);

/*
	Adds a new Category object to a list<Category>.
	@param name : Reference to string, the name of the Category object being added to list<Category>.
	@param lst : The list<Category> that the Category object is being added to.
	@return : If the Category object was successfully added to list<Category>.
*/
void addCategoryFromLoad(std::string& name, std::list<Category>& lst);

/*
	Removes named Category object from list<Category>.
	@param name : Reference to string, the name of the Category object being removed from list<Category>.
	@param lst : The list<Category> that the Category object is being removed from.
	@return : If the Category object was successfully removed from list<Category>.
*/
bool removeCategory(std::string& name, std::list<Category>& lst);

/*
	Save existing list<Category> to designated fileName.
	File is CSV format, fileName value must end in ".csv".
	@param fileName : Name of the file to save list<Category> to.
	@param lst : The list<Category> that the Category object is being saved.
*/
void saveCategoryList(std::string& fileName, std::list<Category>& lst);

/*
	Load list<Category> from designated fileName.
	File is CSV format, fileName value must end in ".csv".
	@param fileName : Name of the file to save list<Category> to.
	@param lst : The list<Category> that the Category object is being loaded.
*/
void loadCategoryList(std::string& fileName, std::list<Category>& lst);

/*
	Sorts the list<Category> by indicated column.
	@param byCol : Column index to sort the list by.
	@param lst : The list<Category> that the Category object is being loaded.
*/
void sortCategories(int byCol, std::list<Category>& lst);

/*
	Comparator by Name for list sorting.
	@param first : first Category object to make comparison.
	@param second : second Category object to make comparison.
	@return : If the first object is less than the second object.
*/
bool compareCategoryNames(const Category& first, const Category& second);

/*
	Comparator by Ingredient Count for list sorting.
	@param first : first Category object to make comparison.
	@param second : second Category object to make comparison.
	@return : If the first object is less than the second object.
*/
bool compareCategoryIngredientCount(const Category& first, const Category& second); 

/*
	Checks if a Category object exists in list<Category> based on its name.
	@param name : Reference to string, the name of the Category object searched for in list<Category>.
	@param lst : The list<Category> that the Category object is being removed from.
*/
//bool doesNamedCategoryExist(string& name, list<Category>& lst);

/*
	Returns a reference to named Category object in list<Category> if it exists.
	Otherwise returns first Category object in list<Category>.
	@param name : Reference to string, the name of the Category object searched for in list<Category>.
	@param lst : The list<Category> that the Category object is being removed from.
*/
Category& getCategoryInList(std::string& name, std::list<Category>& lst);

#endif
