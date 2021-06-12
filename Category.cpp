/*
	Category.cpp
	Function definitions for Category.h
*/

#include "Category.h"

using namespace std;

#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>      // redefines the new() operator 
#endif

// Makes two Category objects comparable using name variable
bool Category::operator == (const Category& c) const
{
	return name == c.name;
}

// Makes two Category objects comparable using name variable
bool Category::operator != (const Category& c) const
{
	return !operator == (c);
}

// Create a Category object "NONE"
Category::Category()
{
	name = "NONE";
	ingredientsUsingCategoryCount = 0;
}

// Initialize a Category object based on a valid string parameter
Category::Category(string& name)
{
	this->name = name;
	ingredientsUsingCategoryCount = 0;
}

// Redefine the name of the Category
void Category::setName(string& name)
{
	stringRemoveCommas(name);
	stringToUpperAll(name);
	if(!name.empty())
		this->name = name;
}

// Returns the name of the Category object
string Category::getName() const
{
	return name;
}

// Increments a variable that tracks how many Ingredient objects are using this Category object
void Category::incrementIngredientsUsingCategoryCount()
{
	ingredientsUsingCategoryCount++;
}

// Decrements a variable that tracks how many Ingredient objects are using this Category object
void Category::decrementIngredientsUsingCategoryCount()
{
	ingredientsUsingCategoryCount--;
}

// Returns how many Ingredient objects are using this Category object
int Category::getIngredientsUsingCategoryCount() const
{
	return ingredientsUsingCategoryCount;
}