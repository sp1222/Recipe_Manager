#include "IngredientInRecipe.h"
#include "IngredientList.h"
#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>      // redefines the new() operator 
#endif

bool IngredientInRecipe::operator == (const IngredientInRecipe& i) const
{
	return ingredient == i.ingredient;
}

bool IngredientInRecipe::operator != (const IngredientInRecipe& i) const
{
	return !operator == (i);
}

IngredientInRecipe::IngredientInRecipe()
{
	ingredientQuantity = 0.0f;
	string unit = "NONE";
	Units u(unit);
	ingredientUnit = u;
}

IngredientInRecipe::IngredientInRecipe(string& ingred, float& quantity, string& unit, list<Ingredient>& list)
{
	// first, determine if the ingredient exists.
	if (doesIngredientExist(ingred, list))
	{
		ingredient = &getIngredientInList(ingred, list);
		ingredient->incrementRecipesUsingIngredientCount();
//		float2Decimals(quantity);
		ingredientQuantity = quantity;
		Units u(unit);
		ingredientUnit = u;
	}
}

IngredientInRecipe::IngredientInRecipe(Ingredient& ingred, float& quantity, string& unit)
{
	ingredient = &ingred;
	ingredient->incrementRecipesUsingIngredientCount();
//	float2Decimals(quantity);
	ingredientQuantity = quantity;
	Units u(unit);
	ingredientUnit = u;
}

void IngredientInRecipe::setIngredient(Ingredient& ingred)
{
	if (ingredient != nullptr)
		ingredient->decrementRecipesUsingIngredientCount();
	ingredient = &ingred;
	ingredient->incrementRecipesUsingIngredientCount();
}

void IngredientInRecipe::setIngredientQuantity(float& quantity)
{
	if (quantity > 0)
		ingredientQuantity = quantity;
	else
		ingredientQuantity = 0.0;

//	float2Decimals(quantity);
}

void IngredientInRecipe::setIngredientUnit(string& unit)
{
	Units u(unit);
	ingredientUnit = u;
}

Ingredient& IngredientInRecipe::getIngredient()
{
	return *ingredient;
}

string IngredientInRecipe::getIngredientName() const
{
	return ingredient->getName();
}

float IngredientInRecipe::getIngredientQuantity() const
{
	return ingredientQuantity;
}

Units IngredientInRecipe::getIngredientUnit()
{
	return ingredientUnit;
}

string IngredientInRecipe::getIngredientUnitStr() const
{
	return ingredientUnit.getUnitStr();
}
