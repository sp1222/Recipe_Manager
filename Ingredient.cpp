/*
	Ingredient.cpp
	Function definitions for Ingredient.h
*/

#include "Category.h"
#include "Ingredient.h"

#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>      // redefines the new() operator 
#endif

// Makes two Ingredient objects comparable by name
bool Ingredient::operator == (const Ingredient & i) const
{
	return name == i.name;
}

// Makes two Ingredient objects comparable by name
bool Ingredient::operator != (const Ingredient& i) const
{
	return !operator == (i);
}

// Create an empty Ingredient object
Ingredient::Ingredient() 
{
	name = "";
	description = "";
	category = nullptr;
	recipesUsingIngredientCount = 0;
}

// Initialize an Ingredient object with valid parameter values
Ingredient::Ingredient(string& name, string& description, Category& categoryObj)
{

	setName(name);
	setDescription(description);
	setCategory(categoryObj);
	recipesUsingIngredientCount = 0;
}

// Set the name of the Ingredient object
void Ingredient::setName(string& name)
{
	stringRemoveCommas(name);
	this->name = name;
}

// Set the description of the Ingredient object
void Ingredient::setDescription(string& description)
{
	stringRemoveCommas(description);
	description = description;
}

// Set the reference to Category object from list<Category> object
void Ingredient::setCategory(Category& categoryObj)
{
	// NOTE: do we need to remove commas from each string value?  No.
	// WILL toupper BE REQUIRED WHEN USING DROPDOWN BOXES?  No.

	// since this implies a re-categorizing of this instance of an ingredient, 
	// we first decrement the ingredientsUsingCategoryCount value for the current category if needed.
	// reassign ingredientCategory to a reference of its new category in the categoryList object.
	// then increment the ingredientsUsingCategoryCount value for the new current category.
	if (category != nullptr)
		category->decrementIngredientsUsingCategoryCount();
	category = &categoryObj;
	category->incrementIngredientsUsingCategoryCount();
}

// Returns the name of Ingredient object
string Ingredient::getName() const
{
	return name;
}

// Returns the description of Ingredient object
string Ingredient::getDescription()
{
	return description;
}

// Returns the Category object this Ingredient object points to
Category& Ingredient::getCategoryObj()
{
	return *category;
}

//Returns the string representation of Category object this Ingredient object points to
string Ingredient::getCategoryStr() const
{
	return category->getName();
}

// Returns the number of Recipe objects this Ingredient object is a part of
int Ingredient::getRecipesUsingIngredientCount() const
{
	return recipesUsingIngredientCount;
}

// Increments the number of Recipe objects this Ingredient object is a part of
void Ingredient::incrementRecipesUsingIngredientCount()
{
	recipesUsingIngredientCount++;
}

// Decrements the number of Recipe objects this Ingredient object is a part of
void Ingredient::decrementRecipesUsingIngredientCount()
{
	if (recipesUsingIngredientCount > 0)
		recipesUsingIngredientCount--;
}