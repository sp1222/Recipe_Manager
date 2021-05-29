/*
	IngredientInRecipe.cpp
	Function definitions for IngredientInRecipe.h
*/

#include "IngredientInRecipe.h"
#include "IngredientList.h"

#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>      // redefines the new() operator 
#endif

// Makes two IngredientInRecipe objects comparable using name variable.
bool IngredientInRecipe::operator == (const IngredientInRecipe& i) const
{
	return ingredient == i.ingredient;
}

// Makes two IngredientInRecipe objects comparable using name variable.
bool IngredientInRecipe::operator != (const IngredientInRecipe& i) const
{
	return !operator == (i);
}

// Initialize a blank IngredientInRecipe object.
IngredientInRecipe::IngredientInRecipe()
{
	ingredientQuantity = 0.0f;
	string unit = "NONE";
	Units u(unit);
	ingredientUnit = u;
}

// Initialize an Ingredient object with using valid arguments.
IngredientInRecipe::IngredientInRecipe(string& ingredient, float& quantity, string& unit, list<Ingredient>& lst)
{
	// first, determine if the ingredient exists.
	if (doesNamedIngredientExist(ingredient, lst))
	{
		this->ingredient = &getIngredientInList(ingredient, lst);
		this->ingredient->incrementRecipesUsingIngredientCount();
//		float2Decimals(quantity);
		ingredientQuantity = quantity;
		Units u(unit);
		ingredientUnit = u;
	}
}

// Initialize an Ingredient object with using valid arguments.
IngredientInRecipe::IngredientInRecipe(Ingredient& ingredient, float& quantity, string& unit)
{
	this->ingredient = &ingredient;
	this->ingredient->incrementRecipesUsingIngredientCount();
//	float2Decimals(quantity);
	ingredientQuantity = quantity;
	Units u(unit);
	ingredientUnit = u;
}

// Set the reference to Ingredient object for this IngredientInRecipe object.
void IngredientInRecipe::setIngredient(Ingredient& ingredient)
{
	if (this->ingredient != nullptr)
		this->ingredient->decrementRecipesUsingIngredientCount();
	this->ingredient = &ingredient;
	this->ingredient->incrementRecipesUsingIngredientCount();
}

// Set the quantity value for this IngredientInRecipe object.
void IngredientInRecipe::setIngredientQuantity(float& quantity)
{
	if (quantity > 0)
		ingredientQuantity = quantity;
	else
		ingredientQuantity = 0.0;

//	float2Decimals(quantity);
}

// Set the Units object for this IngredientInRecipe object.
void IngredientInRecipe::setIngredientUnit(string& unit)
{
	Units u(unit);
	ingredientUnit = u;
}

// Returns the reference to Ingredient object of this IngredientInRecipe object.
Ingredient& IngredientInRecipe::getIngredient()
{
	return *ingredient;
}

// Returns the name of the Ingredient object being referenced.
string IngredientInRecipe::getIngredientName() const
{
	return ingredient->getName();
}

// Returns the quantity value for this IngredientInRecipe object.
float IngredientInRecipe::getIngredientQuantity() const
{
	return ingredientQuantity;
}

// Returns the Units object for this IngredientInRecipe object.
Units IngredientInRecipe::getIngredientUnit()
{
	return ingredientUnit;
}

// Returns the Units object's string value for this IngredientInRecipe object.
string IngredientInRecipe::getIngredientUnitStr() const
{
	return ingredientUnit.getUnitStr();
}
