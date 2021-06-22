/*
	Category.h
	Defines a Category Class.
*/

#pragma once
#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>

#include "Helpers.h"

/*
	Category class for instaces of Category objects.
	This will be the user controlled ingredient category management system.
	The user will be able to add and remove categories as they see fit.
*/
class Category
{
private:
	std::string name;
	int ingredientsUsingCategoryCount;
public:

	/*
		Makes two Category objects comparable using name variable.
		@param c : constant reference to Category object.
		@return : If object matches this instance of a Category.
	*/
	bool operator == (const Category& c) const;

	/*
		Makes two Category objects comparable using name variable.
		@param c : constant reference to Category object.
		@return : If object does not match this instance of a Category.
	*/
	bool operator != (const Category& c) const;

	/*
		Create a Category object "NONE".
	*/
	Category();

	/*
		Initialize a Category object based on a valid string parameter.
		@param name : reference to string to initialize the name of the Category object.
	*/
	Category(std::string& name);

	/*
		Redefine the name of the Category.
		@param name : reference to string to redefine the name of the Category object.
		@return If the name has successfully changed.
	*/
	bool setName(std::string& name);

	/*
		Returns the name of the Category object.
		@return : name of this Category object.
	*/
	std::string getName() const;

	/*
		Increments a variable that tracks how many Ingredient objects are using this Category object.
	*/
	void incrementIngredientsUsingCategoryCount();

	/*
		Decrements a variable that tracks how many Ingredient objects are using this Category object.
	*/
	void decrementIngredientsUsingCategoryCount();

	/*
		Returns how many Ingredient objects are using this Category object.
		@return : number of Ingredient objects using this Category object.
	*/
	int getIngredientsUsingCategoryCount() const;
};

#endif
