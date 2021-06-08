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
	return ingredientptr == i.ingredientptr;
}

// Makes two IngredientInRecipe objects comparable using name variable.
bool IngredientInRecipe::operator != (const IngredientInRecipe& i) const
{
	return !operator == (i);
}

// Initialize a blank IngredientInRecipe object.
IngredientInRecipe::IngredientInRecipe()
{
	this->quantity = 0.0f;
	string unit = "NONE";
	Units u(unit);
	this->unit = u;
}

// Initialize an Ingredient object with using valid arguments.
IngredientInRecipe::IngredientInRecipe(string& ingredient, float& quantity, string& unit, list<Ingredient>& lst)
{
	this->ingredientptr = &getIngredientInList(ingredient, lst);
	this->ingredientptr->incrementRecipesUsingIngredientCount();
//		float2Decimals(quantity);
	this->quantity = quantity;
	Units u(unit);
	this->unit = u;
}

// Initialize an Ingredient object with using valid arguments.
IngredientInRecipe::IngredientInRecipe(Ingredient& ingredient, float& quantity, string& unit)
{
	this->ingredientptr = &ingredient;
	this->ingredientptr->incrementRecipesUsingIngredientCount();
//	float2Decimals(quantity);
	this->quantity = quantity;
	Units u(unit);
	this->unit = u;
}

// Set the reference to Ingredient object for this IngredientInRecipe object.
void IngredientInRecipe::setIngredient(Ingredient& ingredient)
{
	if (this->ingredientptr != nullptr)
		this->ingredientptr->decrementRecipesUsingIngredientCount();
	this->ingredientptr = &ingredient;
	this->ingredientptr->incrementRecipesUsingIngredientCount();
}

// Determines if an ingredient exists. If so sets the reference to Ingredient object for this IngredientInRecipe object.
void IngredientInRecipe::setIngredient(string& name, list<Ingredient>& lst)
{
	if (doesNamedItemExist(name, lst))
	{
		for (auto& i : lst)
		{
			if (name == i.getName())
			{
				if (this->ingredientptr != nullptr)
					this->ingredientptr->decrementRecipesUsingIngredientCount();
				this->ingredientptr = &i;
				this->ingredientptr->incrementRecipesUsingIngredientCount();
				break;
			}
		}
	}
}

// Set the quantity value for this IngredientInRecipe object.
void IngredientInRecipe::setIngredientQuantity(float& quantity)
{
	if (quantity > 0)
		this->quantity = quantity;
	else
		this->quantity = 0.0;

//	float2Decimals(quantity);
}

// Set the Units object for this IngredientInRecipe object.
void IngredientInRecipe::setIngredientUnit(string& unit)
{
	if (!unit.empty())
	{
		Units u(unit);
		this->unit = u;
	}
}

// Returns the reference to Ingredient object of this IngredientInRecipe object.
Ingredient& IngredientInRecipe::getIngredient()
{
	return *ingredientptr;
}

// Returns the name of the Ingredient object being referenced.
string IngredientInRecipe::getIngredientName() const
{
	return ingredientptr->getName();
}

// Returns the quantity value for this IngredientInRecipe object.
float IngredientInRecipe::getIngredientQuantity() const
{
	return this->quantity;
}

// Returns the Units object for this IngredientInRecipe object.
Units IngredientInRecipe::getIngredientUnit()
{
	return this->unit;
}

// Returns the Units object's string value for this IngredientInRecipe object.
string IngredientInRecipe::getIngredientUnitStr() const
{
	return this->unit.getUnitStr();
}
